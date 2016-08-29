#include "statisticswidget.h"

#include <QGroupBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

StatisticsWidget::StatisticsWidget(QWidget *parent) : QWidget(parent)
{
    m_moistureButton = new QPushButton(QStringLiteral("油脂"), this);
    m_greaseButton = new QPushButton(QStringLiteral("水分"), this);
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

    /* stacked widget */
    m_stackedWidget->setObjectName("stackedWidget");

    QGroupBox *buttonGroup = new QGroupBox(this);
    QVBoxLayout *buttonBox = new QVBoxLayout(buttonGroup);
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

}
