#include "editwidget.h"
#include "sources/userclass/customnetwork.h"
#include "sources/customDialog/memberinfodialog/editwidget/dateedit.h"

#include <QComboBox>
#include <QDateTime>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QMenu>
#include <QPushButton>
#include <QWidgetAction>


EditWidget::EditWidget(QWidget *parent) : QWidget(parent),
    m_phone(new QLabel(QStringLiteral("账   号: "), this)),
    m_phoneInfo(new QLineEdit(this)),
    m_name(new QLabel(QStringLiteral("用户名: "), this)),
    m_nameInfo(new QLineEdit(this)),
    m_qq(new QLabel(QStringLiteral("Q    Q: "), this)),
    m_qqInfo(new QLineEdit(this)),
    m_email(new QLabel(QStringLiteral("E-mail: "), this)),
    m_emailInfo(new QLineEdit(this)),
    m_sex(new QLabel(QStringLiteral("性   别: "), this)),
    m_sexInfo(new QComboBox(this)),
    m_birthday(new QLabel(QStringLiteral("生   日: "), this)),
    m_birthdayInfo(new QPushButton(this)),
    m_age(new QLabel(QStringLiteral("年   龄: "), this)),
    m_ageInfo(new QComboBox(this)),
    m_dateEdit(new DateEdit(this))
{
    /* lineEidt */
    m_phoneInfo->setReadOnly(true);
    m_phoneInfo->setCursor(Qt::IBeamCursor);

    /* pushButton */
    QMenu *menu = new QMenu(this);
    QWidgetAction *widgetAction = new QWidgetAction(this);
    widgetAction->setDefaultWidget(m_dateEdit);
    menu->addAction(widgetAction);
    m_birthdayInfo->setMenu(menu);

    /* comboBox */
    m_sexInfo->addItem(QStringLiteral("其他"));
    m_sexInfo->addItem(QStringLiteral("男"));
    m_sexInfo->addItem(QStringLiteral("女"));
    m_sexInfo->setEditable(false);
    m_sexInfo->setView(new QListView(this));
    m_sexInfo->setFixedWidth(60);

    QStringList ageList;
    for(int i = 0; i < 120; ++i) {
        ageList.push_back(QString::number(i));
    }
    m_ageInfo->addItems(ageList);
    m_ageInfo->setMaxVisibleItems(5);
    m_ageInfo->setEditable(false);
    m_ageInfo->setView(new QListView(this));
    m_ageInfo->setFixedWidth(60);

    /* size */
    m_phoneInfo->setFixedHeight(25);
    m_nameInfo->setFixedHeight(25);
    m_qqInfo->setFixedHeight(25);
    m_emailInfo->setFixedHeight(25);
    m_sexInfo->setFixedHeight(25);
    m_birthdayInfo->setFixedHeight(25);
    m_ageInfo->setFixedHeight(25);

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

    /* connect */
    connect(m_nameInfo, &QLineEdit::textChanged, this, &EditWidget::m_infoEdited);
    connect(m_qqInfo, &QLineEdit::textChanged, this, &EditWidget::m_infoEdited);
    connect(m_emailInfo, &QLineEdit::textChanged, this, &EditWidget::m_infoEdited);
    connect(menu, &QMenu::aboutToShow, this, &EditWidget::m_dateEditPopup);
    connect(m_sexInfo, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &EditWidget::m_infoEdited);
    connect(m_ageInfo, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &EditWidget::m_infoEdited);

    connect(m_dateEdit, &DateEdit::dateChanged, this, &EditWidget::m_dateUpdate);
}

void EditWidget::setInfo(QVariantMap info)
{
    m_info = info;
    /* lineEdit */
    m_phoneInfo->setText(m_info.value("phone").toString());
    m_nameInfo->setText(m_info.value("name").toString());
    m_qqInfo->setText(m_info.value("qq").toString());
    m_emailInfo->setText(m_info.value("email").toString());
    m_birthdayInfo->setText(m_info.value("birthday").toString());

    /* comboBox */
    if(m_info.value("sex").toString().isEmpty()) {
        m_sexInfo->setCurrentIndex(0);
    } else if(m_info.value("sex").toString() == QStringLiteral("男")) {
        m_sexInfo->setCurrentIndex(1);
    } else if(m_info.value("sex").toString() == QStringLiteral("女")) {
        m_sexInfo->setCurrentIndex(2);
    }
    m_ageInfo->setCurrentIndex(m_info.value("age").toInt());
}

QVariantMap EditWidget::getInfo() const
{
    QVariantMap infoTemp = m_info;
    infoTemp["phone"] = m_phoneInfo->text();
    infoTemp["name"] = m_nameInfo->text();
    infoTemp["qq"] = m_qqInfo->text();
    infoTemp["email"] = m_emailInfo->text();
    infoTemp["birthday"] = m_birthdayInfo->text();
    infoTemp["sex"] = m_sexInfo->currentText();
    infoTemp["age"] = m_ageInfo->currentText();

    return infoTemp;
}

void EditWidget::save()
{
    m_info["phone"] = m_phoneInfo->text();
    m_info["name"] = m_nameInfo->text();
    m_info["qq"] = m_qqInfo->text();
    m_info["email"] = m_emailInfo->text();
    m_info["birthday"] = m_birthdayInfo->text();
    m_info["sex"] = m_sexInfo->currentText();
    m_info["age"] = m_ageInfo->currentText();
}

void EditWidget::cancel()
{
    m_phoneInfo->setText(m_info.value("phone").toString());
    m_nameInfo->setText(m_info.value("name").toString());
    m_qqInfo->setText(m_info.value("qq").toString());
    m_emailInfo->setText(m_info.value("email").toString());
    m_birthdayInfo->setText(m_info.value("birthday").toString());
    if(m_info.value("sex").toString().isEmpty()) {
        m_sexInfo->setCurrentIndex(0);
    } else if(m_info.value("sex").toString() == QStringLiteral("男")) {
        m_sexInfo->setCurrentIndex(1);
    } else if(m_info.value("sex").toString() == QStringLiteral("女")) {
        m_sexInfo->setCurrentIndex(2);
    }
    m_ageInfo->setCurrentIndex(m_info.value("age").toInt());
}

void EditWidget::m_infoEdited()
{
    emit infoEdited(true);
}

void EditWidget::m_dateUpdate(const QString &date)
{
    m_birthdayInfo->setText(date);
    this->m_infoEdited();
}

void EditWidget::m_dateEditPopup()
{
    m_dateEdit->setDate(QDate::fromString(m_birthdayInfo->text(), "yyyy-MM-dd"));
}
