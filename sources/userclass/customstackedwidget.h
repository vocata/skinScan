#ifndef CUSTOMSTACKEDWIDGET_H
#define CUSTOMSTACKEDWIDGET_H

#include <QStackedWidget>

class QGraphicsOpacityEffect;
class QPropertyAnimation;

class CustomStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit CustomStackedWidget(QWidget *parent = 0);
    void setEffectEnable(bool enable);

signals:

public slots:
    void setCurrentIndex(int index);
    void setCurrentWidget(QWidget *w);

private:
    QGraphicsOpacityEffect *m_effect = nullptr;
    QPropertyAnimation *m_animation = nullptr;
};

#endif // CUSTOMSTACKEDWIDGET_H
