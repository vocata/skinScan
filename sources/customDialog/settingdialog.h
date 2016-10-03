#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include "sources/userclass/customdialog.h"

#include <QWidget>

class QToolButton;
class QStackedWidget;
class RegularWidget;
class NetworkWidget;

class SettingDialog : public CustomDialog
{
    Q_OBJECT
public:
    explicit SettingDialog(QWidget *parent = 0);

signals:

public slots:

private:
    QToolButton *m_regularButton = nullptr;
    QToolButton *m_networkButton = nullptr;
    QStackedWidget *m_stackedWidget = nullptr;
    RegularWidget *m_regularWidget = nullptr;
    NetworkWidget *m_networkWidget = nullptr;
    QToolButton *m_confirmButton = nullptr;
    QToolButton *m_cancelButton = nullptr;

private slots:
    void m_confirm();
    void m_cancel();
};

#endif // SETTINGDIALOG_H
