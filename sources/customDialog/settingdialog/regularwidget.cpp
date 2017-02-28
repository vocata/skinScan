#include "regularwidget.h"

#include <QButtonGroup>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QSettings>

#include <QDebug>

RegularWidget::RegularWidget(QWidget *parent) : QWidget(parent)
{
    m_loginLabel = new QLabel(QStringLiteral("登陆 :"), this);
    m_dataLabel = new QLabel(QStringLiteral("测量数据 :"), this);
    m_saveLoginInfoButton = new QRadioButton(QStringLiteral("保留登陆信息"), this);
    m_notSaveLoginInfoButton = new QRadioButton(QStringLiteral("不保留登陆信息"), this);
    m_saveToCloudButton = new QRadioButton(QStringLiteral("保存至云 (需要联网)"), this);
    m_saveToLocalButton = new QRadioButton(QStringLiteral("保存至本地"), this);
    m_loginButtonGroup = new QButtonGroup(this);
    m_dataButtonGroup = new QButtonGroup(this);

    /* radioButton */
    m_loginButtonGroup->addButton(m_saveLoginInfoButton, 0);
    m_loginButtonGroup->addButton(m_notSaveLoginInfoButton, 1);
    m_saveLoginInfoButton->setChecked(true);

    m_dataButtonGroup->addButton(m_saveToCloudButton, 0);
    m_dataButtonGroup->addButton(m_saveToLocalButton, 1);
    m_saveToCloudButton->setChecked(true);

    /* layout */
    m_loginLabel->move(40, 40);
    m_saveLoginInfoButton->move(80, 70);
    m_notSaveLoginInfoButton->move(230, 70);

    m_dataLabel->move(40, 120);
    m_saveToCloudButton->move(80, 150);
    m_saveToLocalButton->move(230, 150);

    /* recovery */
    this->m_recovery();
}

void RegularWidget::save()
{
    QSettings settings("./setting.ini", QSettings::IniFormat);
    settings.beginGroup("regular");
    settings.setValue("login", m_loginButtonGroup->checkedId());
    settings.setValue("data", m_dataButtonGroup->checkedId());
    settings.endGroup();
}

void RegularWidget::m_recovery()
{
    QSettings settings("./setting.ini", QSettings::IniFormat);
    settings.beginGroup("regular");
    QVariant login = settings.value("login");
    QVariant data = settings.value("data");
    settings.endGroup();

    /* login */
    if(!login.isNull()) {
        switch (login.toInt()) {
        case 0: m_saveLoginInfoButton->setChecked(true); break;
        case 1: m_notSaveLoginInfoButton->setChecked(true); break;
        default: break;
        }
    }

    /* data */
    if(!data.isNull()) {
        switch (data.toInt()) {
        case 0: m_saveToCloudButton->setChecked(true); break;
        case 1: m_saveToLocalButton->setChecked(true); break;
        default: break;
        }
    }
}
