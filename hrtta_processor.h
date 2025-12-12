#ifndef THRTTAPROCESSOR_H
#define THRTTAPROCESSOR_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QVector>
#include <memory>

#include "network/rpc/devices/sh_rpc_proxy_lib/command/sa_rpc_types.h"

#include "htra_api.h"

class THrttaProcessor : public QObject {
    Q_OBJECT
public:
    explicit THrttaProcessor(QObject *parent = nullptr);
    double centerFreq();
    double level();
    double span();
    double rbw();
    double vbw();
    uint32_t sweepCount();
    QVector<float> getMinSweep();
    uint8_t pickSearchType();
    double pickSearchCenter();
    double pickSearchWidth();
    double pick();
    double perTry();
signals:
    void translateDataReady();
public slots:
    void onOpenCmd(quint64 transportId);
    void onOpenSerialCmd(quint64 transportId, uint32_t serial);
    void onCloseCmd(quint64 transportId);
    void onSetCenter(quint64 transportId, uint64_t center);
    void onSetLevel(quint64 transportId, uint64_t level);
    void onSetSpan(quint64 transportId, uint64_t span);
    void onSetRbw(quint64 transportId, uint64_t rbw);
    void onSetVbw(quint64 transportId, uint64_t vbw);
    void onSetPickSearchType(quint64 transportId, uint8_t type);
    void onSetPickSearchCenter(quint64 transportId, uint64_t center);
    void onSetPickSearchWidth(quint64 transportId, uint64_t width);
    void onSetPickSearchFullSpan(quint64 transportId);
private slots:
    void onReconnectTimer();
    void onWorkTimer();
private:
    bool m_connected;

    QTimer *m_ReconnectTimer;
    QTimer *m_WorkTimer;

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
    double getSimpleMaximum();
    double getIntegralMaximum();
};

#endif // THRTTAPROCESSOR_H
