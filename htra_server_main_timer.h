#ifndef HTRASERVERMAINTIMER_H
#define HTRASERVERMAINTIMER_H

#include <QObject>
#include <QTimer>
#include <QDebug>

#include "devices/i_htra_device.h"
#include <htra_proxy_server.h>
#include <telemetry/htra_telemetry_server.h>
#include <telemetry/telemetry_packet_source.h>
#include <providers/htra_telemetry_provider.h>
#include <builders/htra_packet_builder.h>
#include <dto/htra_telemetry_data.h>
#include <utilities/console_utilities.h>

class HtraServerMainTimer : public QObject {
    Q_OBJECT
public:
    explicit HtraServerMainTimer(IHtraDevice &device, QObject *parent = 0);

signals:
private:
    HtraProxyServer *proxyServer;
    QTimer *m_loggerTimer;

    IHtraDevice &m_device;
    HtraTelemetryServer *htraTelemetryServer;

    HtraTelemetryProvider provider;
    HtraPacketBuilder builder;
    TelemetryPacketSource<HtraTelemetryData> packetSource;

private slots:
    void onLogerTimer();
};

#endif // HTRASERVERMAINTIMER_H
