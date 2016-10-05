#include "statisticswidget.h"
#include "sources/chart/plotwidget.h"
#include "sources/chart/jsontodata.h"
#include "sources/chart/tablewidget.h"
#include "sources/customDialog/syncdialog.h"
#include "sources/customDialog/messagedialog.h"

#include <QGroupBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

#include <QDebug>



StatisticsWidget::StatisticsWidget(QWidget *parent) : QWidget(parent)
{
    m_chartButton = new QPushButton(QStringLiteral("折线图"), this);
    m_tableButton = new QPushButton(QStringLiteral("表格"), this);
    m_moistureButton = new QPushButton(QStringLiteral("   水分"), this);
    m_greaseButton = new QPushButton(QStringLiteral("   油脂"), this);
    m_temperatureButton = new QPushButton(QStringLiteral("   温度"), this);
    m_PHButton = new QPushButton(QStringLiteral("   PH值"), this);
    m_localButton = new QPushButton(QStringLiteral("   本地数据"), this);
    m_stackedWidget = new QStackedWidget(this);
    m_moistureWidget = new PlotWidget(this);
    m_greaseWidget = new PlotWidget(this);
    m_tempWidget = new PlotWidget(this);
    m_PHWidget = new PlotWidget(this);
    m_moistureTable = new TableWidget(this);
    m_greaseTable = new TableWidget(this);
    m_tempTable = new TableWidget(this);
    m_PHTable = new TableWidget(this);
    m_manager = new CustomNetwork(this);

    /* button */
    m_chartButton->setFixedSize(60, 25);
    m_chartButton->setCheckable(true);
    m_chartButton->setChecked(true);
    m_chartButton->setObjectName("chartButton");

    m_tableButton->setFixedSize(60, 25);
    m_tableButton->setCheckable(true);
    m_tableButton->setObjectName("tableButton");

    m_moistureButton->setFixedSize(200, 40);
    m_moistureButton->setIcon(QIcon(":/statistics/icon/moisture"));
    m_moistureButton->setIconSize(QSize(24, 24));
    m_moistureButton->setObjectName("indexButton");

    m_greaseButton->setFixedSize(200, 40);
    m_greaseButton->setIcon(QIcon(":/statistics/icon/grease"));
    m_greaseButton->setIconSize(QSize(24, 24));
    m_greaseButton->setObjectName("indexButton");

    m_temperatureButton->setFixedSize(200, 40);
    m_temperatureButton->setIcon(QIcon(":/statistics/icon/temperature"));
    m_temperatureButton->setIconSize(QSize(24, 24));
    m_temperatureButton->setObjectName("indexButton");

    m_PHButton->setFixedSize(200, 40);
    m_PHButton->setIcon(QIcon(":/statistics/icon/PH"));
    m_PHButton->setIconSize(QSize(24, 24));
    m_PHButton->setObjectName("indexButton");

    m_localButton->setFixedSize(200, 40);
    m_localButton->setIcon(QIcon(":/statistics/icon/local"));
    m_localButton->setIconSize(QSize(24, 24));
    m_localButton->setObjectName("indexButton");

    QButtonGroup *formatGroup = new QButtonGroup(this);
    formatGroup->addButton(m_chartButton, 0);
    formatGroup->addButton(m_tableButton, 4);

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(m_moistureButton, 0);
    buttonGroup->addButton(m_greaseButton, 1);
    buttonGroup->addButton(m_temperatureButton, 2);
    buttonGroup->addButton(m_PHButton, 3);

    /* plot widget */
    QVector<double> y;
    QVector<QString> yTick;

    y << -0.30 << 0 << 0.30 << 0.60 << 0.90 << 1.20 << 1.50;
    yTick << "-0.30" << "0" << "0.30" << "0.60" << "0.90" << "1.20" << "1.50";
    m_moistureWidget->setYRange(y, yTick);
    y.clear();
    yTick.clear();

    y << -0.30 << 0 << 0.30 << 0.60 << 0.90 << 1.20 << 1.50;
    yTick << "-0.30" << "0" << "0.30" << "0.60" << "0.90" << "1.20" << "1.50";
    m_greaseWidget->setYRange(y, yTick);
    y.clear();
    yTick.clear();

    y << -10.0 << 0 << 10.0 << 20.0 << 30.0 << 40.0 << 50.0;
    yTick << "-10.0" << "0" << "10.0" << "20.0"<< "30.0" << "40.0" << "50.0";
    m_tempWidget->setYRange(y, yTick);
    y.clear();
    yTick.clear();

    y << -3.0 << 0 << 3.0 << 6.0 << 9.0 << 12.0 << 15.0;
    yTick << "-3.00" << "0" << "3.00" << "6.00" << "9.00" << "12.0" << "15.0";
    m_PHWidget->setYRange(y, yTick);
    y = QVector<double>();
    yTick = QVector<QString>();

    /* stacked widget */
    m_stackedWidget->addWidget(m_moistureWidget);
    m_stackedWidget->addWidget(m_greaseWidget);
    m_stackedWidget->addWidget(m_tempWidget);
    m_stackedWidget->addWidget(m_PHWidget);

    m_stackedWidget->addWidget(m_moistureTable);
    m_stackedWidget->addWidget(m_greaseTable);
    m_stackedWidget->addWidget(m_tempTable);
    m_stackedWidget->addWidget(m_PHTable);

    m_stackedWidget->setObjectName("stackedWidget");

    /* layout */
    QGroupBox *formatBox = new QGroupBox(this);
    formatBox->setObjectName("formatBox");
    QHBoxLayout *formatLayout = new QHBoxLayout(formatBox);
    formatLayout->addWidget(m_chartButton, 0, Qt::AlignRight);
    formatLayout->addWidget(m_tableButton, 0, Qt::AlignLeft);
    formatLayout->setMargin(20);
    formatLayout->setSpacing(0);

    QGroupBox *buttonBox = new QGroupBox(this);
    buttonBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    buttonBox->setObjectName("buttonBox");
    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonBox);
    buttonLayout->addWidget(m_moistureButton);
    buttonLayout->addWidget(m_greaseButton);
    buttonLayout->addWidget(m_temperatureButton);
    buttonLayout->addWidget(m_PHButton, 0, Qt::AlignTop);
    buttonLayout->addWidget(m_localButton, 0, Qt::AlignBottom);
    buttonLayout->setContentsMargins(20, 0, 20, 20);
    buttonLayout->setSpacing(0);

    /* 左边部分布局 */
    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(formatBox);
    leftLayout->addWidget(buttonBox);
    leftLayout->setMargin(0);
    leftLayout->setSpacing(0);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addLayout(leftLayout);
    hLayout->addWidget(m_stackedWidget);
    hLayout->setMargin(0);
    hLayout->setSpacing(0);

    /* connect */
    connect(formatGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            [&](int index) { m_column = index; m_stackedWidget->setCurrentIndex(index + m_row); });
    connect(buttonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            [&](int index) { m_row = index; m_stackedWidget->setCurrentIndex(index + m_column); });
    connect(m_localButton, &QPushButton::clicked, this, &StatisticsWidget::m_showSyncDialog);
    connect(m_manager, &CustomNetwork::downloadUserDataStatus, this, &StatisticsWidget::m_downloadDataReply);
}

