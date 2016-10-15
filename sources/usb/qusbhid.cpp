#include "qusbhid.h"
#include "hidapi.h"

#include <QString>
#include <QVector>
#include <QDebug>

QUsbHid::QUsbHid(QObject *parent) : QObject(parent)
{
    this->initUsbHid();
}

QUsbHid::QUsbHid(quint16 vendorID, quint16 productID, QObject *parent)
    : QObject(parent)
{
    vendor_id = vendorID;
    product_id = productID;
    this->initUsbHid();
}

QUsbHid::QUsbHid(const QString &path, QObject *parent)
    : QObject(parent)
{
    hid_path = path;
    this->initUsbHid();
}

QUsbHid::~QUsbHid()
{
    this->closeUsbHid();
    this->exitUsbHid();
}

void QUsbHid::setUsbHid(quint16 vendorID, quint16 productID)
{
    this->vendor_id = vendorID;
    this->product_id = productID;
}

void QUsbHid::setUsbHidPath(const QString &path)
{
    this->hid_path = path;
}

quint16 QUsbHid::vendorID() const
{
    return this->vendor_id;
}

quint16 QUsbHid::productID() const
{
    return this->product_id;
}

QString QUsbHid::usbHidPath() const
{
    return this->hid_path;
}

bool QUsbHid::openUsbHid()
{
    hid_device_handle = hid_open(vendor_id, product_id, nullptr);
    return hid_device_handle;
}

bool QUsbHid::openUsbHid(quint16 vendorID, quint16 productID)
{
    vendor_id = vendorID;
    product_id = productID;
    hid_device_handle = hid_open(vendor_id, product_id, nullptr);
    return hid_device_handle;
}
bool QUsbHid::openUsbHid(const QList<quint16> &device)
{
    vendor_id = device.at(0);
    product_id = device.at(1);
    hid_device_handle = hid_open(vendor_id, product_id, nullptr);
    return hid_device_handle;
}

bool QUsbHid::openUsbHid(const QString &path)
{
    hid_path = path;
    hid_device_handle = hid_open_path(hid_path.toLatin1().constData());
    return hid_device_handle;
}

bool QUsbHid::enumerateUsbHid()
{
    hid_device_info *device_info = hid_enumerate(vendor_id, product_id);
    hid_free_enumeration(device_info);
    return (device_info == nullptr)? false: true;
}

bool QUsbHid::closeUsbHid()
{
    if(hid_device_handle) {
        hid_close(hid_device_handle);
        hid_device_handle = nullptr;
        return true;
    }
    return false;
}

qint32 QUsbHid::write(const QByteArray &data)
{
    QByteArray buffer = data;

    buffer.prepend(static_cast<char>(data.length()));       //加入长度字节
    buffer.prepend(static_cast<char>(0x3f));                //加入report ID字节

    return hid_write(hid_device_handle, (quint8*)buffer.data(), buffer.length());
}

QByteArray QUsbHid::read(quint32 maxLength, bool nonBlock)
{
    hid_set_nonblocking(hid_device_handle, nonBlock);
    quint8 *buffer = new quint8[maxLength + 2]();          //最后一位为'\0'
    int length = hid_read(hid_device_handle, buffer, maxLength + 2);

    if(length == 0) {
        return QByteArray();
    }
    QByteArray data((char *)buffer, maxLength + 2);
    delete[] buffer;

    int dataLength = (int)data.at(1);   //获取真正的数据长度
    data.remove(0, 2);
    data.truncate(dataLength);          //length只是获取数据的最大值, 这里是获取真正的数据部分
    return data;
}

QByteArray QUsbHid::readTimeout(quint32 maxLength, int milliseconds)
{
    quint8 *buffer = new quint8[maxLength + 2]();

    int length = hid_read_timeout(hid_device_handle, buffer, maxLength + 2, milliseconds);

    if(length == 0) {
        return QByteArray();
    }
    QByteArray data((char *)buffer, maxLength + 2);
    delete[] buffer;

    int dataLength = (int)data.at(1);   //获取真正的数据长度
    data.remove(0, 2);
    data.truncate(dataLength);          //length只是获取数据的最大值, 这里是获取真正的数据部分
    return data;
}

QString QUsbHid::lastError()
{
    std::wstring buffer(hid_error(hid_device_handle));
    QString error = QString::fromStdWString(buffer);
    return error;
}

QList<QList<quint16>> QUsbHid::allUsbHid()
{
    hid_device_info *device_info = hid_enumerate(0, 0);
    hid_device_info *next = device_info;

    QList<QList<quint16>> allID;
    while(next) {
        QList<quint16> id;
        id << next->vendor_id << next->product_id;
        allID.push_back(id);
        next = next->next;
    }
    hid_free_enumeration(device_info);
    return allID;
}

bool QUsbHid::initUsbHid()
{
    return !hid_init();
}

bool QUsbHid::exitUsbHid()
{
    return !hid_exit();
}

