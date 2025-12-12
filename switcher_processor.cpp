#include "switcher_processor.h"

SwitcherProcessor::SwitcherProcessor(QString configPath, QString section, QObject *parent)
    : QObject{parent} {
    transport = AbstractNetworkTransportFactory::getInstance(configPath, section);
    connect(transport, SIGNAL(translateData(QByteArray)), this, SLOT(OnGetReply(QByteArray)));
}

void SwitcherProcessor::setRF1() {
    sendCmd(0x01);
}

void SwitcherProcessor::setRF2() {
    sendCmd(0x02);
}

void SwitcherProcessor::setRF3() {
    sendCmd(0x03);
}

void SwitcherProcessor::setRF4() {
    sendCmd(0x04);
}

void SwitcherProcessor::RFoff() {
    sendCmd(0x00);
}

void SwitcherProcessor::sendCmd(quint8 cmdId) {
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::BigEndian);
    out.setFloatingPointPrecision(QDataStream::SinglePrecision);
    out << (quint8)0xAA
        << (quint8)0x55
        << cmdId;
    transport->write(packet);
}

void SwitcherProcessor::OnGetReply(QByteArray reply) {
    QByteArray buffer;
    quint8 value;
    //qDebug() << "Reply" << reply.toHex();
    buffer.append(reply);
    QDataStream in(&buffer, QIODevice::ReadOnly);
    in.setByteOrder(QDataStream::LittleEndian);
    in.setFloatingPointPrecision(QDataStream::SinglePrecision);
    in >> value;
    buffer.clear();

    switch(value) {
        case 0x00:
            //qDebug() << "RFoff";
            mode = "RFoff";
            break;

        case 0x01:
            //qDebug() << "RF1 on";
            mode = "RF1 on";
            break;

        case 0x02:
            //qDebug() << "RF2 on";
            mode = "RF2 on";
            break;

        case 0x03:
            //qDebug() << "RF3 on";
            mode = "RF3 on";
            break;

        case 0x04:
            //qDebug() << "RF4 on";
            mode = "RF4 on";
            break;

        default:
            break;
    }

}

