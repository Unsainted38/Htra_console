include($${_PRO_FILE_PWD_}/../playground/common_lib/common_lib.pri)

QT       += core network
CONFIG   += console c++17
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win64_mingw-g++: {
CONFIG -= htra_mock
LIBS += \
  -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/htra_api/ -lhtra_api \
  -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/htra_api/ -llibfftw3-3 \
  -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/htra_api/ -llibliquid
}
linux {
CONFIG -= htra_mock
LIBS += \
    -lpthread \
    -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/linux/ -lfftw3 \
    -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/linux/ -lusb-1.0 \
    -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/linux/ -lliquid \
    -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/linux/ -lhtraapi
}

macx {
    INCLUDEPATH += /opt/homebrew/include
    LIBS += -L/opt/homebrew/lib -lliquid
    CONFIG += htra_mock
}

contains(CONFIG, htra_mock) {
    DEFINES += HTRA_MOCK

    message("Build without libhtraapi: MOCK mode enabled")
} else {
    message("Build with real libhtraapi")

    SOURCES += \
        htra_device.cpp

    HEADERS += \
        htra_device.h
}

SOURCES += \
        builders/htra_packet_builder.cpp \
        devices/mock_htra_device.cpp \
        htra_proxy_server.cpp \
        htra_server_main_timer.cpp \
        main.cpp \
        providers/htra_telemetry_provider.cpp \
        switcher_processor.cpp \
        telemetry/htra_telemetry_server.cpp

HEADERS += \
    builders/htra_packet_builder.h \
    devices/i_htra_device.h \
    devices/mock_htra_device.h \
    dto/htra_telemetry_data.h \
    htra_api.h \
    htra_proxy_server.h \
    htra_server_main_timer.h \
    providers/htra_telemetry_provider.h \
    switcher_processor.h \
    telemetry/htra_telemetry_server.h

