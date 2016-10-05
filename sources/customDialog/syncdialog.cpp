#include "messagedialog.h"
#include "syncdialog.h"
#include "sources/sql/connection.h"

#include <QVBoxLayout>
#include <QSqlQueryModel>
#include <QTableView>
#include <QTabWidget>
#include <QHeaderView>
#include <QLabel>
#include <QJsonDocument>
#include <QTimer>
#include <QProgressBar>
#include <QToolButton>

#include <QDebug>

SyncDialog::SyncDialog(const QString &account, QWidget *parent) : CustomDialog(parent), m_account(account)
{
    createConnection();
    m_moistureModel = new QSqlQueryModel(this);
    m_greaseModel = new QSqlQueryModel(this);
    m_temperatureModel = new QSqlQueryModel(this);
    m_phModel = new QSqlQueryModel(this);
    m_moistureView = new QTableView(this);
    m_greaseView = new QTableView(this);
    m_temperatureView = new QTableView(this);
    m_phView = new QTableView(this);
    m_tabWidget = new QTabWidget(this);
    m_syncButton = new QToolButton(this);
    m_progressBar = new QProgressBar(this);
    m_manager = new CustomNetwork(this);
    m_timer = new QTimer(this);

    /* titleLabel */
    QLabel *titleLabel = new QLabel(QStringLiteral("本地数据"), this);

    /* tabWidget */
    m_tabWidget->addTab(m_moistureView, QIcon(":/statistics/icon/moisture"), QStringLiteral("水分"));
    m_tabWidget->addTab(m_greaseView, QIcon(":/statistics/icon/grease"), QStringLiteral("油脂"));
    m_tabWidget->addTab(m_temperatureView, QIcon(":/statistics/icon/temperature"), QStringLiteral("温度"));
    m_tabWidget->addTab(m_phView, QIcon(":/statistics/icon/PH"), QStringLiteral(" PH "));

    /* view */
    m_moistureView->setModel(m_moistureModel);
    m_greaseView->setModel(m_greaseModel);
    m_temperatureView->setModel(m_temperatureModel);
    m_phView->setModel(m_phModel);
    this->m_setTable();

    /* pushButton */
    m_syncButton->setText(QStringLiteral("立即同步"));
    m_syncButton->setFixedSize(70, 30);

    /* progressBar */
    m_progressBar->setMinimum(0);
    m_progressBar->setFixedSize(140, 18);
    m_progressBar->hide();

    /* layout */
    QHBoxLayout *hBox = new QHBoxLayout();
    hBox->addWidget(m_progressBar, 0, Qt::AlignLeft);
    hBox->addWidget(m_syncButton, 0, Qt::AlignRight);

    QVBoxLayout *vBox = new QVBoxLayout();
    vBox->addWidget(m_tabWidget);
    vBox->addLayout(hBox);

    /* connect */
    connect(m_syncButton, &QToolButton::clicked, this, &SyncDialog::sync);
    connect(m_timer, &QTimer::timeout, this, &SyncDialog::m_syncData);
    connect(m_manager, &CustomNetwork::uploadUserDataStatus, this, &SyncDialog::m_uploadDataReply);

    this->setWindowTitle(titleLabel);
    this->setCentralWidgetLayout(vBox);
    this->setShadow(true);
    this->hideMinIcon();
    this->setFixedSize(500, 400);
    this->startAnimation();
    this->centralWidget()->setObjectName("centralDialog");
}

void SyncDialog::m_setTable()
{
    /* model */
    m_moistureModel->setQuery(QString("select date, value, deviceId from moisture where phone = '%1'").arg(m_account));
    m_moistureModel->setHeaderData(0, Qt::Horizontal, QStringLiteral("测量日期"));
    m_moistureModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("水分"));
    m_moistureModel->setHeaderData(2, Qt::Horizontal, QStringLiteral("设备ID"));

    m_greaseModel->setQuery(QString("select date, value, deviceId from grease where phone = '%1'").arg(m_account));
    m_greaseModel->setHeaderData(0, Qt::Horizontal, QStringLiteral("测量日期"));
    m_greaseModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("油脂"));
    m_greaseModel->setHeaderData(2, Qt::Horizontal, QStringLiteral("设备ID"));

    m_temperatureModel->setQuery(QString("select date, value, deviceId from temperature where phone = '%1'").arg(m_account));
    m_temperatureModel->setHeaderData(0, Qt::Horizontal, QStringLiteral("测量日期"));
    m_temperatureModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("温度"));
    m_temperatureModel->setHeaderData(2, Qt::Horizontal, QStringLiteral("设备ID"));

    m_phModel->setQuery(QString("select date, value, deviceId from ph where phone = '%1'").arg(m_account));
    m_phModel->setHeaderData(0, Qt::Horizontal, QStringLiteral("测量日期"));
    m_phModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("PH"));
    m_phModel->setHeaderData(2, Qt::Horizontal, QStringLiteral("设备ID"));

    m_moistureView->setColumnWidth(0, 150);
    m_moistureView->setColumnWidth(1, 110);
    m_moistureView->setColumnWidth(2, 110);
    m_moistureView->horizontalHeader()->setStretchLastSection(true);
    m_moistureView->horizontalHeader()->setSectionsMovable(true);
    m_greaseView->setColumnWidth(0, 150);
    m_greaseView->setColumnWidth(1, 110);
    m_greaseView->setColumnWidth(2, 110);
    m_greaseView->horizontalHeader()->setStretchLastSection(true);
    m_greaseView->horizontalHeader()->setSectionsMovable(true);
    m_temperatureView->setColumnWidth(0, 150);
    m_temperatureView->setColumnWidth(1, 110);
    m_temperatureView->setColumnWidth(2, 110);
    m_temperatureView->horizontalHeader()->setStretchLastSection(true);
    m_temperatureView->horizontalHeader()->setSectionsMovable(true);
    m_phView->setColumnWidth(0, 150);
    m_phView->setColumnWidth(1, 110);
    m_phView->setColumnWidth(2, 110);
    m_phView->horizontalHeader()->setStretchLastSection(true);
    m_phView->horizontalHeader()->setSectionsMovable(true);
}

