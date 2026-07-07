#include "htra_telemetry_server.h"
#include <QDebug>

HtraTelemetryServer::HtraTelemetryServer(
    const QString &fileName,
    const QString &section,
    int period,
    ITelemetryPacketSource &source,
    QObject *parent) :
    TcpTelemetryServer(fileName, section, period, source, parent),
        fileName(fileName),
        section(section) {
}
