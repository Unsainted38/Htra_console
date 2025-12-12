#ifndef SWITCHERPROCESSOR_H
#define SWITCHERPROCESSOR_H

#include <QObject>
#include <QCoreApplication>
#include <QDataStream>
#include <QIODevice>

#include <network_transport/abstract_network_transport.h>
#include <network_transport/abstract_network_transport_factory.h>

class SwitcherProcessor : public QObject {
    Q_OBJECT
    AbstractNetworkTransport *transport;
public:
    explicit SwitcherProcessor(QString configPath, QString section, QObject *parent = nullptr);
    void setRF1();
    void setRF2();
    void setRF3();
    void setRF4();
    void RFoff();
    QString mode = "RFoff";
signals:
private:
    void sendCmd(quint8 cmdId);
private slots:
    void OnGetReply(QByteArray);
};

#endif // SWITCHERPROCESSOR_H
