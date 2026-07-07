#include "htra_telemetry_provider.h"

HtraTelemetryProvider::HtraTelemetryProvider(const IHtraDevice &device)
    : m_device(device){}

HtraTelemetryData HtraTelemetryProvider::currentData() const
{
    HtraTelemetryData data;
    data.isOnline = m_device.isOnline();
    data.centerFreq = m_device.centerFreq();
    data.level = m_device.level();
    data.span = m_device.span();
    data.rbw = m_device.rbw();
    data.vbw = m_device.vbw();
    data.pickSearchType = m_device.pickSearchType();
    data.pickSearchCenter = m_device.pickSearchCenter();
    data.pickSearchWidth = m_device.pickSearchWidth();
    data.pick = m_device.pick();
    return data;
}
