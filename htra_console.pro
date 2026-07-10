COMMON_LIB_PATH = $$clean_path($$PWD/third_party/common_lib)

!exists($$COMMON_LIB_PATH/common_lib.pri) {
    error("common_lib not found. Run: git submodule update --init --recursive")
}

include($$COMMON_LIB_PATH/common_lib.pri)

QT += core network serialport

CONFIG += console c++17
CONFIG -= app_bundle

# By default the project is built in mock mode.
# Real hardware SDK build must be enabled explicitly:
# qmake "CONFIG+=htra_real" "HTRA_SDK_PATH=/path/to/htra_spectrum" htra_console.pro

contains(CONFIG, htra_real) {
    CONFIG -= htra_mock
} else {
    CONFIG += htra_mock
}

contains(CONFIG, htra_mock) {
    DEFINES += HTRA_MOCK
    message("Build without libhtraapi: MOCK mode enabled")
} else {
    isEmpty(HTRA_SDK_PATH) {
       error("HTRA_SDK_PATH is not set. Example: qmake \"CONFIG+=htra_real\" \"HTRA_SDK_PATH=/opt/htra_spectrum\" htra_console.pro")
    }

    HTRA_SDK_PATH = $$clean_path($$HTRA_SDK_PATH)

    INCLUDEPATH += $$HTRA_SDK_PATH/include

    win32 {
        message("Build with real libhtraapi for Windows")

        HTRA_LIB_PATH = $$HTRA_SDK_PATH/lib/windows/x64

        INCLUDEPATH += $$HTRA_SDK_PATH/include

        LIBS += -L$$HTRA_LIB_PATH

        win32-g++ {
            # MinGW:
            # libhtra_api.a      -> -lhtra_api
            # libfftw3-3.dll.a   -> -lfftw3-3
            # libliquid.dll.a    -> -lliquid
            LIBS += -lhtra_api
            LIBS += -lfftw3-3
            LIBS += -lliquid
        }

        msvc {
            # MSVC:
            # If SDK provides .lib files, link them directly.
            LIBS += $$quote($$HTRA_LIB_PATH/htra_api.lib)
            LIBS += $$quote($$HTRA_LIB_PATH/libfftw3-3.lib)
            LIBS += $$quote($$HTRA_LIB_PATH/liquid.lib)
        }
    }

    linux {
        message("Build with real libhtraapi for Linux")

        HTRA_LIB_PATH = $$HTRA_SDK_PATH/lib/linux/x64

        LIBS += -L$$HTRA_LIB_PATH
        LIBS += -lhtraapi
        LIBS += -lfftw3
        LIBS += -lusb-1.0
        LIBS += -lliquid
        LIBS += -lpthread

        # Optional: helps the app find .so files at runtime
        # if they are located in the SDK folder.
        QMAKE_LFLAGS += -Wl,-rpath,$$HTRA_LIB_PATH
    }

    SOURCES += \
        devices/htra_device.cpp

    HEADERS += \
        devices/htra_device.h
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
    htra_proxy_server.h \
    htra_server_main_timer.h \
    providers/htra_telemetry_provider.h \
    switcher_processor.h \
    telemetry/htra_telemetry_server.h
