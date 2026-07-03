#include <QCoreApplication>

#include <htra_server_main_timer.h>
#include <htra_proxy_server.h>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    HtraServerMainTimer *mainTimer = new HtraServerMainTimer();


    return a.exec();
}
