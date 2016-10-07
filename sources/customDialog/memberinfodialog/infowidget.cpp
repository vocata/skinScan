#include "infowidget.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QVariantMap>

InfoWidget::InfoWidget(QWidget *parent) : QWidget(parent),
    m_phone(new QLabel(QStringLiteral("账   号: "), this)),
    m_phoneInfo(new QLabel(this)),
    m_name(new QLabel(QStringLiteral("用户名: "), this)),
    m_nameInfo(new QLabel(this)),
    m_qq(new QLabel(QStringLiteral("Q    Q: "), this)),
    m_qqInfo(new QLabel(this)),
    m_email(new QLabel(QStringLiteral("E-mail: "), this)),
    m_emailInfo(new QLabel(this)),
    m_sex(new QLabel(QStringLiteral("性   别: "), this)),
    m_sexInfo(new QLabel(this)),
    m_birthday(new QLabel(QStringLiteral("生   日: "), this)),
    m_birthdayInfo(new QLabel(this)),
    m_age(new QLabel(QStringLiteral("年   龄: "), this)),
    m_ageInfo(new QLabel(this))
{
    /* label */
    m_phone->setFixedWidth(40);
    m_name->setFixedWidth(40);
    m_qq->setFixedWidth(40);
    m_email->setFixedWidth(40);
    m_sex->setFixedWidth(40);
    m_birthday->setFixedWidth(40);
    m_age->setFixedWidth(40);

    /* layout */
    QGridLayout *gBox = new QGridLayout(this);
    gBox->addWidget(m_phone, 0, 0, 1, 1);
    gBox->addWidget(m_phoneInfo, 0, 1, 1, 1);
    gBox->addWidget(m_name, 1, 0, 1, 1);
    gBox->addWidget(m_nameInfo, 1, 1, 1, 1);
    gBox->addWidget(m_qq, 2, 0, 1, 1);
    gBox->addWidget(m_qqInfo, 2, 1, 1, 1);
    gBox->addWidget(m_email, 3, 0, 1, 1);
    gBox->addWidget(m_emailInfo, 3, 1, 1, 1);
    gBox->addWidget(m_birthday, 4, 0, 1, 1);
    gBox->addWidget(m_birthdayInfo, 4, 1, 1, 1);
    gBox->addWidget(m_sex, 5, 0, 1, 1);
    gBox->addWidget(m_sexInfo, 5, 1, 1, 1);
    gBox->addWidget(m_age, 6, 0, 1, 1);
    gBox->addWidget(m_ageInfo, 6, 1, 1, 1);
    gBox->setHorizontalSpacing(20);
    gBox->setVerticalSpacing(10);
}

void InfoWidget::setInfo(QVariantMap info)
{
    m_phoneInfo->setText(info.value("phone").toString());
    m_nameInfo->setText(info.value("name").toString());
    m_qqInfo->setText(info.value("qq").toString());
    m_emailInfo->setText(info.value("email").toString());
    m_sexInfo->setText(info.value("sex").toString());
    m_birthdayInfo->setText(info.value("birthday").toString());
    m_ageInfo->setText(info.value("age").toString());
}
