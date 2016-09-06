#ifndef LOGINREGISTERDIALOG_H
#define LOGINREGISTERDIALOG_H

#include "sources/userclass/customdialog.h"
#include "sources/userclass/customnetwork.h"

class QLineEdit;
class QPushButton;
class QTimer;

class LoginRegisterDialog : public CustomDialog
{
    Q_OBJECT
public:
    explicit LoginRegisterDialog(QWidget *parent = 0);

signals:
    void loginSuccess(const QVariantMap &userInfo);

protected:

private:
    QPushButton *m_titleButton = nullptr;
    QPushButton *m_login = nullptr;
    QPushButton *m_register = nullptr;
    QPushButton *m_loginButton = nullptr;
    QPushButton *m_registerButton = nullptr;
    QPushButton *m_loginAccountIcon = nullptr;
    QPushButton *m_loginPasswordIcon = nullptr;
    QPushButton *m_registerAccountIcon = nullptr;
    QPushButton *m_registerPasswordIcon = nullptr;
    QPushButton *m_registerUserIcon = nullptr;

    QLineEdit *m_loginAccountEdit = nullptr;
    QLineEdit *m_loginPasswordEdit = nullptr;
    QLineEdit *m_registerAccountEdit = nullptr;
    QLineEdit *m_registerPasswordEdit = nullptr;
    QLineEdit *m_registerUserEdit = nullptr;

    QLabel *m_loginStatusLabel = nullptr;
    QLabel *m_registerStatusLabel = nullptr;

    QWidget *m_mainWidget = nullptr;
    QWidget *m_loginWidget = nullptr;
    QWidget *m_registerWidget = nullptr;

    QTimer *m_timer = nullptr;

    CustomNetwork *m_manager = nullptr;

private slots:
    void m_showMain();
    void m_loginShow();
    void m_registerShow();
    void m_loginRequest();
    void m_registerRequest();

    void m_loginTips();
    void m_loginResume();
    void m_registerResume();

    void m_loginReply(CustomNetwork::Status status);
    void m_registerReply(CustomNetwork::Status status);
    void m_userInfoReply(CustomNetwork::Status status);

};

#endif // LOGINREGISTERDIALOG_H
