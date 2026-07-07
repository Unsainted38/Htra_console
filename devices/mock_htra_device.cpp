#include "mock_htra_device.h"
#include <utilities/random_utils.h>

MockHtraDevice::MockHtraDevice(QObject *parent)
    : IHtraDevice{parent}
{}


double MockHtraDevice::centerFreq() const
{
    return m_centerFreq;
}

double MockHtraDevice::level() const
{
    return m_level;
}

double MockHtraDevice::span() const
{
    return m_span;
}

double MockHtraDevice::rbw() const
{
    return m_rbw;
}

double MockHtraDevice::vbw() const
{
    return m_vbw;
}

uint8_t MockHtraDevice::pickSearchType() const
{
    return m_pickSearchType;
}

double MockHtraDevice::pickSearchCenter() const
{
    return m_pickSearchCenter;
}

double MockHtraDevice::pickSearchWidth() const
{
    return m_pickSearchWidth;
}

double MockHtraDevice::pick() const
{
    return randomDouble(-70, -60);
}

bool MockHtraDevice::isOnline() const
{
    return m_connected;
}


void MockHtraDevice::onSetCenter(uint64_t center) {
    m_centerFreq = center;
}

void MockHtraDevice::onSetLevel(uint64_t level) {
    m_level = level;
}

void MockHtraDevice::onSetSpan(uint64_t span) {
    m_span = span;
}

void MockHtraDevice::onSetRbw(uint64_t rbw) {
    m_rbw = rbw;
}

void MockHtraDevice::onSetVbw(uint64_t vbw) {
    m_vbw = vbw;
}

void MockHtraDevice::onSetPickSearchType(uint8_t type) {
    m_pickSearchType = type;
}

void MockHtraDevice::onSetPickSearchCenter(uint64_t center) {
    m_pickSearchCenter = center;
}

void MockHtraDevice::onSetPickSearchWidth(uint64_t width) {
    m_pickSearchWidth = width;
}

void MockHtraDevice::onSetPickSearchFullSpan() {
    m_pickSearchCenter = m_centerFreq;
    m_pickSearchWidth = m_span;
}


uint32_t MockHtraDevice::sweepCount()
{
}

QVector<float> MockHtraDevice::getMinSweep()
{
}

double MockHtraDevice::perTry()
{
}
