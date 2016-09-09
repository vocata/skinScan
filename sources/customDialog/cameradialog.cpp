#include "cameradialog.h"
#include "messagedialog.h"

#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QDateTime>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCameraInfo>
#include <QDir>
#include <QLabel>

#include <QDebug>

CameraDialog::CameraDialog(const QString &name, QWidget *parent) : CustomDialog(parent)
{
    m_camera = new QCamera(this);
    m_viewfinder = new QCameraViewfinder(this);
    m_imageCapture = new QCameraImageCapture(m_camera, this);
    m_takeImageButton = new QPushButton(QStringLiteral("拍照"), this);
    m_saveImageButton = new QPushButton(QStringLiteral("保存"), this);
    m_dir = QString("image/%1").arg(name);

    /* camera */
    m_camera->setViewfinder(m_viewfinder);
    m_imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);

    /* pushButton */
    m_takeImageButton->setFixedSize(100, 25);
    if(QCameraInfo::availableCameras().isEmpty()) {
        m_takeImageButton->setEnabled(false);
    }
    m_saveImageButton->setFixedSize(100, 25);
    m_saveImageButton->setEnabled(false);

    /* layout */
    QVBoxLayout *rightBox = new QVBoxLayout();
    rightBox->addWidget(m_takeImageButton);
    rightBox->addWidget(m_saveImageButton);
    rightBox->setAlignment(m_takeImageButton, Qt::AlignBottom | Qt::AlignHCenter);
    rightBox->setAlignment(m_saveImageButton, Qt::AlignHCenter);
    rightBox->setMargin(10);

    QVBoxLayout *leftBox = new QVBoxLayout();
    leftBox->addWidget(m_viewfinder);

    QHBoxLayout *hBox = new QHBoxLayout();
    hBox->addLayout(leftBox);
    hBox->addLayout(rightBox);
    hBox->setMargin(10);

    /* connect */
    connect(m_takeImageButton, &QPushButton::clicked, this, &CameraDialog::m_captureImage);
    connect(m_saveImageButton, &QPushButton::clicked, this, &CameraDialog::m_saveImage);
    connect(m_imageCapture, &QCameraImageCapture::imageCaptured, this, &CameraDialog::m_setImage);
    connect(m_camera, static_cast<void(QCamera::*)(QCamera::Error)>(&QCamera::error), this, &CameraDialog::m_handelError);
    connect(m_camera, &QCamera::lockFailed, [=](){ qDebug() << "error";});

    /* window attribution */
    this->hideMinIcon();
    this->setCentralWidgetLayout(hBox);
    this->setShadow(false);
    this->setWindowTitle(new QLabel("拍照"));
    this->startAnimation();
    this->centralWidget()->setObjectName("centralDialog");

    /* camera start */
    m_camera->start();
}

void CameraDialog::m_captureImage()
{
    if(m_takeImageButton->text() == QStringLiteral("拍照")) {
        m_imageCapture->capture();
        m_takeImageButton->setText(QStringLiteral("重新拍照"));
    } else {
        m_camera->start();
        m_saveImageButton->setEnabled(false);
        m_takeImageButton->setText(QStringLiteral("拍照"));
    }
}

void CameraDialog::m_saveImage()
{
    QDir().mkpath(m_dir);
    QString fullPath = m_dir + QString("/%1.%2").arg(m_date, "jpg");
    m_image.save(fullPath, "JPG");
    m_camera->start();
    m_takeImageButton->setText(QStringLiteral("拍照"));
    m_saveImageButton->setEnabled(false);
    /* 提示保存成功 */
    MessageDialog dialog(this);
    dialog.execInformation(QStringLiteral("图片保存成功"), QStringLiteral("保存"));
}

void CameraDialog::m_setImage(int id, const QImage &preview)
{
    Q_UNUSED(id);
    m_image = preview;
    m_saveImageButton->setEnabled(true);
    m_camera->stop();
    m_date = QDateTime::currentDateTime().toString("yyyy-MM-ddThh-mm-ss");
}

void CameraDialog::m_handelError(QCamera::Error error)
{
    if(error != QCamera::NoError) {
        qDebug() << "有相机";
    } else {
        qDebug() << "没有相机";
    }
}
