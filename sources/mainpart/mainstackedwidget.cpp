#include "mainstackedwidget.h"

#include <QMouseEvent>

MainStackedWidget::MainStackedWidget(QWidget *parent) : QStackedWidget(parent)
{

}

void MainStackedWidget::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
}

void MainStackedWidget::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}

void MainStackedWidget::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
}

void MainStackedWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    event->accept();
}
