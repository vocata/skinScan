#include "settingdialog.h"

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <qtoolbutton.h>

#include "sources/customDialog/settingdialog/networkwidget.h"
#include "sources/customDialog/settingdialog/regularwidget.h"

#include <QDebug>

SettingDialog::SettingDialog(QWidget *parent) : CustomDialog(parent)
{
    m_regularButton = new QToolButton(this);
    m_networkButton = new QToolButton(this);
    m_stackedWidget = new QStackedWidget(this);
    m_regularWidget = new RegularWidget(this);
    m_networkWidget = new NetworkWidget(this);
    m_confirmButton = new QToolButton(this);
    m_cancelButton = new QToolButton(this);

    /* toolButton */
    m_regularButton->setText(QStringLiteral("常规"));
    m_regularButton->setCheckable(true);
    m_regularButton->setChecked(true);
    m_regularButton->setFixedSize(80, 30);
    m_regularButton->setObjectName("regularButton");

    m_networkButton->setText(QStringLiteral("网络"));
    m_networkButton->setCheckable(true);
    m_networkButton->setFixedSize(80, 30);
    m_networkButton->setObjectName("networkButton");

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(m_regularButton, 0);
    buttonGroup->addButton(m_networkButton, 1);

    m_confirmButton->setText(QStringLiteral("确认"));
    m_confirmButton->setFixedSize(60, 30);
    m_confirmButton->setObjectName("confirmButton");

    m_cancelButton->setText(QStringLiteral("取消"));
    m_cancelButton->setFixedSize(60, 30);
    m_cancelButton->setObjectName("cancelButton");

    /* widget */
    m_regularWidget->setObjectName("regularWidget");
    m_networkWidget->setObjectName("networkWidget");

    /* stackedWidget */
    m_stackedWidget->addWidget(m_regularWidget);
    m_stackedWidget->addWidget(m_networkWidget);

    /* titleLabel */
    QLabel *titleLabel = new QLabel(QStringLiteral("设置"));
    titleLabel->setObjectName("titleLabel");

    /* layout */
    QWidget *leftWiget = new QWidget(this);
    leftWiget->setObjectName("leftWidget");
    QVBoxLayout *buttonBox = new QVBoxLayout(leftWiget);
    buttonBox->addWidget(m_regularButton);
    buttonBox->addWidget(m_networkButton);
    buttonBox->setAlignment(m_networkButton, Qt::AlignTop);
    buttonBox->setMargin(0);
    buttonBox->setSpacing(0);

    QHBoxLayout *bottomBox = new QHBoxLayout();
    bottomBox->addWidget(m_confirmButton);
    bottomBox->addWidget(m_cancelButton);
    bottomBox->setContentsMargins(0, 10, 10, 10);
    bottomBox->setSpacing(10);

    QVBoxLayout *vBox = new QVBoxLayout();
    vBox->addWidget(m_stackedWidget);
    vBox->addLayout(bottomBox);
    vBox->setAlignment(bottomBox, Qt::AlignBottom | Qt::AlignRight);
    vBox->setMargin(0);
    vBox->setSpacing(0);

    QHBoxLayout *hBox = new QHBoxLayout();
    hBox->addWidget(leftWiget);
    hBox->addLayout(vBox);
    hBox->setContentsMargins(0, 10, 0, 0);
    hBox->setSpacing(0);

    /* connect */
    connect(buttonGroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [=](int index) { m_stackedWidget->setCurrentIndex(index); });

    connect(m_confirmButton, &QPushButton::clicked, this, &SettingDialog::m_confirm);
    connect(m_cancelButton, &QPushButton::clicked, this, &SettingDialog::m_cancel);

    /* windows attribution */
    this->setWindowTitle(titleLabel);
    this->setCentralWidgetLayout(hBox);
    this->setShadow(true);
    this->hideMinIcon();
    this->setFixedSize(600, 400);
    this->startAnimation();
    this->centralWidget()->setObjectName("centralDialog");
}

void SettingDialog::m_confirm()
{
    m_regularWidget->save();
    m_networkWidget->save();
    this->accept();
}

void SettingDialog::m_cancel()
{

    this->reject();
}
