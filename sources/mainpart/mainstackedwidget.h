#ifndef MAINSTACKEDWIDGET_H
#define MAINSTACKEDWIDGET_H

#include <QStackedWidget>

class MainStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit MainStackedWidget(QWidget *parent = 0);

signals:

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
public slots:
};

#endif // MAINSTACKEDWIDGET_H
