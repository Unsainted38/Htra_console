#include "signalhound_server_main_timer.h"

#include "algorithm/config_path_helper.h"
#include "network/rpc/devices/sh_rpc_proxy_lib/command/sa_rpc_types.h"


TSignalhoundServerMainTimer::TSignalhoundServerMainTimer(
    quint8 logType,
    QObject *parent) :
    QObject(parent) {
    m_loger = new QLoger::QLogerTimeLockedFacade(
        250,
        1,
        (QLoger::LogViewType)logType
    );

    m_shProcessor = new HtraProcessor;

    m_lastCommandLoger = new TSignalHoundServerRpcLastCommandLoger;

    m_rpcCmdServer = new TSignalHaundServerRpcCmdServer;
    m_rpcCmdServer->connectImplement(m_lastCommandLoger);
    m_rpcCmdServer->connectImplement(m_shProcessor);

    m_signalhoundTelemetryServer = new TSignalhoundTelemetryServer(
        getRootAppsPath() +
        "/etc/client_server/config.ini",
        "SignalhoundTelemetryServer"
    );
    proxyServer = new HtraProxyServer(
        QCoreApplication::applicationDirPath() +
        "/etc/client_server/config.ini",
        "BasProxyServer");
    m_signalhoundTelemetryServer->stopTelemetry();
    m_signalhoundTelemetryServer->setSignalhoundProcessor(m_shProcessor);
    proxyServer->setHtraProcessor(m_shProcessor);
    connect(m_shProcessor, SIGNAL(translateDataReady()), m_signalhoundTelemetryServer, SLOT(sendTelemetry()));
    connect(proxyServer, SIGNAL(translateLastPacket(QByteArray)), m_lastCommandLoger, SLOT(onDataRecieved(QByteArray)));

    m_logerTimer = new QTimer;
    m_logerTimer->setInterval(250);
    connect(m_logerTimer, SIGNAL(timeout()), SLOT(onLogerTimer()));
    m_logerTimer->start();
}

void TSignalhoundServerMainTimer::onLogerTimer() {
    m_loger->clear("Hound");
    m_loger->append(QString().sprintf("Last command : %s", m_lastCommandLoger->lastCommand().toLatin1().data()), "Hound");
    m_loger->append("--------------------------------------", "Hound");
    m_loger->append(QString().sprintf("Center freq      : %f", m_shProcessor->centerFreq()), "Hound");
    m_loger->append(QString().sprintf("Level            : %f", m_shProcessor->level()), "Hound");
    m_loger->append(QString().sprintf("Span             : %f", m_shProcessor->span()), "Hound");
    m_loger->append(QString().sprintf("RBW              : %f", m_shProcessor->rbw()), "Hound");
    m_loger->append(QString().sprintf("VBW              : %f", m_shProcessor->vbw()), "Hound");
    m_loger->append(QString().sprintf("Count            : %d", m_shProcessor->sweepCount()), "Hound");
    m_loger->append("--------------------------------------", "Hound");
    m_loger->append(QString().sprintf("Type pick        : %s", TSaRpcTypes::getPickSearchType(m_shProcessor->pickSearchType()).toLatin1().data()), "Hound");
    m_loger->append(QString().sprintf("Center pick freq : %f", m_shProcessor->pickSearchCenter()), "Hound");
    m_loger->append(QString().sprintf("Width pick       : %f", m_shProcessor->pickSearchWidth()), "Hound");
    m_loger->append(QString().sprintf("Pick level       : %f", m_shProcessor->pick()), "Hound");
    m_loger->append("--------------------------------------", "Hound");
    m_loger->append(QString().sprintf("Per try          : %f", m_shProcessor->perTry()), "Hound");
    m_loger->append(QString("Switch Mode      : " + proxyServer->RFprocessor->mode), "Hound");
    m_loger->append("--------------------------------------", "Hound");
    //m_loger->append(QString().sprintf("Type pick        : %s", m_shProcessor, "Hound");
    m_loger->print();
}
