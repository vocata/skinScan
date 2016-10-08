#include "measurewidget.h"
#include "sources/chart/barchart.h"
#include "sources/userclass/usbstatueshare.h"
#include "sources/userclass/customdialog.h"
#include "sources/userclass/customnetwork.h"
#include "sources/customDialog/questionnairedialog.h"
#include "sources/customDialog/cameradialog.h"
#include "sources/customDialog/albumdialog.h"
#include "sources/customDialog/messagedialog.h"
#include "sources/sql/connection.h"

#include <QFrame>
#include <QGridLayout>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QDateTime>
#include <QMetaType>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>

#include <QDebug>


MeasureWidget::MeasureWidget(QWidget *parent) : QWidget(parent)
{
    m_startMeasureButton = new QPushButton(this);
    m_skinEvaluationButton = new QPushButton(this);
    m_takePhotoButton = new QPushButton(this);
    m_showPhotoButton = new QPushButton(this);
    m_printReasultButton = new QPushButton(this);
    m_saveResultButton = new QPushButton(this);
    m_moisture = new QPushButton(this);
    m_grease = new QPushButton(this);
    m_temperature = new QPushButton(this);
    m_PH = new QPushButton(this);
    m_moistureInfo = new QPlainTextEdit(this);
    m_greaseInfo = new QPlainTextEdit(this);
    m_temperatureInfo = new QPlainTextEdit(this);
    m_PHInfo = new QPlainTextEdit(this);
    m_moistureBar = new BarChart(this);
    m_greaseBar = new BarChart(this);
    m_temperatureBar = new BarChart(this);
    m_PHBar = new BarChart(this);
    m_manager = new CustomNetwork(this);

    /* QPushButton */
    m_startMeasureButton->setText(QStringLiteral("开始检测"));
    m_startMeasureButton->setFixedHeight(25);

    m_skinEvaluationButton->setText(QStringLiteral("皮肤评价"));
    m_skinEvaluationButton->setFixedHeight(25);

    m_takePhotoButton->setText(QStringLiteral("皮肤拍照"));
    m_takePhotoButton->setFixedHeight(25);

    m_showPhotoButton->setText(QStringLiteral("查看图片"));
    m_showPhotoButton->setFixedHeight(25);

    m_printReasultButton->setText(QStringLiteral("打印结果"));
    m_printReasultButton->setFixedHeight(25);

    m_saveResultButton->setText(QStringLiteral("保存纪录"));
    m_saveResultButton->setFixedHeight(25);

    m_moisture->setText(QStringLiteral("水分"));
    m_moisture->setIcon(QIcon(":/measure/button/icon/tip"));
    m_moisture->setFocusPolicy(Qt::NoFocus);
    m_moisture->setIconSize(QSize(16, 16));

    m_grease->setText(QStringLiteral("油脂"));
    m_grease->setIcon(QIcon(":/measure/button/icon/tip"));
    m_grease->setFocusPolicy(Qt::NoFocus);
    m_grease->setIconSize(QSize(16, 16));

    m_temperature->setText(QStringLiteral("温度"));
    m_temperature->setIcon(QIcon(":/measure/button/icon/tip"));
    m_temperature->setFocusPolicy(Qt::NoFocus);
    m_temperature->setIconSize(QSize(16, 16));

    m_PH->setText(QStringLiteral("PH值"));
    m_PH->setIcon(QIcon(":/measure/button/icon/tip"));
    m_PH->setFocusPolicy(Qt::NoFocus);
    m_PH->setIconSize(QSize(16, 16));

    /* QPlainTextEdit */
    m_moistureInfo->setPlainText(QStringLiteral("水分含量: 无数据"));
    m_moistureInfo->setReadOnly(true);
    m_moistureInfo->setFixedSize(230, 50);

    m_greaseInfo->setPlainText(QStringLiteral("油脂含量: 无数据"));
    m_greaseInfo->setReadOnly(true);
    m_greaseInfo->setFixedSize(230, 50);

    m_temperatureInfo->setPlainText(QStringLiteral("皮肤温度：无数据"));
    m_temperatureInfo->setReadOnly(true);
    m_temperatureInfo->setFixedSize(230, 50);

    m_PHInfo->setPlainText(QStringLiteral("PH值: 无数据"));
    m_PHInfo->setReadOnly(true);
    m_PHInfo->setFixedSize(230, 50);
    m_PHInfo->setObjectName("PHInfo");

    /* line */
    QFrame *line = new QFrame(this);
    line->setFixedSize(200, 1);
    line->setFrameShape(QFrame::HLine);
    line->setObjectName("line");

    /* BarChart */
    m_moistureBar->setBarColor(QColor(220, 33, 40), Qt::gray);
    m_moistureBar->setLeftText(QStringLiteral("水分(单位  %)"));
    m_moistureBar->setData(20);
    m_moistureBar->setBarIndex(Moisture);

    m_greaseBar->setBarColor(QColor(21, 165, 140), Qt::gray);
    m_greaseBar->setLeftText(QStringLiteral("油脂(单位  %)"));
    m_greaseBar->setData(40);
    m_greaseBar->setBarIndex(Grease);

    m_temperatureBar->setBarColor(QColor(252, 133, 33), Qt::gray);
    m_temperatureBar->setLeftText(QStringLiteral("温度(单位  ℃)"));
    m_temperatureBar->setBarRange(0, 50);
    m_temperatureBar->setData(37);
    m_temperatureBar->setBarIndex(Temperature);

    m_PHBar->setBarColor(QColor(121, 83, 70), Qt::gray);
    m_PHBar->setLeftText(QStringLiteral("PH值(单位 PH)"));
    m_PHBar->setBarRange(0, 14);
    m_PHBar->setData(5.9);
    m_PHBar->setBarIndex(PH);

    /* layout */
    QWidget *leftTopWidget = new QWidget(this);
    leftTopWidget->setObjectName("leftTopWidget");
    QGridLayout *buttonBox = new QGridLayout(leftTopWidget);
    buttonBox->addWidget(m_startMeasureButton, 0, 0, 1, 1);
    buttonBox->addWidget(m_skinEvaluationButton, 0, 1, 1, 1);
    buttonBox->addWidget(m_takePhotoButton, 1, 0, 1, 1);
    buttonBox->addWidget(m_showPhotoButton, 1, 1, 1, 1);
    buttonBox->addWidget(m_printReasultButton, 2, 0, 1, 1);
    buttonBox->addWidget(m_saveResultButton, 2, 1, 1, 1);
    buttonBox->setHorizontalSpacing(25);

    QWidget *leftBottomWidget = new QWidget(this);
    leftBottomWidget->setObjectName("leftBottomWidget");
    QVBoxLayout *formBox = new QVBoxLayout(leftBottomWidget);
    formBox->addWidget(m_moisture);
    formBox->addWidget(m_moistureInfo);
    formBox->addWidget(m_grease);
    formBox->addWidget(m_greaseInfo);
    formBox->addWidget(m_temperature);
    formBox->addWidget(m_temperatureInfo);
    formBox->addWidget(m_PH);
    formBox->addWidget(m_PHInfo);
    formBox->setAlignment(m_moisture, Qt::AlignLeft);
    formBox->setAlignment(m_grease, Qt::AlignLeft);
    formBox->setAlignment(m_temperature, Qt::AlignLeft);
    formBox->setAlignment(m_PH, Qt::AlignLeft);
    formBox->setSpacing(5);
    formBox->setMargin(0);

    QGroupBox *leftWidget = new QGroupBox(this);
    leftWidget->setObjectName("leftWidget");
    QVBoxLayout *leftBox = new QVBoxLayout(leftWidget);
    leftBox->addWidget(leftTopWidget);
    leftBox->addWidget(line);
    leftBox->addWidget(leftBottomWidget);
    leftBox->setAlignment(line, Qt::AlignHCenter);
    leftBox->setSpacing(10);
    leftBox->setMargin(10);

    QGroupBox *rightWidget = new QGroupBox(this);
    rightWidget->setObjectName("rightWidget");
    QGridLayout *rightBox = new QGridLayout(rightWidget);
    rightBox->addWidget(m_moistureBar, 0, 0, 1, 1);
    rightBox->addWidget(m_greaseBar, 0, 1, 1, 1);
    rightBox->addWidget(m_temperatureBar, 1, 0, 1, 1);
    rightBox->addWidget(m_PHBar, 1, 1, 1, 1);
    rightBox->setSpacing(10);
    rightBox->setMargin(10);

    QHBoxLayout *hBox = new QHBoxLayout(this);
    hBox->addWidget(leftWidget);
    hBox->addWidget(rightWidget);
    hBox->setAlignment(leftWidget, Qt::AlignLeft);
    hBox->setSpacing(0);
    hBox->setMargin(0);

    /* connect */
    /* button */
    connect(m_startMeasureButton, &QPushButton::clicked, this, &MeasureWidget::m_startMeasure); //打开检测线程
    connect(m_skinEvaluationButton, &QPushButton::clicked, this, &MeasureWidget::m_skinEvaluation);
    connect(m_takePhotoButton, &QPushButton::clicked, this, &MeasureWidget::m_takePhoto);
    connect(m_showPhotoButton, &QPushButton::clicked, this, &MeasureWidget::m_showPhoto);
    connect(m_printReasultButton, &QPushButton::clicked, this, &MeasureWidget::m_printReasult);
    connect(m_saveResultButton, &QPushButton::clicked, this, &MeasureWidget::m_saveReasult);
    /* usb */
    connect(&m_usbMeasure, &UsbMeasure::usbDisconnect, this, &MeasureWidget::m_usbPullOut);    //usb设备突然拔出处理
    qRegisterMetaType<QByteArray>("QByteArray");        //跨线程注册QByteArray
    connect(&m_usbMeasure, &UsbMeasure::readyRead, this, &MeasureWidget::m_dataHandle);
    /* textEdit show */
    connect(m_moistureBar, &BarChart::plotFinish, this, &MeasureWidget::m_setSuggestion);
    connect(m_greaseBar, &BarChart::plotFinish, this, &MeasureWidget::m_setSuggestion);
    connect(m_temperatureBar, &BarChart::plotFinish, this, &MeasureWidget::m_setSuggestion);
    connect(m_PHBar, &BarChart::plotFinish, this, &MeasureWidget::m_setSuggestion);
    /* network */
    connect(m_manager, &CustomNetwork::uploadUserDataStatus, this, &MeasureWidget::m_uploadDataReply);
}

