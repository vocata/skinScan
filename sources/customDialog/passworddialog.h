#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QWidget>

#include "sources/userclass/customdialog.h"
#include "sources/userclass/customnetwork.h"

class QLabel;
class QLineEdit;
class QToolButton;
class QPushButton;

class PasswordDialog : public CustomDialog
{
    Q_OBJECT
public:
    explicit PasswordDialog(QWidget *parent = 0);

signals:
    void passwordChanged();

public slots:

private:
    QPushButton *m_icon;
    QToolButton *m_confirmButton;
    QToolButton *m_cancelButton;
    QLabel *m_accountLabel;
    QLineEdit *m_account;
    QLabel *m_passwordLabel;
    QLineEdit *m_password;
    QLabel *m_newPasswordLabel;
    QLineEdit *m_newPassword;
    QLineEdit *m_newPasswordAgain;
    QLabel *m_tip;
    CustomNetwork *m_manager;

private slots:
    void m_setInfo();
    void m_setNewPassword();

    void m_modifyPasswordReply(CustomNetwork::Status status);
};

#endif // PASSWORDDIALOG_H
