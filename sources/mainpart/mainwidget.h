#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include "sources/userclass/customwidget.h"

class QPushButton;
class QLineEdit;
class QToolButton;
class StatisticsWidget;
class MainStatusBar;
class CustomNetwork;
class CustomStackedWidget;
class LoginRegisterDialog;

class MeasureWidget;

class MainWidget : public CustomWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

signals:

public slots:

private:
    QPushButton *m_userImage = nullptr;
    QPushButton *m_accountButton = nullptr;
    QPushButton *m_userButton = nullptr;
    QToolButton *m_measureButton = nullptr;
    QToolButton *m_statisticsButton = nullptr;
    QToolButton *m_historyButton = nullptr;
    QToolButton *m_helpButton = nullptr;
    QToolButton *m_aboutButton = nullptr;
    QMenu *m_infoMenu = nullptr;

    MeasureWidget *m_measureWidget = nullptr;
    StatisticsWidget *m_statisticsWidget = nullptr;
    CustomStackedWidget *m_stackedWidget = nullptr;

    MainStatusBar *m_statusBar = nullptr;
    LoginRegisterDialog *m_loginRegisterDialog = nullptr;

    CustomNetwork *m_manager = nullptr;

private slots:
    void m_stackedMeasureWidget();
    void m_stackedStatisticsWidget();
    void m_stackedHistoryWidget();

    /* action */
    void m_memberInfo();
    void m_modifyPassword();
    void m_loginRegister();
    void m_logout();

    /* login */
    void m_setAccountAndUser(const QVariantMap &userInfo);

};

#endif // MAINWIDGET_H
