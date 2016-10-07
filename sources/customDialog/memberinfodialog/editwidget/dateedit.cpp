#include "dateedit.h"

#include <QComboBox>
#include <QDateTime>
#include <QHBoxLayout>
#include <QListView>

#include <QDebug>

DateEdit::DateEdit(QWidget *parent) : QWidget(parent)
{
    m_yearEdit = new QComboBox(this);
    m_monthEdit = new QComboBox(this);
    m_dayEdit = new QComboBox(this);

    /* comboBox */
    m_yearEdit->setView(new QListView(this));
    m_yearEdit->setMaxVisibleItems(5);
    m_monthEdit->setView(new QListView(this));
    m_monthEdit->setMaxVisibleItems(5);
    m_dayEdit->setView(new QListView(this));
    m_dayEdit->setMaxVisibleItems(5);

    /* size */
    m_yearEdit->setFixedWidth(60);
    m_monthEdit->setFixedWidth(40);
    m_dayEdit->setFixedWidth(40);

    /* set date */
    int year = QDate::currentDate().year();
    int month = QDate::currentDate().month();
    int day = QDate::currentDate().day();

    /* year */
    int yearCount = 120;
    int firstYear = year - yearCount;
    QStringList yearList;
    for(int i = 1; i <= yearCount; ++i) {
        yearList.push_back(QString::number(firstYear + i));
    }
    m_yearEdit->addItems(yearList);
    m_yearEdit->setCurrentIndex(yearCount - 1);

    /* month */
    int monthCount = 12;
    QStringList monthList;
    for(int i = 1; i <= monthCount; ++i) {
        if(i < 10) {
            monthList.push_back("0" + QString::number(i));
        } else {
            monthList.push_back(QString::number(i));
        }
    }
    m_monthEdit->addItems(monthList);
    m_monthEdit->setCurrentIndex(month - 1);

    /* day */
    int dayCount = QDate(year, month, day).daysInMonth();
    QStringList dayList;
    for(int i = 1; i <= dayCount; ++i) {
        if(i < 10) {
            dayList.push_back("0" + QString::number(i));
        } else {
            dayList.push_back(QString::number(i));
        }
    }
    m_dayEdit->addItems(dayList);
    m_dayEdit->setCurrentIndex(day - 1);

    /* layout */
    QHBoxLayout *hBox = new QHBoxLayout(this);
    hBox->addWidget(m_yearEdit);
    hBox->addWidget(m_monthEdit);
    hBox->addWidget(m_dayEdit);

    /* connect */
    connect(m_yearEdit, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &DateEdit::m_updateDay);
    connect(m_monthEdit, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &DateEdit::m_updateDay);

    connect(m_yearEdit, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &DateEdit::m_currentDay);
    connect(m_monthEdit, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &DateEdit::m_currentDay);
    connect(m_dayEdit, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &DateEdit::m_currentDay);

    /* windows attribution */
    this->setAttribute(Qt::WA_StyledBackground);
}

void DateEdit::setDate(const QDate &date)
{
    m_yearEdit->setCurrentText(QString::number(date.year()));
    m_monthEdit->setCurrentText(QString::number(date.month()));
}

void DateEdit::m_updateDay()
{
    QDate date(m_yearEdit->currentText().toInt(), m_monthEdit->currentText().toInt(), 1);   //记录当前显示的时间
    if(date.daysInMonth() != m_dayEdit->count()) {          //判断当前月份的天数与comboBox的天数是否相同
        int currentDay = m_dayEdit->currentText().toInt();      //当前显示的天数，后续用作判断

        /* 更新日期 */
        QStringList dateList;
        for(int i = 1; i <= date.daysInMonth(); ++i) {
            if(i < 10) {
                dateList.push_back("0" + QString::number(i));
            } else {
                dateList.push_back(QString::number(i));
            }
        }
        m_dayEdit->clear();
        m_dayEdit->addItems(dateList);

        if(currentDay <= date.daysInMonth()) {
            m_dayEdit->setCurrentIndex(currentDay - 1);     //小于之前的天数则设置回之前的天数
        } else {
            m_dayEdit->setCurrentIndex(0);                  //否则设置当前天数为1
        }
    }
}

void DateEdit::m_currentDay()
{
    QString date = m_yearEdit->currentText() + '-' +
            m_monthEdit->currentText() + '-' +
            m_dayEdit->currentText();
    emit dateChanged(date);
}
