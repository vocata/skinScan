#include "barchart.h"
#include "sources/qcustomplot/qcustomplot.h"

#include <QTimer>

constexpr int TickNum = 5;
constexpr int PlotTime = 200;

BarChart::BarChart(QWidget *parent) : QWidget(parent)
{
    m_customPlot = new QCustomPlot(this);
    m_mainBars = new QCPBars(m_customPlot->xAxis, m_customPlot->yAxis);
    m_subBars = new QCPBars(m_customPlot->xAxis, m_customPlot->yAxis);
    m_timer = new QTimer(this);

    /* x & y */
    QVector<double> x;
    x << 1 << 2;
    QVector<QString> xTick;
    xTick << QStringLiteral("本次") << QStringLiteral("上次");
    m_customPlot->xAxis->setAutoTicks(false);
    m_customPlot->xAxis->setAutoTickLabels(false);
    m_customPlot->xAxis->setTickVectorLabels(xTick);
    m_customPlot->xAxis->setTickVector(x);
    m_customPlot->xAxis->setSubTickCount(0);
    m_customPlot->xAxis->setRange(0.5, 3);

    m_customPlot->xAxis->setTickLabelRotation(0);
    m_customPlot->xAxis->setTickLabelFont(QFont("Microsoft Yahei", 10));
    m_customPlot->xAxis->setLabelFont(QFont("Microsoft Yahei", 10));

    m_y << 0 << 20 << 40 << 60 << 80 << 100;
    m_yTick << "0" << "20" << "40" << "60" << "80" << "100";
    m_customPlot->yAxis->setAutoTicks(false);
    m_customPlot->yAxis->setAutoTickLabels(false);
    m_customPlot->yAxis->setTickVectorLabels(m_yTick);
    m_customPlot->yAxis->setTickVector(m_y);
    m_customPlot->yAxis->setSubTickCount(0);
    m_customPlot->yAxis->setRange(0, 100);

    m_customPlot->yAxis->setPadding(10);
    m_customPlot->yAxis->setTickLabelFont(QFont("Microsoft Yahei", 10));
    m_customPlot->yAxis->setLabelFont(QFont("Microsoft Yahei", 14));

    /* bar */
    m_mainBars->setWidth(0.5);
    m_mainBars->setPen(Qt::NoPen);
    m_subBars->setWidth(0.5);
    m_subBars->setPen(Qt::NoPen);

    /* color */
    m_customPlot->xAxis->setBasePen(QPen(QColor(216, 216, 216, 255), 1));
    m_customPlot->yAxis->setBasePen(QPen(QColor(216, 216, 216, 255), 1));
    m_customPlot->xAxis->setTickPen(QPen(QColor(200, 200, 200, 255), 2));
    m_customPlot->yAxis->setTickPen(QPen(QColor(200, 200, 200, 255), 1));

    m_customPlot->xAxis->grid()->setPen(QPen(QColor(216, 216, 216, 255), 1, Qt::DotLine));
    m_customPlot->yAxis->grid()->setPen(QPen(QColor(216, 216, 216, 255), 1, Qt::DotLine));
    m_customPlot->setBackground(QColor(250, 250, 250, 255));

    /* layout */
    QVBoxLayout *vBox = new QVBoxLayout(this);
    vBox->addWidget(m_customPlot);
    vBox->setMargin(0);

    connect(m_timer, &QTimer::timeout, this, &BarChart::m_plot, Qt::DirectConnection);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void BarChart::setBarRange(const double &start, const double &end)
{
    double average = end / TickNum;
    m_y.clear();
    m_yTick.clear();
    for(int i = 0; i <= TickNum; ++i) {
        double tick = start + i * average;
        m_y.push_back(tick);
        m_yTick.push_back(QString::number(tick));
    }
    m_customPlot->yAxis->setTickVectorLabels(m_yTick);
    m_customPlot->yAxis->setTickVector(m_y);
    m_customPlot->yAxis->setRange(start, end);
    m_customPlot->replot(QCustomPlot::rpImmediate);
}

void BarChart::setBarColor(const QColor &firColor, const QColor &secColor)
{
    m_mainBars->setBrush(firColor);
    m_subBars->setBrush(secColor);
}

void BarChart::setLeftText(const QString &text)
{
    m_customPlot->yAxis->setLabel(text);
}

void BarChart::setData(const double &data)
{
    m_lastData = m_currentData;
    m_currentData = QVector<double> (1, data);
    m_subBars->setData(QVector<double> (1, 2), m_lastData);
    m_customPlot->replot(QCustomPlot::rpImmediate);

    /* start timer */
    m_plotStep = data / PlotTime;
    m_timer->start(1);
}

void BarChart::setBarIndex(const qint16 index)
{
    m_index = index;
}

double BarChart::data() const
{
    return m_currentData.at(0);
}

void BarChart::clearData()
{
    /* clear plot cache */
    m_plotStep = 0;
    m_valueTemp = 0;
    m_plotCount = 0;
    m_timer->stop();

    /* clear data */
    m_currentData.clear();
    m_lastData.clear();
    m_mainBars->clearData();
    m_subBars->clearData();
    m_customPlot->replot(QCustomPlot::rpImmediate);
}

void BarChart::m_plot()
{
    if(m_plotCount != PlotTime) {
        m_valueTemp += m_plotStep;
        m_mainBars->setData(QVector<double> (1, 1), QVector<double> (1, m_valueTemp));
        m_customPlot->replot(QCustomPlot::rpImmediate);
        ++m_plotCount;
    } else {
        m_valueTemp = 0;
        m_plotCount = 0;
        m_plotStep = 0;
        m_timer->stop();
        emit plotFinish(m_currentData.at(0), m_index);
    }
}
