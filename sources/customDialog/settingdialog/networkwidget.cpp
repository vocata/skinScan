#include "networkwidget.h"

#include <QButtonGroup>
#include <QLabel>
#include <QRadioButton>
#include <QSettings>

NetworkWidget::NetworkWidget(QWidget *parent) : QWidget(parent)
{
    m_syncLabel = new QLabel(QStringLiteral("同步 :"), this);
    m_autoSyncRadioButton = new QRadioButton(QStringLiteral("软件开启时同步 (推荐)"), this);
    m_manualSyncRadioButton = new QRadioButton(QStringLiteral("手动同步"), this);
    m_syncButtonGroup = new QButtonGroup(this);

    /* radioButton */
    m_syncButtonGroup->addButton(m_autoSyncRadioButton, 0);
    m_syncButtonGroup->addButton(m_manualSyncRadioButton, 1);
    m_autoSyncRadioButton->setChecked(true);

    /* layout */
    m_syncLabel->move(40, 40);
    m_autoSyncRadioButton->move(80, 70);
    m_manualSyncRadioButton->move(230, 70);

    /* recovery */
    this->m_recovery();
}

void NetworkWidget::save()
{
    QSettings settings("setting.ini", QSettings::IniFormat);
    settings.beginGroup("network");
    settings.setValue("sync", m_syncButtonGroup->checkedId());
    settings.endGroup();
}

void NetworkWidget::m_recovery()
{
    QSettings settings("setting.ini", QSettings::IniFormat);
    settings.beginGroup("network");
    QVariant sync = settings.value("sync");
    settings.endGroup();

    /* sync */
    if(!sync.isNull()) {
        switch (sync.toInt()) {
        case 0:
            m_autoSyncRadioButton->setChecked(true);
            break;
        case 1:
            m_manualSyncRadioButton->setChecked(true);
        default:
            break;
        }
    }
}
