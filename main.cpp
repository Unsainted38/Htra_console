#include <QCoreApplication>

#include <signalhound_server_main_timer.h>
#include <htra_proxy_server.h>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    quint8 outputType = 0;

    qRegisterMetaType<QList<uint32_t> >("QList<uint32_t>");

    if(argc > 1) {
        QStringList tmpList = QCoreApplication::arguments();
        QString tmpString = tmpList[1];
        outputType = tmpString.toInt();
    }

    for(int i = 3400; i < 3600; ++i) {
        qDebug() << i << "   " << (i - 3400) / 10.0 << "   " << (i - 3400) / 10 << "   " << (((i - 3400) / 10) / 5) * 5;
    }

    TSignalhoundServerMainTimer *mainTimer = new TSignalhoundServerMainTimer(outputType);


    return a.exec();
}
