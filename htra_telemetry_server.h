#ifndef HTRATELEMETRYSERVER_H
#define HTRATELEMETRYSERVER_H

#include <QObject>
#include <QVector>

#include <stdint.h>

#include "hrtta_processor.h"

class HtraTelemetryServer : public QObject {
    Q_OBJECT
    QString fileName;
    QString section;
    uint16_t timeout;
    bool startFlag = false;
public:
    explicit HtraTelemetryServer(
        const QString &fileName,
        const QString &section,
        uint16_t timeout = 1000,
        bool startFlag = true,
        QObject *parent = 0);
    void setHtraProcessor(HtraProcessor *processor);
public slots:
    void sendTelemetry();
signals:
private:
    HtraProcessor *m_processor;
};

#endif // HTRATELEMETRYSERVER_H
