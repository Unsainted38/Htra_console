#ifndef HTRATELEMETRYSERVER_H
#define HTRATELEMETRYSERVER_H

#include <telemetry/tcp_telemetry_server.h>
#include <devices/i_htra_device.h>
#include <dto/htra_telemetry_data.h>


class HtraTelemetryServer final : public TcpTelemetryServer {
    Q_OBJECT
    const QString &fileName;
    const QString &section;
    int period;
public:
    explicit HtraTelemetryServer(
        const QString &fileName,
        const QString &section,
        int period,
        ITelemetryPacketSource &packetsource,
        QObject *parent = 0);
signals:
};

#endif // HTRATELEMETRYSERVER_H
