#include "sources/chart/plotwidget.h"

PlotWidget::PlotWidget(QWidget *parent)
        : QWidget(parent)
{
    pQCustomPlot = new QCustomPlot;
    //x轴坐标不可见
    pQCustomPlot->xAxis->setTickLabels(false);
    //设置图例格式
    pQCustomPlot->legend->setVisible(true);
    pQCustomPlot->legend->setFont(QFont("Microsoft YaHei",9));
    pQCustomPlot->legend->setSelectedFont(QFont("Microsoft YaHei",9));
    pQCustomPlot->legend->setSelectableParts(QCPLegend::spItems);
    //线的粗细
    pQPen = new QPen;
    pQPen->setWidth(2);

    /* color */
    pQCustomPlot->xAxis->setBasePen(QPen(QColor(216, 216, 216, 255), 1));
    pQCustomPlot->yAxis->setBasePen(QPen(QColor(216, 216, 216, 255), 1));
    pQCustomPlot->xAxis->setTickPen(QPen(QColor(200, 200, 200, 255), 2));
    pQCustomPlot->yAxis->setTickPen(QPen(QColor(200, 200, 200, 255), 1));
    pQCustomPlot->xAxis->setSubTickPen(QPen(QColor(216, 216, 216, 255), 1));
    pQCustomPlot->yAxis->setSubTickPen(QPen(QColor(216, 216, 216, 255), 1));

    pQCustomPlot->xAxis->grid()->setPen(QPen(QColor(216, 216, 216, 255), 1, Qt::DotLine));
    pQCustomPlot->yAxis->grid()->setPen(QPen(QColor(216, 216, 216, 255), 1, Qt::DotLine));
    pQCustomPlot->setBackground(QColor(250, 250, 250, 255));

    //互动
    pQCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectLegend | QCP::iSelectPlottables);

    connect(pQCustomPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));//标签被选中

    pQCustomPlot->setContextMenuPolicy(Qt::CustomContextMenu);//右键功能
    connect(pQCustomPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));

    QHBoxLayout *vBox = new QHBoxLayout(this);
    vBox->addWidget(pQCustomPlot);
    this->resize(500,500);
}

PlotWidget::~PlotWidget()
{
    delete pQPen;
}

void PlotWidget::setTitle(const QString &title)
{
    pQCustomPlot->plotLayout()->insertRow(0);
    QCPPlotTitle *pTitle = new QCPPlotTitle(pQCustomPlot, title);
    pTitle->setFont(QFont("Microsoft YaHei",12));
    pQCustomPlot->plotLayout()->addElement(0, 0, pTitle);
}

void PlotWidget::setSingleData(QVector<double> aData, const QString &dataName, const QColor &color)
{
    QVector<double> serials;
    serials.resize(aData.size());
    for(int i = 0; i < aData.size(); i++)
        serials[i] = i;
    pQCustomPlot->addGraph();
    pQCustomPlot->graph(0)->setData(serials, aData);//设置数据
    pQCustomPlot->graph(0)->setName(dataName);//设置图例名称
    pQPen->setColor(color);//设置线的颜色
    pQCustomPlot->graph(0)->setPen(*pQPen);
    pQCustomPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));//线上的点
    pQCustomPlot->graph(0)->rescaleAxes();//重新绘制坐标轴


}

void PlotWidget::setMultiData(QVector<double> oil, QVector<double> moisture, QVector<double> temper, QVector<double> PHValue)
{
    QStringList dataNames;
    dataNames << "油脂" << "水分" << "温度" << "PH值";
    QVector<QColor> dataColor;
    dataColor << Qt::red << Qt::blue << Qt::yellow << Qt::green;

    QVector<double> serials;
    serials.resize(oil.size());
    for(int i = 0; i < oil.size(); i++)
        serials[i] = i;

    for (int i = 0; i < dataNames.size(); ++i)
    {
      pQCustomPlot->addGraph();//增加线
      pQPen->setColor(dataColor.at(i));//线的颜色
      pQCustomPlot->graph()->setPen(*pQPen);
      pQCustomPlot->graph()->setName(dataNames.at(i));//线的名称
      pQCustomPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));//线上的点
    }
    pQCustomPlot->graph(0)->setData(serials, oil);
    pQCustomPlot->graph(1)->setData(serials, moisture);
    pQCustomPlot->graph(2)->setData(serials, temper);
    pQCustomPlot->graph(3)->setData(serials, PHValue);

    for(int i = 0; i < dataNames.size(); ++i)//重画坐标
        pQCustomPlot->graph(i)->rescaleAxes(true);
}

void PlotWidget::selectionChanged()
{
    for (int i=0; i< pQCustomPlot->graphCount(); ++i)
    {
      QCPGraph *graph = pQCustomPlot->graph(i);
      QCPPlottableLegendItem *item = pQCustomPlot->legend->itemWithPlottable(graph);
      if (item->selected() || graph->selected())
      {
        item->setSelected(true);
        graph->setSelected(true);
      }
    }
}

void PlotWidget::contextMenuRequest(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    if (pQCustomPlot->legend->selectTest(pos, false) >= 0) // context menu on legend requested
    {
      menu->addAction("顶部左侧", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
      menu->addAction("顶部居中", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
      menu->addAction("顶部右侧", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
      menu->addAction("底部左侧", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
      menu->addAction("底部右侧", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
    }
    else  // general context menu on graphs requested
    {
      menu->addAction("适应页面", this, SLOT(fitPage()));
    }

    menu->popup(pQCustomPlot->mapToGlobal(pos));
}

void PlotWidget::moveLegend()
{
    if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
    {
      bool ok;
      int dataInt = contextAction->data().toInt(&ok);
      if (ok)
      {
        pQCustomPlot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
        pQCustomPlot->replot();
      }
    }
}

void PlotWidget::fitPage()
{
    pQCustomPlot->xAxis->setRange(0, 0.1);
    pQCustomPlot->yAxis->setRange(0, 0.1);
    for(int i = 0; i < pQCustomPlot->graphCount(); ++i)//重画坐标
        pQCustomPlot->graph(i)->rescaleAxes(true);
    pQCustomPlot->replot();
}
