#include "signalhaund_server_rpc_last_command_loger.h"

#include "network/rpc/devices/sh_rpc_proxy_lib/command/sa_rpc_types.h"

TSignalHoundServerRpcLastCommandLoger::TSignalHoundServerRpcLastCommandLoger(QObject *parent)
    : QObject(parent) {

}

QString TSignalHoundServerRpcLastCommandLoger::lastCommand() {
    return m_lastCommand;
}

void TSignalHoundServerRpcLastCommandLoger::onOpenCmd(quint64 transportId) {
    Q_UNUSED(transportId);
    m_lastCommand = "Open cmd";
}

void TSignalHoundServerRpcLastCommandLoger::onOpenSerialCmd(
    quint64 transportId,
    uint32_t serial) {
    Q_UNUSED(transportId);
    m_lastCommand = "Open serial: " + QString::number(serial) + " cmd";
}

void TSignalHoundServerRpcLastCommandLoger::onCloseCmd(quint64 transportId) {
    Q_UNUSED(transportId);
    m_lastCommand = "Close cmd";
}

void TSignalHoundServerRpcLastCommandLoger::onSetCenter(
    quint64 transportId,
    uint64_t center) {
    Q_UNUSED(transportId);
    m_lastCommand = "Set center: " + QString::number(center) + " cmd";
}

void TSignalHoundServerRpcLastCommandLoger::onSetLevel(
    quint64 transportId,
    uint64_t level) {
    Q_UNUSED(transportId);
    m_lastCommand = "Set level: " + QString::number((int64_t)level) + " cmd";
}

void TSignalHoundServerRpcLastCommandLoger::onSetSpan(
    quint64 transportId,
    uint64_t span) {
    Q_UNUSED(transportId);
    m_lastCommand = "Set span : " + QString::number(span) + " cmd";
}

void TSignalHoundServerRpcLastCommandLoger::onSetRbw(
    quint64 transportId,
    uint64_t rbw) {
    Q_UNUSED(transportId);
    m_lastCommand = "Set rbw: " + QString::number(rbw) + " cmd";
}

void TSignalHoundServerRpcLastCommandLoger::onSetVbw(
    quint64 transportId,
    uint64_t vbw) {
    Q_UNUSED(transportId);
    m_lastCommand = "Set vbw: " + QString::number(vbw) + " cmd";
}

void TSignalHoundServerRpcLastCommandLoger::onSetPickSearchType(
    quint64 transportId,
    uint8_t type) {
    Q_UNUSED(transportId);
    m_lastCommand = "Set pick search type: " +
                    TSaRpcTypes::getPickSearchType(type) + " cmd";
}

void TSignalHoundServerRpcLastCommandLoger::onSetPickSearchCenter(
    quint64 transportId,
    uint64_t center) {
    Q_UNUSED(transportId);
    m_lastCommand = "Set pick search center: " +
                    QString::number(center) + " cmd";
}

void TSignalHoundServerRpcLastCommandLoger::onSetPickSearchWidth(
    quint64 transportId,
    uint64_t width) {
    Q_UNUSED(transportId);
    m_lastCommand = "Set pick search width: " +
                    QString::number(width) + " cmd";
}

void TSignalHoundServerRpcLastCommandLoger::onSetPickSearchFullSpan(quint64 transportId) {
    Q_UNUSED(transportId);
    m_lastCommand = "Set pick search full span cmd";
}

void TSignalHoundServerRpcLastCommandLoger::onDataRecieved(QByteArray data) {
    m_lastCommand = QString::fromUtf8(data);
}
