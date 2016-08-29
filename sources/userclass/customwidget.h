#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>

class TitleIcon;
class QVBoxLayout;
class QToolButton;
class QMenu;

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = 0);

    /* show & hide icon */
    void hideMenuIcon() const;
    void showMenuIcon() const;
    void hideMaxIcon() const;
    void hideMinIcon() const;
    void hideCloseIcon() const;
    void showMaxIcon() const;
    void showMinIcon() const;
    void showCloseIcon() const;

    void addMenuAction(QAction *action);
    void addMenuSeparator();
    void setCentralWidgetLayout(QLayout *layout);
public slots:
    void setRedirection();
    void resetRedirection();


signals:

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void changeEvent(QEvent *event);

public slots:

private:
    TitleIcon *m_menu = nullptr;
    TitleIcon *m_max = nullptr;
    TitleIcon *m_min = nullptr;
    TitleIcon *m_close = nullptr;
    QVBoxLayout *m_layout = nullptr;

    QMenu *m_popMenu = nullptr;
    bool m_isRedirection = false;

private slots:
    void m_setPopUpPos();
    void m_windowChange();
};

#endif // CUSTOMWIDGET_H