void MeasureWidget::clear()
{
    m_moistureInfo->setPlainText(QStringLiteral("水分含量: 无数据"));
    m_greaseInfo->setPlainText(QStringLiteral("油脂含量: 无数据"));
    m_temperatureInfo->setPlainText(QStringLiteral("皮肤温度: 无数据"));
    m_PHInfo->setPlainText(QStringLiteral("PH值: 无数据"));

    m_moistureBar->clearData();
    m_greaseBar->clearData();
    m_temperatureBar->clearData();
    m_PHBar->clearData();

    /* data store */
    for(int i = 0; i < 4; ++i) {
        m_dataStore[i].clear();
    }

    /* measure thread */
    m_usbMeasure.stop();
    m_startMeasureButton->setText(QStringLiteral("开始检测"));
}

void MeasureWidget::m_startMeasure()
{
    if(!UsbStatueShare::usbStatus()) {
        MessageDialog dialog(this);
        dialog.execInformation(QStringLiteral("检测设备尚未连接!"), QStringLiteral("检测"));
        return;
    }
    if(m_startMeasureButton->text() == QStringLiteral("开始检测")) {
        m_usbMeasure.start();
        m_startMeasureButton->setText(QStringLiteral("停止检测"));
    } else {
        m_usbMeasure.stop();
        m_startMeasureButton->setText(QStringLiteral("开始检测"));
    }
}

