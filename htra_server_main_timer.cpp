#include "htra_server_main_timer.h"


HtraServerMainTimer::HtraServerMainTimer(
    IHtraDevice &device,
    QObject *parent) :
    QObject(parent),
    m_device(device),
    provider(m_device),
    builder(),
    packetSource(builder, provider) {

    htraTelemetryServer = new HtraTelemetryServer(
        QCoreApplication::applicationDirPath() +
        "/etc/client_server/config.ini",
        "HtraTelemetryServer",
        100,
        packetSource
    );
    proxyServer = new HtraProxyServer(
        QCoreApplication::applicationDirPath() +
        "/etc/client_server/config.ini",
        "HtraProxyServer",
        m_device);
    connect(&m_device, SIGNAL(translateDataReady()), htraTelemetryServer, SLOT(sendTelemetry()));

    m_loggerTimer = new QTimer;
    m_loggerTimer->setInterval(250);
    connect(m_loggerTimer, SIGNAL(timeout()), SLOT(onLogerTimer()));
    m_loggerTimer->start();
}

void HtraServerMainTimer::onLogerTimer() {

    QString text;

    text += "--------------------------------------\n";
    text += QString::asprintf("Center freq      : %f\n", m_device.centerFreq());
    text += QString::asprintf("Level            : %f\n", m_device.level());
    text += QString::asprintf("Span             : %f\n", m_device.span());
    text += QString::asprintf("RBW              : %f\n", m_device.rbw());
    text += QString::asprintf("VBW              : %f\n", m_device.vbw());
    text += QString::asprintf("Count            : %d\n", m_device.sweepCount());

    text += "--------------------------------------\n";
    text += QString::asprintf("Type pick        : %s\n",
                              PowerPickType::getPickSearchType(m_device.pickSearchType())
                                  .toLatin1()
                                  .data());

    text += QString::asprintf("Center pick freq : %f\n", m_device.pickSearchCenter());
    text += QString::asprintf("Width pick       : %f\n", m_device.pickSearchWidth());
    text += QString::asprintf("Pick level       : %f\n", m_device.pick());

    text += "--------------------------------------\n";
    text += QString::asprintf("Per try          : %f\n", m_device.perTry());
    text += "Switch Mode      : " + proxyServer->RFprocessor->mode + "\n";
    text += "--------------------------------------\n";

    QTextStream out(stdout);
    out << text;
    out.flush();
}
