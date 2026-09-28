#ifndef HTRAPROXYSERVER_H
#define HTRAPROXYSERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>
#include <QSettings>
#include <QDataStream>
#include <QIODevice>
#include <QDebug>
#include <QHash>
#include "devices/i_htra_device.h"
#include "htra_protocol.h"
#include "switcher_processor.h"

class HtraProxyServer : public QObject {
    Q_OBJECT
    QString configPath;
    QString section;
    QTcpServer *server;
    QHostAddress ServerAddress;
    QHostAddress ListenIp;
    quint16 port;
    QString name;
    IHtraDevice &m_device;

    QHash<QTcpSocket *, QByteArray> clientBuffers;
public:
    explicit HtraProxyServer(QString configPath, QString section, IHtraDevice &device, QObject *parent = nullptr);

    void sendReply(QTcpSocket *clientSocket, const QByteArray &reply);
    SwitcherProcessor *RFprocessor;
signals:
    void translateData(QByteArray);
    void translateLastPacket(QByteArray);
private:
    void loadConfig();
    void processHtraCmd(const QByteArray &packet, QTcpSocket *clientSocket);
public slots:
    void onNewConnection();
    void onDataReady();
};

#endif // HTRAPROXYSERVER_H
