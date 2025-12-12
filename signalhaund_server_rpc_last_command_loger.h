#ifndef TSIGNALHOUNDSERVERRPCLASTCOMMANDLOGER_H
#define TSIGNALHOUNDSERVERRPCLASTCOMMANDLOGER_H

#include <QObject>
#include <QString>

#include <stdint.h>

class TSignalHoundServerRpcLastCommandLoger : public QObject {
    Q_OBJECT
public:
    explicit TSignalHoundServerRpcLastCommandLoger(QObject *parent = 0);
    QString lastCommand();
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

    void onDataRecieved(QByteArray data);
private:
    QString m_lastCommand;
};

#endif // TSIGNALHOUNDSERVERRPCLASTCOMMANDLOGER_H
