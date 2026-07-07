#include <QCoreApplication>

#include <htra_server_main_timer.h>
#ifdef HTRA_MOCK
#include "devices/mock_htra_device.h"
#else
#include "devices/htra_device.h"
#endif

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

#ifdef HTRA_MOCK
    MockHtraDevice device;
#else
    HtraDevice device;
#endif
    HtraServerMainTimer *mainTimer = new HtraServerMainTimer(device);


    return a.exec();
}
