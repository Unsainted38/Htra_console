greaterThan(QT_MAJOR_VERSION, 4) {
    QT += serialport widgets
} else {
    CONFIG += serialport
    QT += gui
}
QT       += core network
CONFIG   += console c++17
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

ROOT_APS = spps/data_servers
ROOT_SUBDIRS = spps/data_servers

include(/home/user/develop/host/projects/common/libs/app.pri)
include(/home/user/develop/host/projects/common/libs/serial.pri)

addLib(,network_transport_lib)
addLib(,abstract_rpc_lib)
addLib(,tna_common_rpc_lib)

#INCLUDEPATH +=  /home/user/develop/playground/common_lib \
#                /home/user/develop/playground/UACS
#
#LIBS += -L/home/user/develop/playground/common_lib -lcommon_lib \
#        -L/home/user/develop/playground/UACS/uacslib -luacslib

win64_mingw-g++: {
LIBS += \
  -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/htra_api/ -lhtra_api \
  -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/htra_api/ -llibfftw3-3 \
  -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/htra_api/ -llibliquid
} else {
QMAKE_CXXFLAGS += -std=gnu++17
LIBS += \
    -lpthread \
    -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/linux/ -lfftw3 \
    -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/linux/ -lusb-1.0 \
    -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/linux/ -lliquid \
    -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/linux/ -lhtraapi
}

message($$LIBS)

SOURCES += \
        hrtta_processor.cpp \
        htra_proxy_server.cpp \
        main.cpp \
        network_transport/abstract_network_transport.cpp \
        network_transport/abstract_network_transport_factory.cpp \
        network_transport/serial_transport.cpp \
        network_transport/tcp_transport.cpp \
        signalhaund_server_rpc_cmd_server.cpp \
        signalhaund_server_rpc_last_command_loger.cpp \
        signalhound_server_main_timer.cpp \
        signalhound_telemetry_server.cpp \
        switcher_processor.cpp

HEADERS += \
    hrtta_processor.h \
    htra_api.h \
    htra_proxy_server.h \
    network_transport/abstract_network_transport.h \
    network_transport/abstract_network_transport_factory.h \
    network_transport/network_transport_locker.h \
    network_transport/serial_transport.h \
    network_transport/tcp_transport.h \
    signalhaund_server_rpc_cmd_server.h \
    signalhaund_server_rpc_last_command_loger.h \
    signalhound_server_main_timer.h \
    signalhound_telemetry_server.h \
    switcher_processor.h
