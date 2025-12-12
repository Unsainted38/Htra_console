#include "signalhaund_server_rpc_cmd_server.h"

#include <QMap>
#include <QSettings>

#include "network/rpc/tna/tna_tirada_rpc_lib/command/tna_tirada_types.h"

#include "algorithm/config_path_helper.h"

TSignalHaundServerRpcCmdServer::TSignalHaundServerRpcCmdServer(QObject *parent)
    : QObject(parent) {

    QSettings settings(
        getRootAppsPath() +
        "/etc/client_server/config.ini",
        QSettings::IniFormat
    );
    settings.beginGroup("SignalhoundRpcServer");
    m_port = settings.value("Port", 4400).toUInt();
    settings.endGroup();

    cmdProcessor = new TAbstractRpcServerCommandProcessor;

    QMap<QString, QVariant> settingsMap;
    settingsMap["Port"] =  m_port;
    cmdServer = new TAbstractRpcTcpServer(cmdProcessor);
    cmdServer->start(settingsMap);

    openCmd = new TTnaCommonRpcNullCmd(TNATIRADA::CMD_OPEN_SH_CMD);
    openSerialCmd = new TTnaCommonRpcUint32Cmd(TNATIRADA::CMD_OPEN_SH_SERIAL_CMD);
    closeCmd = new TTnaCommonRpcNullCmd(TNATIRADA::CMD_CLOSE_SH_CMD);

    setCenterCmd = new TTnaCommonRpcUint64Cmd(TNATIRADA::CMD_SET_SH_CENTER_CMD);
    setLevelCmd = new TTnaCommonRpcUint64Cmd(TNATIRADA::CMD_SET_SH_LEVEL_CMD);
    setSpanCmd = new TTnaCommonRpcUint64Cmd(TNATIRADA::CMD_SET_SH_SPAN_CMD);
    setRbwCmd = new TTnaCommonRpcUint64Cmd(TNATIRADA::CMD_SET_SH_RBW_CMD);
    setVbwCmd = new TTnaCommonRpcUint64Cmd(TNATIRADA::CMD_SET_SH_VBW_CMD);

    setPickSearchTypeCmd = new TTnaCommonRpcUint8Cmd(TNATIRADA::CMD_SET_SH_TYPE_PICK_SEARCH_CMD);
    setPickSearchCenterCmd = new TTnaCommonRpcUint64Cmd(TNATIRADA::CMD_SET_SH_CENTER_PICK_SEARCH_CMD);
    setPickSearchWidthCmd = new TTnaCommonRpcUint64Cmd(TNATIRADA::CMD_SET_SH_WIDTH_PICK_SEARCH_CMD);
    setPickSearchFullSpanCmd = new TTnaCommonRpcNullCmd(TNATIRADA::CMD_SET_SH_FULL_SPAN_PICK_SEARCH_CMD);

    cmdProcessor->addCommand(openCmd);
    cmdProcessor->addCommand(openSerialCmd);
    cmdProcessor->addCommand(closeCmd);
    cmdProcessor->addCommand(setCenterCmd);
    cmdProcessor->addCommand(setLevelCmd);
    cmdProcessor->addCommand(setSpanCmd);
    cmdProcessor->addCommand(setRbwCmd);
    cmdProcessor->addCommand(setVbwCmd);
    cmdProcessor->addCommand(setPickSearchTypeCmd);
    cmdProcessor->addCommand(setPickSearchCenterCmd);
    cmdProcessor->addCommand(setPickSearchWidthCmd);
    cmdProcessor->addCommand(setPickSearchFullSpanCmd);
}

