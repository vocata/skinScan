#include "statusicon.h"

#include <QPainter>

StatusIcon::StatusIcon(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
}

StatusIcon::StatusIcon(const QString &icon1, const QString &icon2, QWidget *parent)
    :QWidget(parent)
{
    m_pixPair.first = QPixmap(icon1);
    m_pixPair.second = QPixmap(icon2);
    m_currentPix = m_pixPair.first;

    this->setFixedSize(m_currentPix.size());
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void StatusIcon::setIcon(const QString &icon1, const QString &icon2)
{
    m_pixPair.first = QPixmap(icon1);
    m_pixPair.second = QPixmap(icon2);
    m_currentPix = m_pixPair.first;

    this->setFixedSize(m_currentPix.size());
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void StatusIcon::setIconStatus(bool enable)
{
    if(!enable) {
        m_currentPix = m_pixPair.first;
    } else {
        m_currentPix = m_pixPair.second;
    }
    this->update();
}

void StatusIcon::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), m_currentPix);
}
