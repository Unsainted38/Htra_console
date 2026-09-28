#ifndef HTRA_PROTOCOL_H
#define HTRA_PROTOCOL_H

#include <QByteArray>
#include <QtGlobal>

#include <functional>

class IHtraDevice;

inline constexpr quint8 HTRA_HEADER = 0x55;

struct HTRA_CMD {
    inline static constexpr quint8 CENTER_FREQ = 0x01;
    inline static constexpr quint8 LEVEL = 0x02;
    inline static constexpr quint8 SPAN = 0x03;
    inline static constexpr quint8 RBW = 0x04;
    inline static constexpr quint8 VBW = 0x05;
    inline static constexpr quint8 PICK = 0x06;
    inline static constexpr quint8 PICK_SEARCH_TYPE = 0x07;
    inline static constexpr quint8 PICK_SEARCH_CENTER = 0x08;
    inline static constexpr quint8 PICK_SEARCH_WIDTH = 0x09;
    inline static constexpr quint8 PICK_SEARCH_FULL_SPAN = 0x10;
    inline static constexpr quint8 RF1 = 0x11;
    inline static constexpr quint8 RF2 = 0x12;
    inline static constexpr quint8 RF3 = 0x13;
    inline static constexpr quint8 RF4 = 0x14;
    inline static constexpr quint8 RFoff = 0x15;
};

namespace HtraProtocol {

using RfCommandHandler = std::function<void(quint8)>;

// Extracts one complete frame and leaves any following frames in buffer.
bool takePacket(QByteArray &buffer, QByteArray &packet);

// Applies a validated command and returns the complete protocol response.
// An empty response means that the frame is malformed or unsupported.
QByteArray processCommand(const QByteArray &packet,
                          IHtraDevice &device,
                          const RfCommandHandler &rfHandler = {});

} // namespace HtraProtocol

#endif // HTRA_PROTOCOL_H
