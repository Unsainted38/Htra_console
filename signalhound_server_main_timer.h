#ifndef TSIGNALHOUNDSERVERMAINTIMER_H
#define TSIGNALHOUNDSERVERMAINTIMER_H

#include <QObject>
#include <QTimer>
#include <QList>

#include "loger/qt_posix_loger_lib/qt_loger_time_locked_facade.h"

#include "hrtta_processor.h"

#include "signalhaund_server_rpc_cmd_server.h"
#include "signalhound_telemetry_server.h"
#include "signalhaund_server_rpc_last_command_loger.h"
#include <htra_proxy_server.h>

class TSignalhoundServerMainTimer : public QObject {
    Q_OBJECT
public:
    explicit TSignalhoundServerMainTimer(quint8 logType, QObject *parent = 0);

signals:
private:
    HtraProxyServer *proxyServer;
    QTimer *m_logerTimer;
    QLoger::QLogerTimeLockedFacade *m_loger;

    THrttaProcessor *m_shProcessor;

    TSignalHaundServerRpcCmdServer *m_rpcCmdServer;
    TSignalhoundTelemetryServer *m_signalhoundTelemetryServer;
    TSignalHoundServerRpcLastCommandLoger *m_lastCommandLoger;
private slots:
    void onLogerTimer();
};

#endif // TSIGNALHOUNDSERVERMAINTIMER_H
