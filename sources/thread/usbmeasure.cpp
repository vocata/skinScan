#include "usbmeasure.h"
#include "sources/userclass/usbstatueshare.h"

#include <QVector>

#include <QDebug>

UsbMeasure::UsbMeasure(QObject *parent) : QThread(parent)
{
}

UsbMeasure::~UsbMeasure()
{
    this->stop();
}

void UsbMeasure::stop()
{
    m_stopped = true;
    this->wait(500);
}

void UsbMeasure::run()
{

    bool isOpen = false;
    while(!m_stopped) {
        if(!UsbStatueShare::usbStatus()) {     //检测突然拔出设备
            emit usbDisconnect();
            isOpen = false;
            break;
        }
        if(!isOpen) {
            isOpen = m_usbDevice.openUsbHid(UsbStatueShare::getUsbDevice());
            if(isOpen) {
                m_usbDevice.write(QByteArray().append('#'));    //start
            }
            continue;
        }
        QByteArray data = m_usbDevice.readTimeout(64, 200);
        if (!data.isEmpty()) {
            emit readyRead(data);
        }

    }
    if(isOpen) {
        m_usbDevice.write(QByteArray().append('@'));    //end
    }
    m_usbDevice.closeUsbHid();
    m_stopped = false;
}
