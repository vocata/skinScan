#include "helpwidget.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>

HelpWidget::HelpWidget(QWidget *parent) : QWidget(parent),
    m_descriptionLabel(new QLabel(QStringLiteral("感谢使用该皮肤检测软件, 点击观看相关的使用说明"), this)),
    m_imageLabel(new QLabel(this)),
    m_showButton(new QPushButton(QStringLiteral("观看视频"), this))
{
    m_imageLabel->setPixmap(QPixmap(":/help/icon/help"));
    m_imageLabel->setScaledContents(true);
    m_imageLabel->setFixedSize(325, 222);

    /* pushButton */
    m_showButton->setFixedSize(140, 40);

    /* connect */
    connect(m_showButton, &QPushButton::clicked, this, &HelpWidget::m_showVedio);

    /* layout */
    QGroupBox *groupBox = new QGroupBox(this);
    groupBox->setFixedWidth(500);
    QHBoxLayout *hBox = new QHBoxLayout(groupBox);
    hBox->addWidget(m_imageLabel);
    hBox->addWidget(m_showButton);

    QWidget *widget = new QWidget(this);
    widget->setFixedHeight(400);
    QVBoxLayout *vBox = new QVBoxLayout(widget);;
    vBox->addWidget(m_descriptionLabel, 0, Qt::AlignHCenter);
    vBox->addWidget(groupBox, 0, Qt::AlignHCenter);

    QHBoxLayout *allBox = new QHBoxLayout(this);
    allBox->addWidget(widget, 0, Qt::AlignTop);
    allBox->setContentsMargins(0, 20, 0, 0);

    /* windows attribution */
    this->setAttribute(Qt::WA_StyledBackground);
}

void HelpWidget::m_showVedio()
{
    QDesktopServices::openUrl(QUrl("http://www.youku.com/"));
}
