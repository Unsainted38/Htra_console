#include "signalhound_telemetry_server.h"

#include "algorithm/config_path_helper.h"

TSignalhoundTelemetryServer::TSignalhoundTelemetryServer(
    const QString &fileName,
    const QString &section,
    uint16_t timeout,
    bool startFlag,
    QObject *parent) :
    TTcpTelemetryServerHelper(
        fileName,
        section,
        timeout,
        startFlag,
        parent),
    m_signalhoundProcessor(0) {
}

void TSignalhoundTelemetryServer::setSignalhoundProcessor(HtraProcessor *signalhoundProcessor) {
    m_signalhoundProcessor = signalhoundProcessor;
}

void TSignalhoundTelemetryServer::sendTelemetry() {
    if(m_signalhoundProcessor == 0) {
        return;
    }

    m_telemetryServer->telemetryPacketBegin();
    bool online = true;

    if(m_signalhoundProcessor->getMinSweep().count() <= 0) {
        qDebug() << "Empty array!";
        return;
    }

    QVector<float> vector;
    vector.append(10.0);
    vector.append(12.0);
    (*m_telemetryServer) << online
                         << m_signalhoundProcessor->centerFreq()
                         << m_signalhoundProcessor->level()
                         << m_signalhoundProcessor->span()
                         << m_signalhoundProcessor->rbw()
                         << m_signalhoundProcessor->vbw()
                         //<< m_signalhoundProcessor->getMinSweep()
                         << m_signalhoundProcessor->pickSearchType()
                         << m_signalhoundProcessor->pickSearchCenter()
                         << m_signalhoundProcessor->pickSearchWidth()
                         << m_signalhoundProcessor->pick();


    m_telemetryServer->telemetryPacketEnd();
}
