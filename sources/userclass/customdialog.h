#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>

class TitleIcon;
class QLabel;
class QVBoxLayout;
class QToolButton;
class QPropertyAnimation;

class CustomDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CustomDialog(QWidget *parent = 0);

    /* show & hide icon */
    void hideMinIcon() const;
    void showMinIcon() const;
    void hideCloseIcon() const;
    void showCloseIcon() const;

    void setShadow(bool enable);
    void setWindowTitle(QWidget *widget);
    void setCentralWidgetLayout(QLayout *layout);

    QWidget *centralWidget() const;

    void startAnimation() const;

signals:
    void animationFinish();

public slots:

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    bool m_shadow = false;
    bool m_drag = false;
    QPoint m_dragPosition;

    QWidget *m_windowTitle = nullptr;
    TitleIcon *m_min = nullptr;
    TitleIcon *m_close = nullptr;
    QWidget *m_mainWidget = nullptr;
    QVBoxLayout *m_layout = nullptr;
    QPropertyAnimation *m_animation = nullptr;

private slots:
    void m_animationFinish();

};

#endif // CUSTOMDIALOG_H
