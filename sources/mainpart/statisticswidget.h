#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QWidget>

class QPushButton;
class QStackedWidget;
class PlotWidget;

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

    PlotWidget *m_moistureWidget;
    PlotWidget *m_greaseWidget;
    PlotWidget *m_tempWidget;
    PlotWidget *m_PHWidget;

private slots:
    void m_moistureSlot();
    void m_greaseSlot();
    void m_tempSlot();
    void m_PHSlot();
};

#endif // STATISTICSWIDGET_H
