#include "titleicon.h"

#include <QMouseEvent>
#include <QPainter>

TitleIcon::TitleIcon(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
}

TitleIcon::TitleIcon(const QString &icon, int num, QWidget *parent)
    : QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    m_num = num;
    QPixmap pixmap(icon);
    QList<QPixmap> pixTemp;
    for(int i=0; i != m_num; i++)
    {
        pixTemp.append(pixmap.copy(i*(pixmap.width()/m_num), 0, pixmap.width()/m_num, pixmap.height()));
    }
    m_pixList = pixTemp;
    m_currentPix = m_pixList.at(0);
    this->setFixedSize(m_currentPix.size());
}

void TitleIcon::setIcon(const QString &icon, int num)
{
    m_num = num;
    QPixmap pixmap(icon);
    QList<QPixmap> pixTemp;
    for(int i=0; i != m_num; i++)
    {
        pixTemp.append(pixmap.copy(i*(pixmap.width()/m_num), 0, pixmap.width()/m_num, pixmap.height()));
    }
    m_pixList = pixTemp;
    m_currentPix = m_pixList.at(0);
    this->setFixedSize(m_currentPix.size());
}

void TitleIcon::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), m_currentPix);
}

void TitleIcon::enterEvent(QEvent *)
{
    setButtonStatus(BUTTON_ENTER);
    emit enterSignal();
}

void TitleIcon::leaveEvent(QEvent *)
{
    setButtonStatus(BUTTON_LEAVE);
    emit leaveSignal();
}

void TitleIcon::mousePressEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton) {
        e->ignore();
        return;
    }
    setButtonStatus(BUTTON_PRESSED);
}

void TitleIcon::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton) {
        e->ignore();
        return;
    }

    if(rect().contains(e->pos()))
    {
        if(this->isEnabled())
            emit buttonClicked();
        setButtonStatus(BUTTON_ENTER);
        e->accept();
    }else{
        setButtonStatus(BUTTON_LEAVE);
        e->ignore();
    }
}

void TitleIcon::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::EnabledChange)
    {
        if(!this->isEnabled() && (m_num == 4))
        {
            setButtonStatus(BUTTON_DISABLE);
        }
    }
}

void TitleIcon::setButtonStatus(TitleIcon::BUTTONSTATUS status)
{
    if(this->isEnabled())
    {
        switch (status) {
        case BUTTON_ENTER:
            m_currentPix = m_pixList.at(1);
            break;
        case BUTTON_LEAVE:
            m_currentPix = m_pixList.at(0);
            break;
        case BUTTON_PRESSED:
            m_currentPix = m_pixList.at(2);
            break;
        default:
            break;
        }
    }else
    {
        if(m_num == 4)
            m_currentPix = m_pixList.at(3);
    }
    update();
}