void StatisticsWidget::setPlotData(const QJsonDocument &document)
{
    qDebug() << document;
    JsonToData jsonData(document);//please add jsonDocument
    m_moistureWidget->setSingleData(jsonData.getData("moisture"), "水分", QColor(220, 33, 40));
    m_greaseWidget->setSingleData(jsonData.getData("grease"), "油脂", QColor(21, 165, 140));
    m_tempWidget->setSingleData(jsonData.getData("temperature"), "温度", QColor(252, 133, 33));
    m_PHWidget->setSingleData(jsonData.getData("ph"), "PH值", QColor(121, 83, 70));

    QStringList otherList;
    otherList << "date" << "phone" << "deviceId";
    m_moistureTable->setTable("水分", jsonData.getOther("moisture", otherList), jsonData.getData("moisture"));
    m_greaseTable->setTable("油脂", jsonData.getOther("grease", otherList), jsonData.getData("grease"));
    m_tempTable->setTable("温度", jsonData.getOther("temperature", otherList), jsonData.getData("temperature"));
    m_PHTable->setTable("PH值", jsonData.getOther("ph", otherList), jsonData.getData("ph"));
}

void StatisticsWidget::getData()
{
    m_manager->downloadUserData();
}

void StatisticsWidget::clear()
{
    m_chartButton->click();
    m_moistureWidget->clearGraph();
    m_greaseWidget->clearGraph();
    m_tempWidget->clearGraph();
    m_PHWidget->clearGraph();
    m_moistureTable->clearTable();
    m_greaseTable->clearTable();
    m_tempTable->clearTable();
    m_PHTable->clearTable();
}

void StatisticsWidget::m_showSyncDialog()
{
    if(m_manager->account().isEmpty()) {
        MessageDialog dialog(this);
        dialog.execInformation(QStringLiteral("账号尚未登陆!"), QStringLiteral("同步"));
        return;
    }
    m_syncDialog = new SyncDialog(m_manager->account(), this);
    m_syncDialog->setWindowModality(Qt::WindowModal);
    m_syncDialog->setAttribute(Qt::WA_DeleteOnClose);
    m_syncDialog->show();
    connect(m_syncDialog, &SyncDialog::syncFinish, this, &StatisticsWidget::getData);
}

void StatisticsWidget::m_downloadDataReply(CustomNetwork::Status status)
{
    switch(status) {
    case CustomNetwork::Success:
        if(m_lastData != m_manager->userData()) {
            this->setPlotData(QJsonDocument::fromVariant(m_manager->userData()));
            m_lastData = m_manager->userData();
        }
        break;
    case CustomNetwork::Failure:
        break;
    case CustomNetwork::Timeout:
        break;
    default:
        break;
    }
}
