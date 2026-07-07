#ifndef I_HTRA_DEVICE_H
#define I_HTRA_DEVICE_H

#include <QObject>

struct PowerPickType {
    static const quint8 SIMPLE_MAXIMUM = 0;
    static const quint8 INTEGRAL_MAXIMUM = 1;

    static QString getPickSearchType(quint8 type) {
        QString res;

        if (type == SIMPLE_MAXIMUM) {
            res = "SIMPLE_MAXIMUM";
        } else if (type == INTEGRAL_MAXIMUM) {
            res = "INTEGRAL_MAXIMUM";
        } else {
            res = "Unknown pick type";
        }

        return res;
    }
};

class IHtraDevice : public QObject {
    Q_OBJECT
public:

    explicit IHtraDevice(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

    virtual ~IHtraDevice() = default;

    virtual double centerFreq() const = 0;
    virtual double level() const = 0;
    virtual double span() const = 0;
    virtual double rbw() const = 0;
    virtual double vbw() const = 0;
    virtual uint32_t sweepCount() = 0;
    virtual QVector<float> getMinSweep() = 0;
    virtual uint8_t pickSearchType() const = 0;
    virtual double pickSearchCenter() const = 0;
    virtual double pickSearchWidth() const = 0;
    virtual double pick() const = 0;
    virtual double perTry() = 0;
    virtual bool isOnline() const = 0;
signals:
    void translateDataReady();
public slots:
    virtual void onSetCenter(uint64_t center) = 0;
    virtual void onSetLevel(uint64_t level) = 0;
    virtual void onSetSpan(uint64_t span) = 0;
    virtual void onSetRbw(uint64_t rbw) = 0;
    virtual void onSetVbw(uint64_t vbw) = 0;

    virtual void onSetPickSearchType(uint8_t type) = 0;
    virtual void onSetPickSearchCenter(uint64_t center) = 0;
    virtual void onSetPickSearchWidth(uint64_t width) = 0;
    virtual void onSetPickSearchFullSpan() = 0;
};

#endif // I_HTRA_DEVICE_H
