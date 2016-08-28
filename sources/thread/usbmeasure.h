#ifndef USBMEASURE_H
#define USBMEASURE_H

#include <QThread>
#include "sources/usb/qusbhid.h"

class UsbMeasure : public QThread
{
    Q_OBJECT
public:
    explicit UsbMeasure(QObject *parent = nullptr);
    ~UsbMeasure();

signals:
    void readyRead(QByteArray data);
    void usbDisconnect();

public slots:
    void stop();

protected:
    void run();

private:
    QUsbHid m_usbDevice;
    volatile bool m_stopped = false;
    volatile bool m_usbStatus = false;
};

#endif // USBMEASURE_H
