#ifndef THRTTAPROCESSOR_H
#define THRTTAPROCESSOR_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QVector>

#include <htra_api.h>
#include "devices/i_htra_device.h"

class HtraDevice : public IHtraDevice {
    Q_OBJECT
public:
    explicit HtraDevice(QObject *parent = nullptr);
    double centerFreq() const override;
    double level() const override;
    double span() const override;
    double rbw() const override;
    double vbw() const override;
    uint32_t sweepCount();
    QVector<float> getMinSweep();
    uint8_t pickSearchType() const override;
    double pickSearchCenter() const override;
    double pickSearchWidth() const override;
    double pick() const override;
    double perTry();
    bool isOnline() const override;
signals:
    void translateDataReady();
private slots:
    void onReconnectTimer();
    void onWorkTimer();
    void onReconfigureTimer();
private:
    bool m_connected;

    QTimer *m_ReconnectTimer;
    QTimer *m_WorkTimer;
    QTimer *m_ReconfigureTimer;

    double m_centerFreq;
    double m_level;
    double m_span;
    double m_rbw;
    double m_vbw;

    uint8_t m_pickSearchType;
    double m_pickSearchCenter;
    double m_pickSearchWidth;

    QElapsedTimer m_elapsedTime;

    int Status; //The function return value or error code. Status == 0 indicates no error. For details please check the Appendix 1 in the API Guide document.

    mutable void *Device;             //Device handle. Use the device handle to specify device for manipulating in the API calls. The device handle must be initialized firstly by function Devcie_Open before it to be used.
    DeviceInfo_TypeDef DeviceInfo;                         //device information including device UID, model, firmware version, etc is stored in this structure.
    SWP_Profile_TypeDef SWP_ProfileIn;                    //configure parameters for SWP mode including start/stop frequency, RBW, R.L. etc.
    SWP_Profile_TypeDef SWP_ProfileOut;                   //feedback information including start/stop frequency, RBW, R.L. etc.
    SWP_TraceInfo_TypeDef TraceInfo;                      //feedback information for the current trace including trace points etc.

    int HopIndex = 0;                                                 //Hop index.
    int FrameIndex = 0;                                               //Frame index.
    MeasAuxInfo_TypeDef MeasAuxInfo;                                  //Auxiliary measurement information.

    QVector<double> Frequency;
    QVector<float> PowerSpec_dBm;

    uint64_t m_allEllapsed = 0;
    uint64_t m_count = 0;

    double m_perTry;

    bool reconfigure();
    double getSimpleMaximum() const;
    double getIntegralMaximum() const;

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
};

#endif // THRTTAPROCESSOR_H
