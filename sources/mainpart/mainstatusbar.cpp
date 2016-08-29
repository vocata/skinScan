#include "mainstatusbar.h"
#include "sources/customIcon/statusicon.h"
#include "sources/usb/qusbhid.h"
#include "sources/userclass/usbstatueshare.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QTimer>

MainStatusBar::MainStatusBar(QWidget *parent) : QStatusBar(parent)
{
    m_usbStatusIcon = new StatusIcon(this);
    m_usbStatusLabel = new QLabel(QStringLiteral("没有皮肤检测设备"), this);

    /* StatusIcon */
    m_usbStatusIcon->setIcon(":/statusbar/icon/usb_disable", ":/statusbar/icon/usb_enable");

    /* QLabel */
    m_usbStatusLabel->setObjectName("usbStatusLabel");

    /* QTimer */
    m_timer = new QTimer(this);
    m_timer->start(1500);

    /* layout */
    QWidget *statusBox = new QWidget(this);
    QHBoxLayout *hBox = new QHBoxLayout(statusBox);
    hBox->addWidget(m_usbStatusIcon);
    hBox->addWidget(m_usbStatusLabel);
    hBox->setSpacing(10);
    hBox->setContentsMargins(5, 0, 5, 0);

    /* statusBar attribution */
    this->addWidget(statusBox);
//    this->setSizeGripEnabled(false);

    /* connect */
    connect(m_timer, &QTimer::timeout, this, &MainStatusBar::m_detectUsbConnect);
}

void MainStatusBar::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
}

void MainStatusBar::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}

void MainStatusBar::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
}

void MainStatusBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    event->accept();
}

void MainStatusBar::setUsbStatus(bool enable)
{
    if(enable) {
        m_usbStatusLabel->setText(QStringLiteral("检测设备连接成功"));
    } else {
        m_usbStatusLabel->setText(QStringLiteral("没有皮肤检测设备"));
    }
    m_usbStatusIcon->setIconStatus(enable);
}

void MainStatusBar::m_detectUsbConnect()
{
    bool enable = false;
    QList<QList<quint16>> usbDevices = QUsbHid::allUsbHid();
    for(const auto &device: usbDevices) {
        // vendor_id == 0x2047
        if(device.at(0) == 0x2047) {
            enable = true;
            UsbStatueShare::setUsbDevice(device);
            break;
        }
    }
    this->setUsbStatus(enable);
    UsbStatueShare::setUsbStatus(enable);
}
