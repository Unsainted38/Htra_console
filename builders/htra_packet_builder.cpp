#include "htra_packet_builder.h"
#include <QByteArray>
#include <QDataStream>
#include <QDateTime>
#include <QIODevice>

QByteArray HtraPacketBuilder::build(const HtraTelemetryData &data)
{
    QByteArray packet;
    quint32 trash = 0;

    QDataStream out(&packet, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setFloatingPointPrecision(QDataStream::SinglePrecision);
    out << trash
        << data.isOnline
        << data.centerFreq
        << data.level
        << data.span
        << data.rbw
        << data.vbw
        << data.pickSearchType
        << data.pickSearchCenter
        << data.pickSearchWidth
        << data.pick;
    return packet;
}
