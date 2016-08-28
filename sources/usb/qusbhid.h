#ifndef QUSBHID_H
#define QUSBHID_H

#include <QObject>

struct hid_device_;

class QUsbHid: public QObject
{
    Q_OBJECT
public:
    QUsbHid(QObject *parent = nullptr);
    QUsbHid(quint16 vendorID, quint16 productID, QObject *parent = nullptr);
    QUsbHid(const QString &path, QObject *parent = nullptr);
    ~QUsbHid();

    /*setting*/
    void setUsbHid(quint16 vendorID, quint16 productID);
    void setUsbHidPath(const QString &path);

    /*getting*/
    quint16 vendorID() const;
    quint16 productID() const;
    QString usbHidPath() const;

    /*Usb operation*/
    bool openUsbHid();  //打开HID设备,获取设备控制句柄
    bool openUsbHid(quint16 vendorID, quint16 productID);
    bool openUsbHid(const QList<quint16> &device);
    bool openUsbHid(const QString &path);
    bool enumerateUsbHid();
    bool closeUsbHid();

    /*Usb write/read operation*/
    qint32 write(const QByteArray &data);           //最大写64bytes
    QByteArray read(quint32 maxLength = 64, bool nonBlock = false);        //最大读64bytes
    QByteArray readTimeout(quint32 maxLength = 64, int milliseconds = -1);  //超时阻塞读取, 当milliseconds为-1时, 阻塞读取数据
    QString lastError();

    /*static function*/
    static QList<QList<quint16>> allUsbHid();       //1为vendorID, 2为productID

private:
    bool initUsbHid();
    bool exitUsbHid();

    quint16 vendor_id = 0;
    quint16 product_id = 0;
    QString hid_path;
    hid_device_ *hid_device_handle = nullptr;     //handle
};
#endif // QUSBHID_H
