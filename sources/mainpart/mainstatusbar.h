#ifndef MAINSTATUSBAR_H
#define MAINSTATUSBAR_H

#include <QStatusBar>

class StatusIcon;
class QLabel;
class QTimer;

class MainStatusBar : public QStatusBar
{
    Q_OBJECT
public:
    explicit MainStatusBar(QWidget *parent = 0);

signals:

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

public slots:
    void setUsbStatus(bool enable);

private:
    StatusIcon *m_usbStatusIcon;
    QLabel *m_usbStatusLabel;
    QTimer *m_timer;

private slots:
    void m_detectUsbConnect();
};

#endif // MAINSTATUSBAR_H
