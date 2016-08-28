#ifndef MAINTABWIDGET_H
#define MAINTABWIDGET_H

#include <QTabWidget>

class MainTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit MainTabWidget(QWidget *parent = 0);

signals:

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
public slots:
};

#endif // MAINTABWIDGET_H
