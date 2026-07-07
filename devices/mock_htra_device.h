#ifndef MOCK_HTRA_DEVICE_H
#define MOCK_HTRA_DEVICE_H

#include "i_htra_device.h"
#include <QTimer>

class MockHtraDevice : public IHtraDevice
{
    bool m_connected = true;

    double m_centerFreq = 1000000000;
    double m_level = 10;
    double m_span = 1000000;
    double m_rbw = 300;
    double m_vbw = 100;

    uint8_t m_pickSearchType = 0;
    double m_pickSearchCenter = 1000000000;
    double m_pickSearchWidth = 1000000;
public:
    explicit MockHtraDevice(QObject *parent = nullptr);

    double centerFreq() const override;
    double level() const override;
    double span() const override;
    double rbw() const override;
    double vbw() const override;
    uint8_t pickSearchType() const override;
    double pickSearchCenter() const override;
    double pickSearchWidth() const override;
    double pick() const override;
    bool isOnline() const override;
public slots:
    void onSetCenter(uint64_t center) override;
    void onSetLevel(uint64_t level) override;
    void onSetSpan(uint64_t span) override;
    void onSetRbw(uint64_t rbw) override;
    void onSetVbw(uint64_t vbw) override;
    void onSetPickSearchType(uint8_t type) override;
    void onSetPickSearchCenter(uint64_t center) override;
    void onSetPickSearchWidth(uint64_t width) override;
    void onSetPickSearchFullSpan() override;

    // IHtraDevice interface
public:
    uint32_t sweepCount() override;
    QVector<float> getMinSweep() override;
    double perTry() override;
};


#endif // MOCK_HTRA_DEVICE_H
