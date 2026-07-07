#ifndef HTRA_TELEMETRY_PROVIDER_H
#define HTRA_TELEMETRY_PROVIDER_H

#include <telemetry/i_telemetry_provider.h>
#include <dto/htra_telemetry_data.h>
#include <devices/i_htra_device.h>

class HtraTelemetryProvider final : public ITelemetryProvider<HtraTelemetryData>
{
    const IHtraDevice &m_device;
public:
    HtraTelemetryProvider(const IHtraDevice &device);

    HtraTelemetryData currentData() const override;
};

#endif // HTRA_TELEMETRY_PROVIDER_H
