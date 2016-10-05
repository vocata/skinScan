#ifndef CAMERADIALOG_H
#define CAMERADIALOG_H

#include "sources/userclass/customdialog.h"

#include <QCamera>

class QCameraViewfinder;
class QCameraImageCapture;
class QPushButton;

class CameraDialog : public CustomDialog
{
    Q_OBJECT
public:
    explicit CameraDialog(const QString &name, QWidget *parent = 0);

    ~CameraDialog();

signals:

public slots:

private:
    QCamera *m_camera = nullptr;
    QCameraViewfinder *m_viewfinder = nullptr;
    QCameraImageCapture *m_imageCapture = nullptr;

    QPushButton *m_takeImageButton = nullptr;
    QPushButton *m_saveImageButton = nullptr;

    /* 图片路径 */
    QString m_dir;
    /* 当前图片路径 */
    QString m_currentImagePath;

private slots:
    void m_captureImage();
    void m_saveImage();
    void m_setImage(int id, const QImage &preview);
    void m_handelError(QCamera::Error error);
};

#endif // CAMERADIALOG_H
