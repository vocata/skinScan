#include "shortcutbutton.h"

#include <QKeyEvent>

ShortcutButton::ShortcutButton(QWidget *parent) : QPushButton(parent)
{
}

ShortcutButton::ShortcutButton(const QString &text, QWidget *parent) : QPushButton(text, parent)
{

}

ShortcutButton::ShortcutButton(const QIcon &icon, const QString &text, QWidget *parent) : QPushButton(icon, text, parent)
{

}

void ShortcutButton::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        this->click();
        event->accept();
    } else {
        this->QPushButton::keyPressEvent(event);
    }
}
