#ifndef SIGNALHAUND_SERVER_RPC_CMD_SERVER_H
#define SIGNALHAUND_SERVER_RPC_CMD_SERVER_H

#include <QObject>

#include "network/rpc/abstract_rpc_lib/command/abstractrpcservercommandprocessor.h"
#include "network/rpc/abstract_rpc_lib/server/tcp/abstractrpctcpserver.h"

#include "network/rpc/tna/tna_tirada_rpc_lib/command/tna_tirada_types.h"
#include "network/rpc/tna/tna_common_rpc_lib/command/tna_common_rpc_null_cmd.h"
#include "network/rpc/tna/tna_common_rpc_lib/command/tna_common_rpc_uint8_cmd.h"
#include "network/rpc/tna/tna_common_rpc_lib/command/tna_common_rpc_uint32_cmd.h"
#include "network/rpc/tna/tna_common_rpc_lib/command/tna_common_rpc_uint64_cmd.h"

#include "signalhaund_server_rpc_last_command_loger.h"
#include "hrtta_processor.h".

class TSignalHaundServerRpcCmdServer : public QObject {
    Q_OBJECT
public:
    explicit TSignalHaundServerRpcCmdServer(QObject *parent = 0);
    void connectImplement(HtraProcessor *object);
    void connectImplement(TSignalHoundServerRpcLastCommandLoger *object);
private:
    uint16_t m_port;
    TAbstractRpcServerCommandProcessor *cmdProcessor;
    TAbstractRpcTcpServer *cmdServer;

    TTnaCommonRpcNullCmd *openCmd;
    TTnaCommonRpcUint32Cmd *openSerialCmd;
    TTnaCommonRpcNullCmd *closeCmd;

    TTnaCommonRpcUint64Cmd *setCenterCmd;
    TTnaCommonRpcUint64Cmd *setLevelCmd;
    TTnaCommonRpcUint64Cmd *setSpanCmd;
    TTnaCommonRpcUint64Cmd *setRbwCmd;
    TTnaCommonRpcUint64Cmd *setVbwCmd;

    TTnaCommonRpcUint8Cmd *setPickSearchTypeCmd;
    TTnaCommonRpcUint64Cmd *setPickSearchCenterCmd;
    TTnaCommonRpcUint64Cmd *setPickSearchWidthCmd;
    TTnaCommonRpcNullCmd *setPickSearchFullSpanCmd;
};

#endif // SIGNALHAUND_SERVER_RPC_CMD_SERVER_H
