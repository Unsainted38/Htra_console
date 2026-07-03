#include "htra_telemetry_server.h"
#include <QDebug>

HtraTelemetryServer::HtraTelemetryServer(
    const QString &fileName,
    const QString &section,
    uint16_t timeout,
    bool startFlag,
    QObject *parent) :
        QObject(parent),
        fileName(fileName),
        section(section),
        timeout(timeout),
        startFlag(startFlag),
        m_processor(0) {
}

void HtraTelemetryServer::setHtraProcessor(HtraProcessor *processor) {
    m_processor = processor;
}

void HtraTelemetryServer::sendTelemetry() {
    if(m_processor == 0) {
        return;
    }

    //m_telemetryServer->telemetryPacketBegin();
    bool online = true;

    if(m_processor->getMinSweep().count() <= 0) {
        qDebug() << "Empty array!";
        return;
    }

    QVector<float> vector;
    vector.append(10.0);
    vector.append(12.0);
    // (*m_telemetryServer) << online
    //                      << m_processor->centerFreq()
    //                      << m_processor->level()
    //                      << m_processor->span()
    //                      << m_processor->rbw()
    //                      << m_processor->vbw()
    //                      //<< m_processor->getMinSweep()
    //                      << m_processor->pickSearchType()
    //                      << m_processor->pickSearchCenter()
    //                      << m_processor->pickSearchWidth()
    //                      << m_processor->pick();


    // m_telemetryServer->telemetryPacketEnd();
}
