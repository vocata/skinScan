#include "customwidget.h"
#include "sources/customIcon/titleicon.h"
#include "sources/mainpart/mainwidget.h"
#include "windows.h"
#include "windowsx.h"
#include <QHBoxLayout>
#include <QMenu>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>

#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>


CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent)
{
    m_menu = new TitleIcon(":/titleBar/icon/menu", 4, this);
    m_max = new TitleIcon(":/titleBar/icon/max", 4, this);
    m_min = new TitleIcon(":/titleBar/icon/min", 4, this);
    m_close =  new TitleIcon(":/titleBar/icon/close_0", 4, this);
    m_popMenu = new QMenu(this);
    m_animation = new QPropertyAnimation(this, "windowOpacity", this);

    /* animation */
    m_animation->setStartValue(0);
    m_animation->setEndValue(1);
    m_animation->setEasingCurve(QEasingCurve::InQuad);

    /* layout */
    QHBoxLayout *hBox = new QHBoxLayout();
    hBox->addWidget(m_menu);
    hBox->addWidget(m_min);
    hBox->addWidget(m_max);
    hBox->addWidget(m_close);
    hBox->setAlignment(m_menu, Qt::AlignTop | Qt::AlignRight);
    hBox->setMargin(0);
    hBox->setSpacing(0);

    m_layout = new QVBoxLayout(this);
    m_layout->addLayout(hBox);
    m_layout->setAlignment(hBox, Qt::AlignTop);
    m_layout->setMargin(2);
    m_layout->setSpacing(0);

    /* read stylesheet */
    QFile qssFile(":/qss/skin");
    qssFile.open(QFile::ReadOnly);
    QString styleSheet = qssFile.readAll();
    this->setStyleSheet(styleSheet);

    /* connect */
    connect(m_menu, &TitleIcon::buttonClicked, this, &CustomWidget::m_setPopUpPos);
    connect(m_min, &TitleIcon::buttonClicked, this, &CustomWidget::showMinimized);
    connect(m_max, &TitleIcon::buttonClicked, this, &CustomWidget::m_windowChange);
    connect(m_close, &TitleIcon::buttonClicked, this, &CustomWidget::close);
    /* window Attribution */
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::FramelessWindowHint);
    /* windows api */
    HWND hwnd = (HWND)this->winId();
    DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
    qDebug() << this->windowFlags();
}

void CustomWidget::hideMenuIcon() const
{
    m_menu->hide();
}

void CustomWidget::showMenuIcon() const
{
    m_menu->show();
}

void CustomWidget::hideMaxIcon() const
{
    m_max->hide();
}

void CustomWidget::hideMinIcon() const
{
    m_max->hide();
}

void CustomWidget::hideCloseIcon() const
{
    m_close->hide();
}

void CustomWidget::showMaxIcon() const
{
    m_max->show();
}

void CustomWidget::showMinIcon() const
{
    m_min->show();
}

void CustomWidget::showCloseIcon() const
{
    m_close->show();
}

void CustomWidget::addMenuAction(QAction *action)
{
    m_popMenu->addAction(action);
}

void CustomWidget::addMenuSeparator()
{
    m_popMenu->addSeparator();
}

void CustomWidget::setCentralWidgetLayout(QLayout *layout)
{
    m_layout->addLayout(layout);
}

void CustomWidget::startAnimation() const
{
    m_animation->start();
}

void CustomWidget::setRedirection()
{
    m_isRedirection = true;
    QTimer::singleShot(100, this, &CustomWidget::resetRedirection);
}

void CustomWidget::resetRedirection()
{
    m_isRedirection = false;
}

bool CustomWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);

    MSG* msg = static_cast<MSG*>(message);

    switch(msg->message) {
    case WM_NCHITTEST: {
        int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
        int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
        if(this->childAt(xPos,yPos) == 0)
        {
            if(!m_isRedirection) {
                *result = HTCAPTION;
            } else {
                return false;
            }
        }else{
            return false;
        }
        if(xPos > 0 && xPos < 5)
            *result = HTLEFT;
        if(xPos > (this->width() - 5) && xPos < (this->width() - 0))
            *result = HTRIGHT;
        if(yPos > 0 && yPos < 5)
            *result = HTTOP;
        if(yPos > (this->height() - 5) && yPos < (this->height() - 0))
            *result = HTBOTTOM;
        if(xPos > 0 && xPos < 5 && yPos > 0 && yPos < 5)
            *result = HTTOPLEFT;
        if(xPos > (this->width() - 5) && xPos < (this->width() - 0) && yPos > 0 && yPos < 5)
            *result = HTTOPRIGHT;
        if(xPos > 0 && xPos < 5 && yPos > (this->height() - 5) && yPos < (this->height() - 0))
            *result = HTBOTTOMLEFT;
        if(xPos > (this->width() - 5) && xPos < (this->width() - 0) && yPos > (this->height() - 5) && yPos < (this->height() - 0))
            *result = HTBOTTOMRIGHT;
        return true;
        break;
    }

    case WM_GETMINMAXINFO:
        if (::IsZoomed(msg->hwnd)) {

            RECT frame = { 0, 0, 0, 0 };
            ::AdjustWindowRectEx(&frame, WS_OVERLAPPEDWINDOW, FALSE, 0);
            frame.left = abs(frame.left);
            frame.top = abs(frame.bottom);
            this->setContentsMargins(frame.left, frame.top, frame.right, frame.bottom);
        }
        else {
            this->setContentsMargins(0, 0, 0, 0);
        }

        *result = ::DefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
        break;

    case WM_NCCALCSIZE:
        return true;
        break;

    default:
        break;
    }
    return false;
}

void CustomWidget::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::WindowStateChange) {
        if(this->windowState() == Qt::WindowMaximized) {
            m_max->setIcon(":/titleBar/icon/restore", 4);

        } else {
            m_max->setIcon(":/titleBar/icon/max", 4);
        }
    }
    this->update();
}

void CustomWidget::m_setPopUpPos()
{
    if(!m_popMenu->isEmpty()) {
        QPoint popUpPos = this->mapToGlobal(QPoint(m_menu->x(), m_menu->y() + m_menu->height()));
        m_popMenu->popup(popUpPos);
    }
}

void CustomWidget::m_windowChange()
{
    if(this->isMaximized()) {
        this->showNormal();
    } else {
        this->showMaximized();
    }
}
