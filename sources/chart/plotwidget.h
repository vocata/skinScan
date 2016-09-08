#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include "sources/qcustomplot/qcustomplot.h"
#include <QVector>
#include <QString>
#include <QHBoxLayout>
#include <QMenu>

class PlotWidget : public QWidget
{
    Q_OBJECT

public:
    PlotWidget(QWidget *parent = 0);
    ~PlotWidget();
    void adjustPlot();
    void setTitle(const QString &title);
    void setSingleData(QVector<double> aData, const QString &dataName, const QColor &color = Qt::blue);
    void setMultiData(QVector<double> oil, QVector<double> moisture, QVector<double> temper, QVector<double> PHValue);
    void setYRange(const QVector<double> &y, const QVector<QString> &yTick);
    void clearGraph();

private slots:
    void selectionChanged();//选中标签
    void contextMenuRequest(QPoint pos);//右键
    void moveLegend();//移动标签
    void fitPage();//适应页面


private:
    QCustomPlot *pQCustomPlot;
    QPen *pQPen;
    QMenu *menu;
};

#endif // PLOTWIDGET_H
