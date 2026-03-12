#include "htra_proxy_server.h"

HtraProxyServer::HtraProxyServer(QString configPath, QString section, QObject *parent)
    : QObject(parent),
      configPath(configPath),
      section(section) {
    loadConfig();
    server = new QTcpServer(this);

    RFprocessor = new SwitcherProcessor(QCoreApplication::applicationDirPath() + "/transport/config.ini", "ArduinoRFSwitcher");

    if(server->listen(QHostAddress::Any, port)) {
        qDebug() << name << "started on ip" << ServerAddress.toString() << ":" << port;
    } else {
        qDebug() << name << "start failed on ip" << ServerAddress.toString() << ":" << port;
    }

    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void HtraProxyServer::onDataReady() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());

    if(clientSocket) {
        currentClient = clientSocket;
        buffer.append(currentClient->readAll());

        while(ParseData(buffer)) {
            continue;
        }
    }
}


void HtraProxyServer::sendReply(QByteArray reply) {
    QString clientIp = currentClient->peerAddress().toString();

    if(currentClient->peerAddress().protocol() == QAbstractSocket::IPv6Protocol &&
            clientIp.startsWith("::ffff:")) {
        clientIp = clientIp.mid(7); // Deleting "::ffff:"
    }

    currentClient->write(reply);
}

void HtraProxyServer::setHtraProcessor(HtraProcessor *implement) {
    processor = implement;
}


void HtraProxyServer::loadConfig() {
    QSettings settings(configPath, QSettings::IniFormat);
    settings.beginGroup(section);
    ServerAddress = QHostAddress(settings.value("HostIp", QHostAddress::LocalHost).toString());
    ListenIp = QHostAddress(settings.value("ListenIp", QHostAddress::Any).toString());
    port = settings.value("Port", 7777).toUInt();
    name = settings.value("Name", "tcp_proxy").toString();
    settings.endGroup();
}

bool HtraProxyServer::ParseData(QByteArray &data) {
    //qDebug() << "Data:" << data.toHex();
    int headerIndex = data.indexOf(HEADER);

    if(headerIndex < 0) {
        return false;
    }

    data.remove(0, headerIndex);
    headerIndex = 0;

    if(data.size() < 3) {
        return false;
    }

    quint8 packetLength = data[2];

    if(data.size() < packetLength + 3) {
        return false;
    }

    QByteArray packet = data.mid(headerIndex, packetLength + 3);
    emit translateLastPacket(packet.toHex());
    //qDebug() << "Packet:" << packet.toHex();
    data.remove(data.indexOf(packet), packet.size());
    ProcessHtraCmd(packet);
    return true;
}

void HtraProxyServer::ProcessHtraCmd(QByteArray packet) {
    QDataStream in(&packet, QIODevice::ReadOnly);
    in.setByteOrder(QDataStream::LittleEndian);
    in.setFloatingPointPrecision(QDataStream::SinglePrecision);
    quint8 header;
    quint8 length;
    quint8 cmdId;
    quint64 value;
    in >> header
       >> cmdId
       >> length;


    if(length > 1) {
        quint32 v;
        in >> v;
        value = static_cast<quint32>(v);
    } else {
        quint8 v;
        in >> v;
        value = static_cast<quint8>(v);
    }


    switch(cmdId) {
        case HTRA_CMD::CENTER_FREQ:
            processor->onSetCenter(transportId, value);
            break;

        case HTRA_CMD::LEVEL:
            processor->onSetLevel(transportId, value);
            break;

        case HTRA_CMD::PICK:

            break;

        case HTRA_CMD::PICK_SEARCH_CENTER:
            processor->onSetPickSearchCenter(transportId, value);
            break;

        case HTRA_CMD::PICK_SEARCH_FULL_SPAN:
            processor->onSetPickSearchFullSpan(transportId);
            break;

        case HTRA_CMD::PICK_SEARCH_TYPE:
            processor->onSetPickSearchType(transportId, value);
            break;

        case HTRA_CMD::PICK_SEARCH_WIDTH:
            processor->onSetPickSearchWidth(transportId, value);
            break;

        case HTRA_CMD::RBW:
            processor->onSetRbw(transportId, value);
            break;

        case HTRA_CMD::SPAN:
            processor->onSetSpan(transportId, value);
            break;

        case HTRA_CMD::VBW:
            processor->onSetVbw(transportId, value);
            break;

        case HTRA_CMD::RF1:
            RFprocessor->setRF1();
            break;

        case HTRA_CMD::RF2:
            RFprocessor->setRF2();
            break;

        case HTRA_CMD::RF3:
            RFprocessor->setRF3();
            break;

        case HTRA_CMD::RF4:
            RFprocessor->setRF4();
            break;

        case HTRA_CMD::RFoff:
            RFprocessor->RFoff();
            break;
    }

    makeResponse(cmdId);
}

void HtraProxyServer::ProcessSwitcherCmd(QByteArray packet) {

}
void HtraProxyServer::makeResponse(quint8 cmdId) {
    QByteArray reply;
    QDataStream out(&reply, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);
    out << HEADER
        << cmdId;

    switch(cmdId) {
        case HTRA_CMD::CENTER_FREQ:
            out << (quint8)4;
            out << static_cast<float>(processor->centerFreq());
            break;

        case HTRA_CMD::LEVEL:
            out << (quint8)4;
            out << static_cast<float>(processor->level());
            break;

        case HTRA_CMD::PICK:
            out << (quint8)4;
            out << static_cast<float>(processor->pick());
            break;

        case HTRA_CMD::PICK_SEARCH_CENTER:
            out << (quint8)4;
            out << static_cast<float>(processor->pickSearchCenter());
            break;

        case HTRA_CMD::PICK_SEARCH_FULL_SPAN:

            break;

        case HTRA_CMD::PICK_SEARCH_TYPE:
            out << (quint8)4;
            out << static_cast<float>(processor->pickSearchType());
            break;

        case HTRA_CMD::PICK_SEARCH_WIDTH:
            out << (quint8)4;
            out << static_cast<float>(processor->pickSearchWidth());
            break;

        case HTRA_CMD::RBW:
            out << (quint8)4;
            out << static_cast<float>(processor->rbw());
            break;

        case HTRA_CMD::SPAN:
            out << (quint8)4;
            out << static_cast<float>(processor->span());
            break;

        case HTRA_CMD::VBW:
            out << (quint8)4;
            out << static_cast<float>(processor->vbw());
            break;

        case HTRA_CMD::RF1:
            out << (quint8)1;
            out << (quint8)0x01;
            break;

        case HTRA_CMD::RF2:
            out << (quint8)1;
            out << (quint8)0x02;
            break;

        case HTRA_CMD::RF3:
            out << (quint8)1;
            out << (quint8)0x03;
            break;

        case HTRA_CMD::RF4:
            out << (quint8)1;
            out << (quint8)0x04;
            break;

        case HTRA_CMD::RFoff:
            out << (quint8)1;
            out << (quint8)0x00;
            break;
    }

    //qDebug() << reply.toHex();
    sendReply(reply);
}

void HtraProxyServer::onNewConnection() {
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
}
