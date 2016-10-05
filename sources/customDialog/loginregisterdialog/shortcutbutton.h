#ifndef SHORTCUTBUTTON_H
#define SHORTCUTBUTTON_H

#include <QPushButton>

class ShortcutButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ShortcutButton(QWidget *parent = Q_NULLPTR);
    explicit ShortcutButton(const QString &text, QWidget *parent = Q_NULLPTR);
    ShortcutButton(const QIcon& icon, const QString &text, QWidget *parent = Q_NULLPTR);

protected:
    void keyPressEvent(QKeyEvent *event);
signals:

public slots:
};

#endif // SHORTCUTBUTTON_H
