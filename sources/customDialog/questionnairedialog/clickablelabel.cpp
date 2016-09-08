#include "clickablelabel.h"

#include <QMouseEvent>

ClickableLabel::ClickableLabel(QWidget *parent) : QLabel(parent)
{

}

void ClickableLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton) {
        emit clicked(true);
        return;
    }
    QLabel::mousePressEvent(ev);
}
