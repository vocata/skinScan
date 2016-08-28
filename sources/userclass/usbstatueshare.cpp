#include "usbstatueshare.h"

UsbStatueShare::UsbStatueShare(QObject *parent) : QObject(parent)
{

}

bool UsbStatueShare::usbStatus()
{
    return m_usbStatus;
}

void UsbStatueShare::setUsbStatus(bool usbStatus)
{
    m_usbStatus = usbStatus;
}

QList<quint16> UsbStatueShare::getUsbDevice()
{
    return m_usbDevice;
}

void UsbStatueShare::setUsbDevice(const QList<quint16> &usbDevice)
{
    m_usbDevice = usbDevice;
}

bool UsbStatueShare::m_usbStatus = false;
QList<quint16> UsbStatueShare::m_usbDevice;
