#include "passworddialog.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>
#include <QTimer>
#include <QToolButton>

#include <QDebug>

PasswordDialog::PasswordDialog(QWidget *parent) : CustomDialog(parent)
{
    m_icon = new QPushButton(this);
    m_confirmButton = new QToolButton(this);
    m_cancelButton = new QToolButton(this);
    m_accountLabel = new QLabel(QStringLiteral("账号"), this);
    m_account = new QLineEdit(this);
    m_passwordLabel = new QLabel(QStringLiteral("旧密码"), this);
    m_password = new QLineEdit(this);
    m_newPasswordLabel = new QLabel(QStringLiteral("新密码"), this);
    m_newPassword = new QLineEdit(this);
    m_tip = new QLabel(this);
    m_manager = new CustomNetwork(this);

    /* titleLabel */
    QLabel *titleLabel = new QLabel(QStringLiteral("修改密码"), this);

    /* pushButton */
    m_icon->setIconSize(QSize(60, 60));
    m_icon->setFixedSize(QSize(64, 64));

    /* toolButton */
    m_confirmButton->setText(QStringLiteral("确认"));
    m_confirmButton->setFixedSize(40, 25);

    m_cancelButton->setText(QStringLiteral("取消"));
    m_cancelButton->setFixedSize(40, 25);

    /* lineEdit */
    m_account->setReadOnly(true);
    m_account->setCursor(Qt::IBeamCursor);
    m_account->setFixedHeight(25);

    m_password->setPlaceholderText(QStringLiteral("请输入旧密码"));
    m_password->setAttribute(Qt::WA_InputMethodEnabled, false);
    m_password->setMaxLength(20);
    m_password->setEchoMode(QLineEdit::Password);
    m_password->setFixedHeight(25);

    m_newPassword->setPlaceholderText(QStringLiteral("请输入新密码, 不少于6位"));
    m_newPassword->setAttribute(Qt::WA_InputMethodEnabled, false);
    m_newPassword->setMaxLength(20);
    m_newPassword->setEchoMode(QLineEdit::Password);
    m_newPassword->setFixedHeight(25);

    /* layout */
    QHBoxLayout *buttonBox = new QHBoxLayout();
    buttonBox->addWidget(m_icon, 0, Qt::AlignLeft | Qt::AlignBottom);
    buttonBox->addWidget(m_confirmButton, 0, Qt::AlignRight | Qt::AlignBottom);
    buttonBox->addWidget(m_cancelButton, 0, Qt::AlignBottom);

    QGroupBox *editGroup = new QGroupBox(this);
    QGridLayout *gBox = new QGridLayout(editGroup);
    gBox->addWidget(m_accountLabel, 0, 0, 1, 1);
    gBox->addWidget(m_account, 0, 1, 1, 1);
    gBox->addWidget(m_passwordLabel, 1, 0, 1, 1);
    gBox->addWidget(m_password, 1, 1, 1, 1);
    gBox->addWidget(m_newPasswordLabel, 2, 0, 1, 1);
    gBox->addWidget(m_newPassword, 2, 1, 1, 1);
    gBox->addWidget(m_tip, 3, 1, 1, 2);
    gBox->setHorizontalSpacing(20);
    gBox->setVerticalSpacing(10);

    QVBoxLayout *vBox = new QVBoxLayout();
    vBox->addLayout(buttonBox);
    vBox->addWidget(editGroup);

    this->m_setInfo();

    /* connect */
    connect(m_confirmButton, &QToolButton::clicked, this, &PasswordDialog::m_setNewPassword);
    connect(m_cancelButton, &QToolButton::clicked, this, &PasswordDialog::close);
//    connect(m_manager, &CustomNetwork::updateUserInfoStatus, this, &PasswordDialog::m_updateUserInfoReply);

    /* windows attribution */
    this->setWindowTitle(titleLabel);
    this->setCentralWidgetLayout(vBox);
    this->setShadow(true);
    this->hideMinIcon();
    this->setFixedSize(340, 280);
    this->startAnimation();
    this->centralWidget()->setObjectName("centralDialog");
}

void PasswordDialog::m_setInfo()
{
    /* icon */
    QSettings settings("conf.ini", QSettings::IniFormat);
    settings.beginGroup("normal");

    QString sex = settings.value("sex").toString();
    if(sex == QStringLiteral("男")) {
        m_icon->setIcon(QIcon(":/button/icon/boy"));
    } else if(sex == QStringLiteral("女")){
        m_icon->setIcon(QIcon(":/button/icon/girl"));
    } else {
        m_icon->setIcon(QIcon(":/button/icon/anonymous"));
    }

    settings.endGroup();

    /* lineEdit */
    m_account->setText(m_manager->account());
}

void PasswordDialog::m_setNewPassword()
{
    if(m_password->text().isEmpty()) {
        m_tip->setText(QStringLiteral("<font color=red>请输入旧密码<font>"));
        QTimer::singleShot(2000, m_tip, &QLabel::clear);
        return;
    }
    if(m_newPassword->text().isEmpty()) {
        m_tip->setText(QStringLiteral("<font color=red>请输入新密码<font>"));
        QTimer::singleShot(2000, m_tip, &QLabel::clear);
        return;
    }
    if(m_password->text() != m_manager->password()) {
        m_tip->setText(QStringLiteral("<font color=red>旧密码不正确<font>"));
        QTimer::singleShot(2000, m_tip, &QLabel::clear);
        return;
    }
    /* 更新操作 */

}

void PasswordDialog::m_updateUserInfoReply(CustomNetwork::Status status)
{
    switch(status) {
    case CustomNetwork::Success:
        emit passwordChanged();
        qDebug() << "in";
        break;
    case CustomNetwork::Failure: break;
    case CustomNetwork::Timeout: break;
    default: break;
    }
}
