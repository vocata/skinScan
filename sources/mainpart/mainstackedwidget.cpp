#include "maintabwidget.h"

#include <QMouseEvent>

MainTabWidget::MainTabWidget(QWidget *parent) : QTabWidget(parent)
{

}

void MainTabWidget::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
}

void MainTabWidget::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}

void MainTabWidget::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
}

void MainTabWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    event->accept();
}
