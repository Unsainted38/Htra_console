#ifndef HTRA_PACKET_BUILDER_H
#define HTRA_PACKET_BUILDER_H

#include <telemetry/i_telemetry_packet_builder.h>
#include <dto/htra_telemetry_data.h>

class HtraPacketBuilder final : public ITelemetryPacketBuilder<HtraTelemetryData>
{
public:

    QByteArray build(const HtraTelemetryData &data) override;
};

#endif // HTRA_PACKET_BUILDER_H
