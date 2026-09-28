#include "htra_proxy_server.h"

HtraProxyServer::HtraProxyServer(QString configPath, QString section, IHtraDevice &device, QObject *parent)
    : QObject(parent),
      configPath(configPath),
      section(section),
      m_device(device) {
    loadConfig();
    server = new QTcpServer(this);

    RFprocessor = new SwitcherProcessor(
        QCoreApplication::applicationDirPath() + "/etc/transport/config.ini",
        "ArduinoRFSwitcher",
        this);

    if(server->listen(ListenIp, port)) {
        qDebug() << name << "started on port:" << port;
    } else {
        qDebug() << name << "start failed on port:" << port;
        qDebug() << server->errorString();
    }

    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void HtraProxyServer::onDataReady() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());

    if(clientSocket) {
        QByteArray &buffer = clientBuffers[clientSocket];
        buffer.append(clientSocket->readAll());

        QByteArray packet;
        while(HtraProtocol::takePacket(buffer, packet)) {
            emit translateLastPacket(packet.toHex());
            processHtraCmd(packet, clientSocket);
        }
    }
}


void HtraProxyServer::sendReply(QTcpSocket *clientSocket, const QByteArray &reply) {
    if(!clientSocket || reply.isEmpty()) {
        return;
    }

    QString clientIp = clientSocket->peerAddress().toString();

    if(clientSocket->peerAddress().protocol() == QAbstractSocket::IPv6Protocol &&
            clientIp.startsWith("::ffff:")) {
        clientIp = clientIp.mid(7); // Deleting "::ffff:"
    }

    clientSocket->write(reply);
}


void HtraProxyServer::loadConfig() {
    QSettings settings(configPath, QSettings::IniFormat);
    settings.beginGroup(section);
    name = settings.value("Name", "tcp_proxy").toString();
    ServerAddress = QHostAddress(settings.value("HostIp", QHostAddress::LocalHost).toString());

    const QString listenIpValue = settings.value("ListenIp").toString().trimmed();
    if(listenIpValue.isEmpty()) {
        ListenIp = QHostAddress::Any;
    } else if(!ListenIp.setAddress(listenIpValue)) {
        qWarning() << name << "invalid ListenIp:" << listenIpValue
                   << "- listening on all interfaces";
        ListenIp = QHostAddress::Any;
    }

    port = settings.value("Port", 7777).toUInt();
    settings.endGroup();
}

void HtraProxyServer::processHtraCmd(const QByteArray &packet, QTcpSocket *clientSocket) {
    const QByteArray reply = HtraProtocol::processCommand(
        packet,
        m_device,
        [this](quint8 cmdId) {
            switch(cmdId) {
                case HTRA_CMD::RF1: RFprocessor->setRF1(); break;
                case HTRA_CMD::RF2: RFprocessor->setRF2(); break;
                case HTRA_CMD::RF3: RFprocessor->setRF3(); break;
                case HTRA_CMD::RF4: RFprocessor->setRF4(); break;
                case HTRA_CMD::RFoff: RFprocessor->RFoff(); break;
            }
        });
    sendReply(clientSocket, reply);
}

void HtraProxyServer::onNewConnection() {
    while(server->hasPendingConnections()) {
        QTcpSocket *clientSocket = server->nextPendingConnection();
        QString clientIp = clientSocket->peerAddress().toString();

        // Преобразование IPv4-mapped IPv6 в обычный IPv4
        if(clientSocket->peerAddress().protocol() == QAbstractSocket::IPv6Protocol &&
                clientIp.startsWith("::ffff:")) {
            clientIp = clientIp.mid(7); // Deleting "::ffff:"
        }

        qDebug() << "New client connected from IP -> " + clientIp;

        connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onDataReady()));
        connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()));
        connect(clientSocket, &QTcpSocket::disconnected, this, [this, clientSocket]() {
            clientBuffers.remove(clientSocket);
        });
    }
}
