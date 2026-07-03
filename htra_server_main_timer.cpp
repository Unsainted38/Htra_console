#include "htra_server_main_timer.h"


HtraServerMainTimer::HtraServerMainTimer(
    QObject *parent) :
    QObject(parent) {

    m_processor = new HtraProcessor;

    htraTelemetryServer = new HtraTelemetryServer(
        QCoreApplication::applicationDirPath() +
        "/etc/client_server/config.ini",
        "SignalHtraTelemetryServer"
    );
    proxyServer = new HtraProxyServer(
        QCoreApplication::applicationDirPath() +
        "/etc/client_server/config.ini",
        "BasProxyServer");
    //htraTelemetryServer->stopTelemetry();
    htraTelemetryServer->setHtraProcessor(m_processor);
    proxyServer->setHtraProcessor(m_processor);
    connect(m_processor, SIGNAL(translateDataReady()), htraTelemetryServer, SLOT(sendTelemetry()));

    m_loggerTimer = new QTimer;
    m_loggerTimer->setInterval(250);
    connect(m_loggerTimer, SIGNAL(timeout()), SLOT(onLogerTimer()));
    m_loggerTimer->start();
}

void HtraServerMainTimer::onLogerTimer() {
    clearConsole();
    //qDebug() << (QString().sprintf("Last command : %s", m_lastCommandLoger->lastCommand().toLatin1().data());
    qDebug() << "--------------------------------------";
    qDebug() << QString().asprintf("Center freq      : %f", m_processor->centerFreq());
    qDebug() << QString().asprintf("Level            : %f", m_processor->level());
    qDebug() << QString().asprintf("Span             : %f", m_processor->span());
    qDebug() << QString().asprintf("RBW              : %f", m_processor->rbw());
    qDebug() << QString().asprintf("VBW              : %f", m_processor->vbw());
    qDebug() << QString().asprintf("Count            : %d", m_processor->sweepCount());
    qDebug() << "--------------------------------------";
    qDebug() << QString().asprintf("Type pick        : %s", PowerPickType::getPickSearchType(m_processor->pickSearchType()).toLatin1().data());
    qDebug() << QString().asprintf("Center pick freq : %f", m_processor->pickSearchCenter());
    qDebug() << QString().asprintf("Width pick       : %f", m_processor->pickSearchWidth());
    qDebug() << QString().asprintf("Pick level       : %f", m_processor->pick());
    qDebug() << "--------------------------------------";
    qDebug() << QString().asprintf("Per try          : %f", m_processor->perTry());
    qDebug() << QString("Switch Mode      : " + proxyServer->RFprocessor->mode);
    qDebug() << "--------------------------------------";
    //qDebug() << (QString().sprintf("Type pick        : %s", m_processor;

}