void TSignalHaundServerRpcCmdServer::connectImplement(THrttaProcessor *object) {
    connect(
        openCmd, SIGNAL(translateNULL(quint64)),
        object,  SLOT(onOpenCmd(quint64))
    );
    connect(
        openSerialCmd, SIGNAL(translateUint32(quint64, uint32_t)),
        object,  SLOT(onOpenSerialCmd(quint64, uint32_t))
    );
    connect(
        closeCmd, SIGNAL(translateNULL(quint64)),
        object,  SLOT(onCloseCmd(quint64))
    );
    connect(
        setCenterCmd, SIGNAL(translateUint64(quint64, uint64_t)),
        object,  SLOT(onSetCenter(quint64, uint64_t))
    );
    connect(
        setLevelCmd, SIGNAL(translateUint64(quint64, uint64_t)),
        object,  SLOT(onSetLevel(quint64, uint64_t))
    );
    connect(
        setSpanCmd, SIGNAL(translateUint64(quint64, uint64_t)),
        object,  SLOT(onSetSpan(quint64, uint64_t))
    );
    connect(
        setRbwCmd, SIGNAL(translateUint64(quint64, uint64_t)),
        object,  SLOT(onSetRbw(quint64, uint64_t))
    );
    connect(
        setVbwCmd, SIGNAL(translateUint64(quint64, uint64_t)),
        object,  SLOT(onSetVbw(quint64, uint64_t))
    );
    connect(
        setPickSearchTypeCmd, SIGNAL(translateUint8(quint64, uint8_t)),
        object, SLOT(onSetPickSearchType(quint64, uint8_t))
    );
    connect(
        setPickSearchCenterCmd, SIGNAL(translateUint64(quint64, uint64_t)),
        object, SLOT(onSetPickSearchCenter(quint64, uint64_t))
    );
    connect(
        setPickSearchWidthCmd, SIGNAL(translateUint64(quint64, uint64_t)),
        object, SLOT(onSetPickSearchWidth(quint64, uint64_t))
    );
    connect(
        setPickSearchFullSpanCmd, SIGNAL(translateNULL(quint64)),
        object, SLOT(onSetPickSearchFullSpan(quint64))
    );
}

void TSignalHaundServerRpcCmdServer::connectImplement(TSignalHoundServerRpcLastCommandLoger *object) {
    connect(
        openCmd, SIGNAL(translateNULL(quint64)),
        object,  SLOT(onOpenCmd(quint64))
    );
    connect(
        openSerialCmd, SIGNAL(translateUint32(quint64, uint32_t)),
        object,  SLOT(onOpenSerialCmd(quint64, uint32_t))
    );
    connect(
        closeCmd, SIGNAL(translateNULL(quint64)),
        object,  SLOT(onCloseCmd(quint64))
    );
    connect(
        setCenterCmd, SIGNAL(translateUint64(quint64, uint64_t)),
        object,  SLOT(onSetCenter(quint64, uint64_t))
    );
    connect(
        setLevelCmd, SIGNAL(translateUint64(quint64, uint64_t)),
        object,  SLOT(onSetLevel(quint64, uint64_t))
    );
    connect(
        setSpanCmd, SIGNAL(translateUint64(quint64, uint64_t)),
        object,  SLOT(onSetSpan(quint64, uint64_t))
    );
    connect(
        setRbwCmd, SIGNAL(translateUint64(quint64, uint64_t)),
        object,  SLOT(onSetRbw(quint64, uint64_t))
    );
    connect(
        setVbwCmd, SIGNAL(translateUint64(quint64, uint64_t)),
        object,  SLOT(onSetVbw(quint64, uint64_t))
    );
    connect(
        setPickSearchTypeCmd, SIGNAL(translateUint8(quint64, uint8_t)),
        object, SLOT(onSetPickSearchType(quint64, uint8_t))
    );
    connect(
        setPickSearchCenterCmd, SIGNAL(translateUint64(quint64, uint64_t)),
        object, SLOT(onSetPickSearchCenter(quint64, uint64_t))
    );
    connect(
        setPickSearchWidthCmd, SIGNAL(translateUint64(quint64, uint64_t)),
        object, SLOT(onSetPickSearchWidth(quint64, uint64_t))
    );
    connect(
        setPickSearchFullSpanCmd, SIGNAL(translateNULL(quint64)),
        object, SLOT(onSetPickSearchFullSpan(quint64))
    );
}
