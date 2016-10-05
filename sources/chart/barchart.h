#ifndef BARCHART_H
#define BARCHART_H

#include <QWidget>

class QCustomPlot;
class QCPBars;
class QTimer;

class BarChart : public QWidget
{
    Q_OBJECT
public:
    explicit BarChart(QWidget *parent = 0);
    void setBarRange(const double &start, const double &end);
    void setBarColor(const QColor &firColor, const QColor &secColor);
    void setLeftText(const QString &text);
    void setData(const double &data);
    void setBarIndex(const qint16 index);

    double data() const;

signals:
    void plotFinish(const double &data, const qint16 &index);

public slots:
    void clearData();

private:
    QCustomPlot *m_customPlot = nullptr;
    QCPBars *m_mainBars = nullptr;
    QCPBars *m_subBars = nullptr;
    QTimer *m_timer = nullptr;

    /* y range */
    QVector<double> m_y;
    QVector<QString> m_yTick;

    /* data */
    QVector<double> m_currentData;
    QVector<double> m_lastData;

    /* plot */
    double m_plotStep = 0;
    double m_valueTemp = 0;
    int m_plotCount = 0;

    /* barIndex */
    qint16 m_index;

private slots:
    void m_plot();
};

constexpr int TickNum = 5;
constexpr int PlotTime = 200;

#endif // BARCHART_H
