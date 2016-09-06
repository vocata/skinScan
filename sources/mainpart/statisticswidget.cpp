#include "statisticswidget.h"
#include "sources/chart/plotwidget.h"
#include "sources/chart/jsontodata.h"

#include <QGroupBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

StatisticsWidget::StatisticsWidget(QWidget *parent) : QWidget(parent)
{
    m_moistureButton = new QPushButton(QStringLiteral("水分"), this);
    m_greaseButton = new QPushButton(QStringLiteral("油脂"), this);
    m_temperatureButton = new QPushButton(QStringLiteral("温度"), this);
    m_PHButton = new QPushButton(QStringLiteral("PH值"), this);
    m_stackedWidget = new QStackedWidget(this);
    m_moistureWidget = new PlotWidget(-0.5, 1.5, this);
    m_greaseWidget = new PlotWidget(-0.5, 1.5, this);
    m_tempWidget = new PlotWidget(0, 45, this);
    m_PHWidget = new PlotWidget(0, 14, this);

    /* button */
    m_moistureButton->setFixedSize(250, 40);
    m_moistureButton->setObjectName("moistureButton");

    m_greaseButton->setFixedSize(250, 40);
    m_greaseButton->setObjectName("greaseButton");

    m_temperatureButton->setFixedSize(250, 40);
    m_temperatureButton->setObjectName("temperatureButton");

    m_PHButton->setFixedSize(250, 40);
    m_PHButton->setObjectName("PHButton");

    /* stacked widget */
    m_stackedWidget->addWidget(m_moistureWidget);
    m_stackedWidget->addWidget(m_greaseWidget);
    m_stackedWidget->addWidget(m_tempWidget);
    m_stackedWidget->addWidget(m_PHWidget);
    m_stackedWidget->setObjectName("stackedWidget");

    QGroupBox *buttonGroup = new QGroupBox(this);
    QVBoxLayout *buttonBox = new QVBoxLayout(buttonGroup);
    buttonBox->setObjectName("buttonBox");
    buttonBox->addWidget(m_moistureButton);
    buttonBox->addWidget(m_greaseButton);
    buttonBox->addWidget(m_temperatureButton);
    buttonBox->addWidget(m_PHButton);
    buttonBox->setAlignment(m_PHButton, Qt::AlignTop);
    buttonBox->setContentsMargins(10, 0, 10, 0);
    buttonBox->setSpacing(0);

    QHBoxLayout *hBox = new QHBoxLayout(this);
    hBox->addWidget(buttonGroup);
    hBox->addWidget(m_stackedWidget);
    hBox->setMargin(0);
    hBox->setSpacing(0);

    /* connect */
    connect(m_greaseButton, &QPushButton::clicked, this, &StatisticsWidget::m_greaseSlot);
    connect(m_moistureButton, &QPushButton::clicked, this, &StatisticsWidget::m_moistureSlot);
    connect(m_temperatureButton, &QPushButton::clicked, this, &StatisticsWidget::m_tempSlot);
    connect(m_PHButton, &QPushButton::clicked, this, &StatisticsWidget::m_PHSlot);

}

void StatisticsWidget::setPlotData(const QJsonDocument &document)
{
    qDebug() << document;
    JsonToData jsonData(document);//please add jsonDocument

    m_moistureWidget->setSingleData(jsonData.getData("moisture"), "水分", QColor(220, 33, 40));
    m_greaseWidget->setSingleData(jsonData.getData("grease"), "油脂", QColor(21, 165, 140));
    m_tempWidget->setSingleData(jsonData.getData("temperature"), "温度", QColor(252, 133, 33));
    m_PHWidget->setSingleData(jsonData.getData("ph"), "PH值", QColor(121, 83, 70));
    /* adjust */
    m_moistureWidget->setYRange(-0.5, 1.5);
    m_greaseWidget->setYRange(-0.5, 1.5);
    m_tempWidget->setYRange(0, 45);
    m_PHWidget->setYRange(0, 14);

    m_moistureWidget->adjustPlot();
    m_greaseWidget->adjustPlot();
    m_tempWidget->adjustPlot();
    m_PHWidget->adjustPlot();
}

void StatisticsWidget::clear()
{
    m_moistureWidget->clearGraph();
    m_greaseWidget->clearGraph();
    m_tempWidget->clearGraph();
    m_PHWidget->clearGraph();
}

void StatisticsWidget::m_moistureSlot()
{
    m_stackedWidget->setCurrentIndex(0);
}

void StatisticsWidget::m_greaseSlot()
{
    m_stackedWidget->setCurrentIndex(1);
}

void StatisticsWidget::m_tempSlot()
{
    m_stackedWidget->setCurrentIndex(2);
}

void StatisticsWidget::m_PHSlot()
{
    m_stackedWidget->setCurrentIndex(3);
}
