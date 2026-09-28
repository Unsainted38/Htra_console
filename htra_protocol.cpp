#include "htra_protocol.h"

#include "devices/i_htra_device.h"

#include <QDataStream>
#include <QIODevice>

namespace {

quint8 expectedPayloadLength(quint8 cmdId)
{
    switch(cmdId) {
        case HTRA_CMD::CENTER_FREQ:
        case HTRA_CMD::LEVEL:
        case HTRA_CMD::SPAN:
        case HTRA_CMD::RBW:
        case HTRA_CMD::VBW:
        case HTRA_CMD::PICK_SEARCH_CENTER:
        case HTRA_CMD::PICK_SEARCH_WIDTH:
            return 4;

        case HTRA_CMD::PICK:
        case HTRA_CMD::PICK_SEARCH_TYPE:
        case HTRA_CMD::PICK_SEARCH_FULL_SPAN:
        case HTRA_CMD::RF1:
        case HTRA_CMD::RF2:
        case HTRA_CMD::RF3:
        case HTRA_CMD::RF4:
        case HTRA_CMD::RFoff:
            return 1;

        default:
            return 0;
    }
}

QByteArray floatResponse(quint8 cmdId, double value)
{
    QByteArray response;
    QDataStream out(&response, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setFloatingPointPrecision(QDataStream::SinglePrecision);
    out << HTRA_HEADER << cmdId << quint8(4) << static_cast<float>(value);
    return response;
}

QByteArray byteResponse(quint8 cmdId, quint8 value)
{
    QByteArray response;
    QDataStream out(&response, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);
    out << HTRA_HEADER << cmdId << quint8(1) << value;
    return response;
}

} // namespace

bool HtraProtocol::takePacket(QByteArray &buffer, QByteArray &packet)
{
    while(true) {
        const int headerIndex = buffer.indexOf(char(HTRA_HEADER));
        if(headerIndex < 0) {
            buffer.clear();
            return false;
        }

        if(headerIndex > 0) {
            buffer.remove(0, headerIndex);
        }

        if(buffer.size() < 3) {
            return false;
        }

        const auto cmdId = static_cast<quint8>(buffer.at(1));
        const auto payloadLength = static_cast<quint8>(buffer.at(2));
        const quint8 expectedLength = expectedPayloadLength(cmdId);
        if(expectedLength == 0 || payloadLength != expectedLength) {
            buffer.remove(0, 1);
            continue;
        }

        const int packetLength = 3 + payloadLength;
        if(buffer.size() < packetLength) {
            return false;
        }

        packet = buffer.left(packetLength);
        buffer.remove(0, packetLength);
        return true;
    }
}

QByteArray HtraProtocol::processCommand(const QByteArray &packet,
                                        IHtraDevice &device,
                                        const RfCommandHandler &rfHandler)
{
    if(packet.size() < 3 || static_cast<quint8>(packet.at(0)) != HTRA_HEADER) {
        return {};
    }

    const auto cmdId = static_cast<quint8>(packet.at(1));
    const auto payloadLength = static_cast<quint8>(packet.at(2));
    const quint8 expectedLength = expectedPayloadLength(cmdId);
    if(expectedLength == 0 || payloadLength != expectedLength ||
            packet.size() != 3 + payloadLength) {
        return {};
    }

    QByteArray payload = packet.mid(3);
    QDataStream in(&payload, QIODevice::ReadOnly);
    in.setByteOrder(QDataStream::LittleEndian);

    quint32 value = 0;
    if(payloadLength == 4) {
        in >> value;
    } else {
        quint8 byteValue = 0;
        in >> byteValue;
        value = byteValue;
    }

    if(in.status() != QDataStream::Ok) {
        return {};
    }

    switch(cmdId) {
        case HTRA_CMD::CENTER_FREQ:
            device.onSetCenter(value);
            return floatResponse(cmdId, device.centerFreq());

        case HTRA_CMD::LEVEL:
            device.onSetLevel(value);
            return floatResponse(cmdId, device.level());

        case HTRA_CMD::SPAN:
            device.onSetSpan(value);
            return floatResponse(cmdId, device.span());

        case HTRA_CMD::RBW:
            device.onSetRbw(value);
            return floatResponse(cmdId, device.rbw());

        case HTRA_CMD::VBW:
            device.onSetVbw(value);
            return floatResponse(cmdId, device.vbw());

        case HTRA_CMD::PICK:
            return floatResponse(cmdId, device.pick());

        case HTRA_CMD::PICK_SEARCH_TYPE:
            device.onSetPickSearchType(static_cast<quint8>(value));
            return floatResponse(cmdId, device.pickSearchType());

        case HTRA_CMD::PICK_SEARCH_CENTER:
            device.onSetPickSearchCenter(value);
            return floatResponse(cmdId, device.pickSearchCenter());

        case HTRA_CMD::PICK_SEARCH_WIDTH:
            device.onSetPickSearchWidth(value);
            return floatResponse(cmdId, device.pickSearchWidth());

        case HTRA_CMD::PICK_SEARCH_FULL_SPAN:
            device.onSetPickSearchFullSpan();
            return byteResponse(cmdId, 1);

        case HTRA_CMD::RF1:
        case HTRA_CMD::RF2:
        case HTRA_CMD::RF3:
        case HTRA_CMD::RF4:
        case HTRA_CMD::RFoff:
            if(rfHandler) {
                rfHandler(cmdId);
            }
            return byteResponse(cmdId,
                                cmdId == HTRA_CMD::RFoff ? 0 : cmdId - 0x10);
    }

    return {};
}
