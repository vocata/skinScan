#ifndef TITLEICON_H
#define TITLEICON_H

#include <QWidget>

class TitleIcon : public QWidget
{
    Q_OBJECT
public:
    enum BUTTONSTATUS{
        BUTTON_ENTER,
        BUTTON_LEAVE,
        BUTTON_PRESSED,
        BUTTON_DISABLE
    };
    explicit TitleIcon(QWidget *parent = 0);
    TitleIcon(const QString &icon, int num = 4, QWidget *parent = 0);
    void setIcon(const QString &icon, int num = 4);

signals:
    void enterSignal();
    void leaveSignal();
    void buttonClicked();

public slots:

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void changeEvent(QEvent *e);

private:
    void setButtonStatus(BUTTONSTATUS status);
    int m_num;
    QList<QPixmap> m_pixList;
    QPixmap m_currentPix;
};

#endif // TITLEICON_H