void SyncDialog::m_syncData()
{
     m_timer->stop();
    if(m_items.count() == 0) {
        /* 提示 */
        MessageDialog dialog(this);
        dialog.execInformation(QStringLiteral("本地没有数据!"), QStringLiteral("同步"));
        return;
    }
    if(m_iterator != m_items.end()) {
        QString item = m_iterator.key();
        QJsonDocument data = m_iterator.value();

        m_syncButton->setEnabled(false);
        m_syncButton->setText(QStringLiteral("正在同步"));
        m_progressBar->show();
        m_manager->uploadSingleUserData(item, data);
    } else {
        m_syncCount = 0;
        m_progressBar->hide();
        m_syncButton->setText(QStringLiteral("立即同步"));
        m_syncButton->setEnabled(true);

        /* 提示 */
        MessageDialog dialog(this);
        dialog.execInformation(QStringLiteral("数据同步完成!"), QStringLiteral("同步"));
    }
}

void SyncDialog::sync()
{
    for(int i = 0; i < m_moistureModel->rowCount(); ++i) {
        QString date = m_moistureModel->data(m_moistureModel->index(i, 0)).toString();
        double value = m_moistureModel->data(m_moistureModel->index(i, 1)).toDouble();
        qint64 deviceId = m_moistureModel->data(m_moistureModel->index(i, 2)).toLongLong();
        QJsonDocument doc = m_formatUploadData(date, value, deviceId, m_manager->account());
        m_items.insert("moisture", doc);
    }
    for(int i = 0; i < m_greaseModel->rowCount(); ++i) {
        QString date = m_greaseModel->data(m_greaseModel->index(i, 0)).toString();
        double value = m_greaseModel->data(m_greaseModel->index(i, 1)).toDouble();
        qint64 deviceId = m_greaseModel->data(m_greaseModel->index(i, 2)).toLongLong();
        QJsonDocument doc = m_formatUploadData(date, value, deviceId, m_manager->account());
        m_items.insert("grease", doc);
    }
    for(int i = 0; i < m_temperatureModel->rowCount(); ++i) {
        QString date = m_temperatureModel->data(m_temperatureModel->index(i, 0)).toString();
        double value = m_temperatureModel->data(m_temperatureModel->index(i, 1)).toDouble();
        qint64 deviceId = m_temperatureModel->data(m_temperatureModel->index(i, 2)).toLongLong();
        QJsonDocument doc = m_formatUploadData(date, value, deviceId, m_manager->account());
        m_items.insert("temperature", doc);
    }
    for(int i = 0; i < m_phModel->rowCount(); ++i) {
        QString date = m_phModel->data(m_phModel->index(i, 0)).toString();
        double value = m_phModel->data(m_phModel->index(i, 1)).toDouble();
        qint64 deviceId = m_phModel->data(m_phModel->index(i, 2)).toLongLong();
        QJsonDocument doc = m_formatUploadData(date, value, deviceId, m_manager->account());
        m_items.insert("ph", doc);
    }
    m_iterator = m_items.begin();
    m_progressBar->setMaximum(m_items.count());

    m_timer->start(20);
}

SyncDialog::~SyncDialog()
{
    closeConnection();
    m_timer->stop();
}

void SyncDialog::closeEvent(QCloseEvent *)
{
    emit syncFinish();
    this->accept();
}

void SyncDialog::m_uploadDataReply(CustomNetwork::Status status)
{
    switch(status) {
    case CustomNetwork::Success: {
        /* 删除已经同步的数据库数据 */
        QString date = m_iterator.value().toVariant().toList().at(0).toMap().value("date").toString();
        QSqlQuery query;
        query.exec(QString("delete from %1 where date = '%2'").arg(m_iterator.key(), date));
        /* 刷新视图 */
        m_moistureModel->setQuery(QString("select date, value, deviceId from moisture where phone = '%1'").arg(m_account));
        m_greaseModel->setQuery(QString("select date, value, deviceId from grease where phone = '%1'").arg(m_account));
        m_temperatureModel->setQuery(QString("select date, value, deviceId from temperature where phone = '%1'").arg(m_account));
        m_phModel->setQuery(QString("select date, value, deviceId from ph where phone = '%1'").arg(m_account));
        /* 递增迭代器, 同步下一个数据 */
        ++m_iterator;
        ++m_syncCount;
        m_progressBar->setValue(m_syncCount);
        m_timer->start(20);
    }
        break;
    case CustomNetwork::Failure:
        break;
    case CustomNetwork::Timeout:
        break;
    }
}

QJsonDocument SyncDialog::m_formatUploadData(const QString &date, double value, qint64 deviceId, const QString &phone)
{
    QVariantList array;
    QVariantMap object;

    object.insert("date", date);
    object.insert("value", value);
    object.insert("deviceId", deviceId);
    object.insert("phone", phone);

    array.push_back(object);
    return QJsonDocument::fromVariant(array);
}
