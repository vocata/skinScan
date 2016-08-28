#ifndef USBSTATUESHARE_H
#define USBSTATUESHARE_H

#include <QObject>

/* USB status share class */

class UsbStatueShare : public QObject
{
    Q_OBJECT
public:
    explicit UsbStatueShare(QObject *parent = 0);

    static bool usbStatus();
    static void setUsbStatus(bool usbStatus);

    static QList<quint16> getUsbDevice();
    static void setUsbDevice(const QList<quint16> &usbDevice);

signals:

public slots:

private:
    static bool m_usbStatus;
    static QList<quint16> m_usbDevice;
};

#endif // USBSTATUESHARE_H
