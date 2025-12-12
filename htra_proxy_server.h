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
#include "hrtta_processor.h"
#include "switcher_processor.h"

const quint8 HEADER = 0x55;

struct HTRA_CMD {
    inline static const quint8 CENTER_FREQ = 0x01;
    inline static const quint8 LEVEL = 0x02;
    inline static const quint8 SPAN = 0x03;
    inline static const quint8 RBW = 0x04;
    inline static const quint8 VBW = 0x05;
    inline static const quint8 PICK = 0x06;
    inline static const quint8 PICK_SEARCH_TYPE = 0x07;
    inline static const quint8 PICK_SEARCH_CENTER = 0x08;
    inline static const quint8 PICK_SEARCH_WIDTH = 0x09;
    inline static const quint8 PICK_SEARCH_FULL_SPAN = 0x10;
    inline static const quint8 RF1 = 0x11;
    inline static const quint8 RF2 = 0x12;
    inline static const quint8 RF3 = 0x13;
    inline static const quint8 RF4 = 0x14;
    inline static const quint8 RFoff = 0x15;
};

class HtraProxyServer : public QObject {
    Q_OBJECT
    QString configPath;
    QString section;
    QTcpServer *server;
    QHostAddress ServerAddress;
    QHostAddress ListenIp;
    quint16 port;
    QString name;
    THrttaProcessor *processor;

    QByteArray buffer;
    QTcpSocket *currentClient;
    quint64 transportId;
public:
    explicit HtraProxyServer(QString configPath, QString section, QObject *parent = nullptr);

    void sendReply(QByteArray reply);
    void setHtraProcessor(THrttaProcessor *implement);
    SwitcherProcessor *RFprocessor;
signals:
    void translateData(QByteArray);
    void translateLastPacket(QByteArray);
private:
    void loadConfig();
    void ParseData(QByteArray data);
    void ProcessHtraCmd(QByteArray packet);
    void ProcessSwitcherCmd(QByteArray packet);
    void makeResponse(quint8 cmdId);
public slots:
    void onNewConnection();
    void onDataReady();
};

#endif // HTRAPROXYSERVER_H
