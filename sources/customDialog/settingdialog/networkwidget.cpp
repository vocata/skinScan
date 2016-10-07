#include "networkwidget.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QLabel>
#include <QRadioButton>
#include <QSettings>

NetworkWidget::NetworkWidget(QWidget *parent) : QWidget(parent)
{
    m_syncLabel = new QLabel(QStringLiteral("同步 :"), this);
    m_moistureChecked = new QCheckBox(QStringLiteral("同步皮肤水分数据"), this);
    m_greaseChecked = new QCheckBox(QStringLiteral("同步皮肤油脂数据"), this);
    m_temperatureChecked = new QCheckBox(QStringLiteral("同步皮肤温度数据"), this);
    m_phChecked = new QCheckBox(QStringLiteral("同步皮肤PH值数据"), this);

    /* checkBox */
    m_moistureChecked->setChecked(true);
    m_greaseChecked->setChecked(true);
    m_temperatureChecked->setChecked(true);
    m_phChecked->setChecked(true);

    /* layout */
    m_syncLabel->move(40, 40);
    m_moistureChecked->move(80, 70);
    m_greaseChecked->move(80, 105);
    m_temperatureChecked->move(80, 140);
    m_phChecked->move(80, 175);

    /* recovery */
    this->m_recovery();
}

void NetworkWidget::save()
{
    QSettings settings("setting.ini", QSettings::IniFormat);
    settings.beginGroup("network");
    settings.setValue("moisture", m_moistureChecked->isChecked());
    settings.setValue("grease", m_greaseChecked->isChecked());
    settings.setValue("temperature", m_temperatureChecked->isChecked());
    settings.setValue("ph", m_phChecked->isChecked());
    settings.endGroup();
}

void NetworkWidget::m_recovery()
{
    QSettings settings("setting.ini", QSettings::IniFormat);
    settings.beginGroup("network");
    QVariant moistuerIsChecked = settings.value("moisture");
    QVariant greaseIsChecked = settings.value("grease");
    QVariant temperatureIsChecked = settings.value("temperature");
    QVariant phIsChecked = settings.value("ph");
    settings.endGroup();

    /* setter */
    if(!moistuerIsChecked.isNull()) {
        m_moistureChecked->setChecked(moistuerIsChecked.toBool());
    }
    if(!greaseIsChecked.isNull()) {
        m_greaseChecked->setChecked(greaseIsChecked.toBool());
    }
    if(!temperatureIsChecked.isNull()) {
        m_temperatureChecked->setChecked(temperatureIsChecked.toBool());
    }
    if(!phIsChecked.isNull()) {
        m_phChecked->setChecked(phIsChecked.toBool());
    }
}
