#include "customdialog.h"
#include "sources/customIcon/titleicon.h"

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QPainter>
#include <QtMath>

#include <QDebug>

CustomDialog::CustomDialog(QWidget *parent) : QDialog(parent)
{
    m_windowTitle = new QWidget(this);
    m_min = new TitleIcon(":/titleBar/icon/min", 4, this);
    m_close =  new TitleIcon(":/titleBar/icon/close_1", 4, this);
    m_mainWidget = new QWidget(this);

    /* mainWidget */
    m_mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    m_mainWidget->setStyleSheet("background: red");

    /* layout */
    QWidget *titleBar = new QWidget(this);
    titleBar->setObjectName("titleBar");
    QHBoxLayout *hBox = new QHBoxLayout(titleBar);
    hBox->addWidget(m_windowTitle);
    hBox->addWidget(m_min);
    hBox->addWidget(m_close);
    hBox->setAlignment(m_windowTitle, Qt::AlignTop | Qt::AlignLeft);
    hBox->setAlignment(m_min, Qt::AlignTop | Qt::AlignRight);
    hBox->setAlignment(m_close, Qt::AlignTop);
    hBox->setMargin(0);
    hBox->setSpacing(0);

    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(titleBar);
    m_layout->addWidget(m_mainWidget);
    m_layout->setAlignment(titleBar, Qt::AlignTop);
    m_layout->setContentsMargins(5, 5, 5, 5);
    m_layout->setSpacing(0);

    /* connect */
    connect(m_min, &TitleIcon::buttonClicked, this, &CustomDialog::showMinimized);
    connect(m_close, &TitleIcon::buttonClicked, this, &CustomDialog::close);

    /* window Attribution */
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}

void CustomDialog::hideMinIcon() const
{
    m_min->hide();
}

void CustomDialog::showMinIcon() const
{
    m_min->show();
}

void CustomDialog::hideCloseIcon() const
{
    m_close->hide();
}

void CustomDialog::showCloseIcon() const
{
    m_close->show();
}

void CustomDialog::setShadow(bool enable)
{
    m_shadow = enable;
    this->setAttribute(Qt::WA_TranslucentBackground, enable);
}

void CustomDialog::setWindowTitle(QWidget *widget)
{
    QHBoxLayout *hBox = new QHBoxLayout(m_windowTitle);
    hBox->addWidget(widget);
    hBox->setContentsMargins(15, 6, 0, 0);
}

void CustomDialog::setCentralWidgetLayout(QLayout *layout)
{
    m_mainWidget->setLayout(layout);
}

QWidget *CustomDialog::centralWidget() const
{
    return m_mainWidget;
}

void CustomDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_drag = true;
        m_dragPosition = event->globalPos() - this->pos();
        event->accept();
    }
}

void CustomDialog::paintEvent(QPaintEvent *)
{
    if(m_shadow) {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRoundedRect(5, 5, this->width() - 10, this->height() - 10, 3, 3);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.fillPath(path, QBrush(Qt::white));

        QColor color(0, 0, 0);
        for(int i = 0; i < 5; ++i)
        {
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);
            QRect rect(5 - i, 5 - i, this->width() - (5 - i) * 2, this->height() - (5 - i) * 2);
            path.addRoundedRect(rect, 3, 3);
            color.setAlpha(50 - qSqrt(i) * 25);
            painter.setPen(color);
            painter.drawPath(path);
        }
    } else {
        m_layout->setMargin(0);
    }
}

void CustomDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_drag && (event->buttons() && Qt::LeftButton)) {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}

void CustomDialog::mouseReleaseEvent(QMouseEvent *)
{
    int currentDeskTopY = 0;
    if(this->x() < QApplication::desktop()->screen()->x() || this->x() + this->width() > QApplication::desktop()->screen()->width()) {
        currentDeskTopY = QApplication::desktop()->screen(1)->y();
    }
    if(this->y() <= currentDeskTopY) {
        move(this->x(), currentDeskTopY);
    }
    m_drag = false;
}
