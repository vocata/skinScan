#include "customstackedwidget.h"

#include <QGraphicsEffect>
#include <QPropertyAnimation>

CustomStackedWidget::CustomStackedWidget(QWidget *parent) : QStackedWidget(parent)
{
    m_effect = new QGraphicsOpacityEffect(this);
    m_animation = new QPropertyAnimation(m_effect, "opacity", this);
    m_animation->setStartValue(0.5);
    m_animation->setEndValue(1);
    m_animation->setDuration(200);
    m_animation->setEasingCurve(QEasingCurve::InQuad);
}

void CustomStackedWidget::setEffectEnable(bool enable)
{
    m_effect->setEnabled(enable);
}

void CustomStackedWidget::setCurrentIndex(int index)
{
    if(this->currentIndex() != index) {
        this->widget(index)->setGraphicsEffect(m_effect);
        m_animation->start();
    }
    this->QStackedWidget::setCurrentIndex(index);
}

void CustomStackedWidget::setCurrentWidget(QWidget *w)
{
    if(this->currentWidget() != w) {
        w->setGraphicsEffect(m_effect);
        m_animation->start();
    }
    this->QStackedWidget::setCurrentWidget(w);
}
