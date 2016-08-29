#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QWidget>

class QPushButton;
class QStackedWidget;

class StatisticsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatisticsWidget(QWidget *parent = 0);

signals:

public slots:

private:
    QPushButton *m_moistureButton;
    QPushButton *m_greaseButton;
    QPushButton *m_temperatureButton;
    QPushButton *m_PHButton;
    QStackedWidget *m_stackedWidget;
};

#endif // STATISTICSWIDGET_H
