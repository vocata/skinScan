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

    /* button */
    m_moistureButton->setFixedSize(250, 40);
    m_moistureButton->setObjectName("moistureButton");

    m_greaseButton->setFixedSize(250, 40);
    m_greaseButton->setObjectName("greaseButton");

    m_temperatureButton->setFixedSize(250, 40);
    m_temperatureButton->setObjectName("temperatureButton");

    m_PHButton->setFixedSize(250, 40);
    m_PHButton->setObjectName("PHButton");

    /* plot widget */
    JsonToData jsonData();//please add jsonDocument
    m_moistureWidget = new PlotWidget;
    m_moistureWidget->setSingleData(jsonData.getData("moisture"), "水分", Qt::blue);

    m_greaseWidget = new PlotWidget;
    m_greaseWidget->setSingleData(jsonData.getData("grease"), "油脂", Qt::red);

    m_tempWidget = new PlotWidget;
    m_tempWidget->setSingleData(jsonData.getData("temperature"), "温度", Qt::yellow);

    m_PHWidget = new PlotWidget;
    m_PHWidget->setSingleData(jsonData.getData("ph"), "PH值", Qt::green);

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
