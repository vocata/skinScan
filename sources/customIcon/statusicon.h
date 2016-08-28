#ifndef STATUSICON_H
#define STATUSICON_H

#include <QWidget>

class StatusIcon : public QWidget
{
    Q_OBJECT
public:
    explicit StatusIcon(QWidget *parent = 0);
    StatusIcon(const QString &icon1, const QString &icon2, QWidget *parent = 0);
    void setIcon(const QString &icon1, const QString &icon2);

signals:

public slots:
    void setIconStatus(bool enable);

protected:
    void paintEvent(QPaintEvent *);

private:
    QPair<QPixmap, QPixmap> m_pixPair;
    QPixmap m_currentPix;
};

#endif // STATUSICON_H
