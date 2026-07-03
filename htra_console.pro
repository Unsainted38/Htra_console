include($${_PRO_FILE_PWD_}/../playground/common_lib/common_lib.pri)

QT       += core network
CONFIG   += console c++17
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win64_mingw-g++: {
LIBS += \
  -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/htra_api/ -lhtra_api \
  -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/htra_api/ -llibfftw3-3 \
  -L$${INC_PATH}/htra_spectrum/HTRA_API/x64/htra_api/ -llibliquid
}
linux {
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
}

SOURCES += \
        hrtta_processor.cpp \
        htra_proxy_server.cpp \
        htra_server_main_timer.cpp \
        htra_telemetry_server.cpp \
        main.cpp \
        switcher_processor.cpp

HEADERS += \
    hrtta_processor.h \
    htra_api.h \
    htra_proxy_server.h \
    htra_server_main_timer.h \
    htra_telemetry_server.h \
    switcher_processor.h
