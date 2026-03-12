#ifndef TSIGNALHOUNDTELEMETRYSERVER_H
#define TSIGNALHOUNDTELEMETRYSERVER_H

#include <QObject>
#include <QVector>

#include <stdint.h>

#include "network/network_transport_lib/tcp_telemetry_server_helper.h"

#include "hrtta_processor.h"

class TSignalhoundTelemetryServer : public TTcpTelemetryServerHelper {
    Q_OBJECT
public:
    explicit TSignalhoundTelemetryServer(
        const QString &fileName,
        const QString &section,
        uint16_t timeout = 1000,
        bool startFlag = true,
        QObject *parent = 0);
    void setSignalhoundProcessor(HtraProcessor *signalhoundProcessor);
public slots:
    void sendTelemetry();
signals:
private:
    HtraProcessor *m_signalhoundProcessor;
};

#endif // TSIGNALHOUNDTELEMETRYSERVER_H
