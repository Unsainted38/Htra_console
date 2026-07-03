#ifndef HTRASERVERMAINTIMER_H
#define HTRASERVERMAINTIMER_H

#include <QObject>
#include <QTimer>
#include <QList>
#include "hrtta_processor.h"
#include <htra_proxy_server.h>
#include <htra_telemetry_server.h>
#include <QDebug>
#include <utilities/console_utilities.h>

class HtraServerMainTimer : public QObject {
    Q_OBJECT
public:
    explicit HtraServerMainTimer(QObject *parent = 0);

signals:
private:
    HtraProxyServer *proxyServer;
    QTimer *m_loggerTimer;

    HtraProcessor *m_processor;
    HtraTelemetryServer *htraTelemetryServer;
private slots:
    void onLogerTimer();
};

#endif // HTRASERVERMAINTIMER_H