void MeasureWidget::m_skinEvaluation()
{
    QuestionnaireDialog *dialog = new QuestionnaireDialog(this);
    dialog->setWindowModality(Qt::WindowModal);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void MeasureWidget::m_takePhoto()
{
    if(m_manager->hasMember()) {
        CameraDialog *dialog = new CameraDialog(m_manager->account(), this);
        dialog->setWindowModality(Qt::WindowModal);
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->show();
    } else {
        MessageDialog dialog(this);
        dialog.execInformation(QStringLiteral("请登录!"), QStringLiteral("登陆"));
    }
}

void MeasureWidget::m_showPhoto()
{
    if(m_manager->hasMember()) {
        AlbumDialog *dialog = new AlbumDialog(m_manager->account(), this);
        dialog->setWindowModality(Qt::WindowModal);
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->show();
    } else {
        MessageDialog dialog(this);
        dialog.execInformation(QStringLiteral("请登录!"), QStringLiteral("登陆"));
    }
}

void MeasureWidget::m_printReasult()
{
    if(m_manager->hasMember()) {

    } else {
        MessageDialog dialog(this);
        dialog.execInformation(QStringLiteral("请登录!"), QStringLiteral("登陆"));
    }
}

void MeasureWidget::m_saveReasult()
{
    if(m_manager->hasMember()) {
        if(m_dataStore[0].hasData() || m_dataStore[1].hasData() || m_dataStore[2].hasData() || m_dataStore[3].hasData()) {

            QSettings settings("setting.ini", QSettings::IniFormat);
            settings.beginGroup("regular");
            int selected = settings.value("data").toInt();
            settings.endGroup();

            if(selected) {
                this->m_saveUserData();     //提交到本地数据库
            } else {
                QJsonDocument document = this->m_formatUploadData();
                m_manager->uploadUserData(document);        //提交到服务器
            }

            /* 设置已经提交标志 */
            m_commit = true;
        } else {
            /* 提示没有数据 */
            MessageDialog dialog(this);
            dialog.execInformation(QStringLiteral("当前没有数据可以保存!"), QStringLiteral("保存"));
        }
    } else {
        /* 提示注册会员 */
        MessageDialog dialog(this);
        dialog.execInformation(QStringLiteral("请登录!"), QStringLiteral("登陆"));
    }
}

void MeasureWidget::m_usbPullOut()
{
    m_startMeasureButton->setText(QStringLiteral("开始检测"));
}

void MeasureWidget::m_dataHandle(const QByteArray &data)
{
    /* set deviceId */
    quint64 deviceId = 0;
    for(int i = 0; i < 8; ++i) {
        deviceId = (deviceId << 8) + data.at(i);
    }

    switch(data.at(8)) {
    case Moisture:
        m_moistureBar->setData(data.at(9));
        m_dataStore[0].data = data.at(9) / 100;
        m_dataStore[0].measureTime = QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss");
        m_dataStore[0].deviceId = deviceId;
        m_dataStore[0].account = m_manager->account();    //无账号插入不了数据库和提交网络
        break;
    case Grease:
        m_greaseBar->setData(data.at(9));
        m_dataStore[1].data = data.at(9) / 100;
        m_dataStore[1].measureTime = QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss");
        m_dataStore[1].deviceId = deviceId;
        m_dataStore[1].account = m_manager->account();
        break;
    case PH:
        m_PHBar->setData(data.at(9) / 10);
        m_dataStore[2].data = data.at(9) / 10;
        m_dataStore[2].measureTime = QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss");
        m_dataStore[2].deviceId = deviceId;
        m_dataStore[2].account = m_manager->account();
        break;
    case Temperature:
        m_temperatureBar->setData(data.at(9) + data.at(10) / 10);
        m_dataStore[3].data = data.at(9) + data.at(10) / 10;
        m_dataStore[3].measureTime = QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss");
        m_dataStore[3].deviceId = deviceId;
        m_dataStore[3].account = m_manager->account();
        break;
    default: break;
    }
    /* 有新数据,将提交标志复位 */
    m_commit = false;
}

void MeasureWidget::m_setSuggestion(const double &data, const qint16 &dataIndex)
{
    switch(dataIndex) {
    case Moisture:
        m_moistureInfo->setPlainText(QStringLiteral("水分含量: %1%").arg(data));
        break;
    case Grease:
        m_greaseInfo->setPlainText(QStringLiteral("油脂含量: %1%").arg(data));
        break;
    case PH:
        m_PHInfo->setPlainText(QStringLiteral("PH值: %1").arg(data));
        break;
    case Temperature:
        m_temperatureInfo->setPlainText(QStringLiteral("皮肤温度: %1℃").arg(data));
        break;
    default: break;
    }
}

void MeasureWidget::m_uploadDataReply(CustomNetwork::Status status)
{
    qDebug() << status;
    switch(status) {
    case CustomNetwork::Success: {
            MessageDialog dialog(this);
            dialog.execInformation(QStringLiteral("保存成功!"), QStringLiteral("保存"));
            qDebug() << "uploadDataReply -> 提交成功";
        }
        break;
    case CustomNetwork::Failure:
        qDebug() << "uploadDataReply -> 提交失败";
        break;
    case CustomNetwork::Timeout:
        qDebug() << "uploadDataReply -> 网络超时";
        break;
    default:
        break;
    }
}

void MeasureWidget::m_saveUserData()
{
    createConnection();

    QSqlQuery query;
    if(m_dataStore[0].hasData()) {
        query.exec(QString("insert into moisture values('%1', '%2', %3, %4)")
                   .arg(m_dataStore[0].account).arg(m_dataStore[0].measureTime)
                   .arg(m_dataStore[0].deviceId).arg(m_dataStore[0].data));
    }
    if(m_dataStore[1].hasData()) {
        query.exec(QString("insert into grease values('%1', '%2', %3, %4)")
                   .arg(m_dataStore[1].account).arg(m_dataStore[1].measureTime)
                   .arg(m_dataStore[1].deviceId).arg(m_dataStore[1].data));
    }
    if(m_dataStore[2].hasData()) {
        query.exec(QString("insert into temperature values('%1', '%2', %3, %4)")
                   .arg(m_dataStore[2].account).arg(m_dataStore[2].measureTime)
                   .arg(m_dataStore[2].deviceId).arg(m_dataStore[2].data));
    }
    if(m_dataStore[3].hasData()) {
        query.exec(QString("insert into ph values('%1', '%2', %3, %4)")
                   .arg(m_dataStore[3].account).arg(m_dataStore[3].measureTime)
                   .arg(m_dataStore[3].deviceId).arg(m_dataStore[3].data));
    }

    closeConnection();

    MessageDialog dialog(this);
    dialog.execInformation(QStringLiteral("保存成功!"), QStringLiteral("保存"));
}

QJsonDocument MeasureWidget::m_formatUploadData()
{
    QVariantList moistureArr;
    QVariantList greaseArr;
    QVariantList temperatureArr;
    QVariantList phArr;

    if(m_dataStore[0].hasData()) {
        QVariantMap moisture;
        moisture.insert("date", m_dataStore[0].measureTime);
        moisture.insert("deviceId", m_dataStore[0].deviceId);
        moisture.insert("phone", m_dataStore[0].account);
        moisture.insert("value", m_dataStore[0].data);

        moistureArr.push_back(moisture);
    }
    if(m_dataStore[1].hasData()) {
        QVariantMap grease;
        grease.insert("date", m_dataStore[1].measureTime);
        grease.insert("deviceId", m_dataStore[1].deviceId);
        grease.insert("phone", m_dataStore[1].account);
        grease.insert("value", m_dataStore[1].data);

        greaseArr.push_back(grease);
    }
    if(m_dataStore[2].hasData()) {
        QVariantMap temperature;
        temperature.insert("date", m_dataStore[2].measureTime);
        temperature.insert("deviceId", m_dataStore[2].deviceId);
        temperature.insert("phone", m_dataStore[2].account);
        temperature.insert("value", m_dataStore[2].data);

        temperatureArr.push_back(temperature);
    }
    if(m_dataStore[3].hasData()) {
        QVariantMap ph;
        ph.insert("date", m_dataStore[3].measureTime);
        ph.insert("deviceId", m_dataStore[3].deviceId);
        ph.insert("phone", m_dataStore[3].account);
        ph.insert("value", m_dataStore[3].data);

        phArr.push_back(ph);
    }

    QVariantMap obj;
    obj.insert("moisture", moistureArr);
    obj.insert("grease", greaseArr);
    obj.insert("temperature", temperatureArr);
    obj.insert("ph", phArr);

    return QJsonDocument::fromVariant(obj);
}
