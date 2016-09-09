#include "loginregisterdialog.h"
#include "messagedialog.h"
#include "sources/userclass/customnetwork.h"

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegexp>
#include <QVBoxLayout>
#include <QTimer>

#include <QCloseEvent>

LoginRegisterDialog::LoginRegisterDialog(QWidget *parent) : CustomDialog(parent)
{
    m_titleButton = new QPushButton(this);
    m_login = new QPushButton(QStringLiteral("手机号登陆"), this);
    m_register = new QPushButton(QStringLiteral("注册"), this);
    m_loginButton = new QPushButton(QStringLiteral("立即登陆"), this);
    m_registerButton = new QPushButton(QStringLiteral("注册"), this);
    m_loginAccountIcon = new QPushButton(QIcon(":/log&reg/icon/phone"), QString(), this);
    m_loginPasswordIcon = new QPushButton(QIcon(":/log&reg/icon/lock"), QString(), this);;
    m_registerAccountIcon = new QPushButton(QIcon(":/log&reg/icon/phone"), QString(), this);;
    m_registerPasswordIcon = new QPushButton(QIcon(":/log&reg/icon/lock"), QString(), this);;
    m_registerUserIcon = new QPushButton(QIcon(":/log&reg/icon/user"), QString(), this);
    m_loginAccountEdit = new QLineEdit(this);
    m_loginPasswordEdit = new QLineEdit(this);
    m_registerAccountEdit = new QLineEdit(this);
    m_registerPasswordEdit = new QLineEdit(this);
    m_registerUserEdit = new QLineEdit(this);
    m_loginStatusLabel = new QLabel(this);
    m_registerStatusLabel = new QLabel(this);
    m_timer = new QTimer(this);
    m_manager = new CustomNetwork(this);

    /* title */
    m_titleButton->setObjectName("titleButton");

    /* main widget */
    m_login->setFixedSize(250, 40);
    m_login->setObjectName("loginRegister");
    m_register->setFixedSize(250, 40);
    m_register->setObjectName("loginRegister");
    /* layout */
    m_mainWidget = new QWidget(this);
    QVBoxLayout *mainBox = new QVBoxLayout(m_mainWidget);
    mainBox->addWidget(m_login);
    mainBox->addWidget(m_register);
    mainBox->setMargin(0);
    mainBox->setSpacing(10);

    /* login widget */
    m_loginButton->setFixedSize(250, 40);
    m_loginButton->setObjectName("button");
    m_loginButton->setShortcut(Qt::Key_Return);

    m_loginAccountIcon->setFixedSize(40, 40);
    m_loginAccountIcon->setFocusPolicy(Qt::NoFocus);
    m_loginAccountIcon->setObjectName("lAccountIcon");
    m_loginPasswordIcon->setFixedSize(40, 40);
    m_loginPasswordIcon->setFocusPolicy(Qt::NoFocus);
    m_loginPasswordIcon->setObjectName("lPasswordIcon");

    m_loginAccountEdit->setPlaceholderText(QStringLiteral("请输入手机号"));
    m_loginAccountEdit->setAttribute(Qt::WA_InputMethodEnabled, false);
    m_loginAccountEdit->setMaxLength(11);
    m_loginAccountEdit->setFixedSize(250, 40);
    m_loginAccountEdit->setObjectName("lAccountEdit");
    m_loginPasswordEdit->setPlaceholderText(QStringLiteral("请输入密码"));
    m_loginPasswordEdit->setAttribute(Qt::WA_InputMethodEnabled, false);
    m_loginPasswordEdit->setMaxLength(20);
    m_loginPasswordEdit->setEchoMode(QLineEdit::Password);
    m_loginPasswordEdit->setFixedSize(250, 40);
    m_loginPasswordEdit->setObjectName("lPasswordEdit");

    /* layout */
    QHBoxLayout *loginAccountBox = new QHBoxLayout();
    loginAccountBox->addWidget(m_loginAccountIcon);
    loginAccountBox->addWidget(m_loginAccountEdit);
    loginAccountBox->setMargin(0);
    loginAccountBox->setSpacing(0);
    QHBoxLayout *loginPasswordBox = new QHBoxLayout();
    loginPasswordBox->addWidget(m_loginPasswordIcon);
    loginPasswordBox->addWidget(m_loginPasswordEdit);
    loginPasswordBox->setMargin(0);
    loginPasswordBox->setSpacing(0);
    QVBoxLayout *loginEditBox = new QVBoxLayout();
    loginEditBox->addLayout(loginAccountBox);
    loginEditBox->addLayout(loginPasswordBox);
    loginEditBox->setMargin(0);
    loginEditBox->setSpacing(0);

    m_loginWidget = new QWidget(this);
    QVBoxLayout *loginBox = new QVBoxLayout(m_loginWidget);
    loginBox->addLayout(loginEditBox);
    loginBox->addWidget(m_loginStatusLabel);
    loginBox->addWidget(m_loginButton);
    loginBox->setAlignment(loginEditBox, Qt::AlignCenter);
    loginBox->setAlignment(m_loginButton, Qt::AlignCenter);
    loginBox->setSpacing(10);

    /* register widget */
    m_registerButton->setFixedSize(250, 40);
    m_registerButton->setObjectName("button");
    m_registerButton->setShortcut(Qt::Key_Return);

    m_registerAccountIcon->setFixedSize(40, 40);
    m_registerAccountIcon->setFocusPolicy(Qt::NoFocus);
    m_registerAccountIcon->setObjectName("rAccountIcon");
    m_registerPasswordIcon->setFixedSize(40, 40);
    m_registerPasswordIcon->setFocusPolicy(Qt::NoFocus);
    m_registerPasswordIcon->setObjectName("rPasswordIcon");
    m_registerUserIcon->setFixedSize(40, 40);
    m_registerUserIcon->setFocusPolicy(Qt::NoFocus);
    m_registerUserIcon->setObjectName("rUserIcon");

    m_registerAccountEdit->setPlaceholderText(QStringLiteral("请输入手机号"));
    m_registerAccountEdit->setAttribute(Qt::WA_InputMethodEnabled, false);
    m_registerAccountEdit->setMaxLength(11);
    m_registerAccountEdit->setFixedSize(250, 40);
    m_registerAccountEdit->setObjectName("rAccountEdit");
    m_registerPasswordEdit->setPlaceholderText(QStringLiteral("设置登陆密码, 不少于6位"));
    m_registerPasswordEdit->setAttribute(Qt::WA_InputMethodEnabled, false);
    m_registerPasswordEdit->setMaxLength(20);
    m_registerPasswordEdit->setEchoMode(QLineEdit::Password);
    m_registerPasswordEdit->setFixedSize(250, 40);
    m_registerPasswordEdit->setObjectName("rPasswordEdit");
    m_registerUserEdit->setPlaceholderText(QStringLiteral("请输入用户名"));
    m_registerUserEdit->setMaxLength(10);
    m_registerUserEdit->setFixedSize(250, 40);
    m_registerUserEdit->setObjectName("rUserEdit");

    /* layout */
    QHBoxLayout *registerAccountBox = new QHBoxLayout();
    registerAccountBox->addWidget(m_registerAccountIcon);
    registerAccountBox->addWidget(m_registerAccountEdit);
    registerAccountBox->setMargin(0);
    registerAccountBox->setSpacing(0);
    QHBoxLayout *registerPasswordBox = new QHBoxLayout();
    registerPasswordBox->addWidget(m_registerPasswordIcon);
    registerPasswordBox->addWidget(m_registerPasswordEdit);
    registerPasswordBox->setMargin(0);
    registerPasswordBox->setSpacing(0);
    QHBoxLayout *registerUserBox = new QHBoxLayout();
    registerUserBox->addWidget(m_registerUserIcon);
    registerUserBox->addWidget(m_registerUserEdit);
    registerUserBox->setMargin(0);
    registerUserBox->setSpacing(0);
    QVBoxLayout *registerEditBox = new QVBoxLayout();
    registerEditBox->addLayout(registerAccountBox);
    registerEditBox->addLayout(registerPasswordBox);
    registerEditBox->addLayout(registerUserBox);
    registerEditBox->setMargin(0);
    registerEditBox->setSpacing(0);

    m_registerWidget = new QWidget(this);
    QVBoxLayout *registerBox = new QVBoxLayout(m_registerWidget);
    registerBox->addLayout(registerEditBox);
    registerBox->addWidget(m_registerStatusLabel);
    registerBox->addWidget(m_registerButton);
    registerBox->setAlignment(registerEditBox, Qt::AlignCenter);
    registerBox->setAlignment(m_registerButton, Qt::AlignCenter);
    registerBox->setSpacing(10);

    /* all Layout */
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_mainWidget);
    layout->addWidget(m_loginWidget);
    layout->addWidget(m_registerWidget);
    layout->setAlignment(m_mainWidget, Qt::AlignCenter);
    layout->setAlignment(m_loginWidget, Qt::AlignCenter);
    layout->setAlignment(m_registerWidget, Qt::AlignCenter);

    /* connect */
    connect(m_titleButton, &QPushButton::clicked, this, &LoginRegisterDialog::m_showMain);
    connect(m_login, &QPushButton::clicked, this, &LoginRegisterDialog::m_loginShow);
    connect(m_register, &QPushButton::clicked, this, &LoginRegisterDialog::m_registerShow);
    /* login & register */
    connect(m_loginButton, &QPushButton::clicked, this, &LoginRegisterDialog::m_loginRequest);
    connect(m_registerButton, &QPushButton::clicked, this, &LoginRegisterDialog::m_registerRequest);
    /* timer */
    connect(m_timer, &QTimer::timeout, this, &LoginRegisterDialog::m_loginTips);
    /* network */
    connect(m_manager, &CustomNetwork::memberLoginStatus, this, &LoginRegisterDialog::m_loginReply);
    connect(m_manager, &CustomNetwork::memberRegisterStatus, this, &LoginRegisterDialog::m_registerReply);
    connect(m_manager, &CustomNetwork::getUserInfoStatus, this, &LoginRegisterDialog::m_userInfoReply);

    /* window Attribution */
    this->m_showMain();
    this->setShadow(true);
    this->setCentralWidgetLayout(layout);
    this->hideMinIcon();
    this->resize(340, 400);
    this->setWindowTitle(m_titleButton);
    this->startAnimation();
    this->centralWidget()->setObjectName("centralDialog");
}

void LoginRegisterDialog::m_showMain()
{
    m_titleButton->setText(QString());
    m_titleButton->hide();
    m_mainWidget->show();
    m_loginWidget->hide();
    m_registerWidget->hide();
}

void LoginRegisterDialog::m_loginShow()
{
    m_titleButton->setText(QStringLiteral("< 返回注册"));
    m_titleButton->show();
    m_mainWidget->hide();
    m_loginWidget->show();
}

void LoginRegisterDialog::m_registerShow()
{
    m_titleButton->setText(QStringLiteral("< 返回登陆"));
    m_titleButton->show();
    m_mainWidget->hide();
    m_registerWidget->show();
}

void LoginRegisterDialog::m_loginRequest()
{
    if(!QRegExp("1[\\d]{10}").exactMatch(m_loginAccountEdit->text())) {
        m_loginStatusLabel->setText(QStringLiteral("<font color=red>请输入11位手机号码!</font>"));
    } else if(m_loginPasswordEdit->text().length() < 6) {
        m_loginStatusLabel->setText(QStringLiteral("<font color=red>请输入6-20位的密码!</font>"));
    } else{
        m_loginStatusLabel->clear();
        m_loginButton->setEnabled(false);
        m_timer->start(500);
        m_loginButton->setText(QStringLiteral("正在登陆"));
        m_manager->memberLogin(m_loginAccountEdit->text(), m_loginPasswordEdit->text());
    }
}

void LoginRegisterDialog::m_registerRequest()
{
    if(!QRegExp("1[\\d]{10}").exactMatch(m_registerAccountEdit->text())) {
        m_registerStatusLabel->setText(QStringLiteral("<font color=red>请输入11位手机号码!</font>"));
    } else if(m_registerPasswordEdit->text().length() < 6) {
        m_registerStatusLabel->setText(QStringLiteral("<font color=red>请输入6-20位的密码!</font>"));
    } else {
        m_registerStatusLabel->clear();
        m_registerButton->setEnabled(false);
        m_manager->memberRegister(m_registerAccountEdit->text(), m_registerPasswordEdit->text(), m_registerUserEdit->text());
    }
}

void LoginRegisterDialog::m_loginTips()
{
    static int times = 0;
    if(times == 0) {
        m_loginButton->setText(QStringLiteral("正在登陆"));
    } else if(times == 1) {
        m_loginButton->setText(QStringLiteral("正在登陆 ."));
    } else if(times == 2) {
        m_loginButton->setText(QStringLiteral("正在登陆 . ."));
    } else {
        m_loginButton->setText(QStringLiteral("正在登陆 . . ."));
        times = -1;
    }
    ++times;
}

void LoginRegisterDialog::m_loginResume()
{
    /* resume */
    m_timer->stop();
    m_loginButton->setEnabled(true);
    m_loginButton->setText(QStringLiteral("立即登陆"));
}

void LoginRegisterDialog::m_registerResume()
{
    m_registerButton->setEnabled(true);
}

void LoginRegisterDialog::m_loginReply(CustomNetwork::Status status)
{
    switch(status) {
    case CustomNetwork::Success:
        m_manager->getUserInfo();
        break;
    case CustomNetwork::Failure:
        m_loginStatusLabel->setText(QStringLiteral("<font color=red>账号或密码错误!</font>"));
        this->m_loginResume();
        break;
    case CustomNetwork::Timeout:
        m_loginStatusLabel->setText(QStringLiteral("<font color=red>网络连接出错!</font>"));
        this->m_loginResume();
        break;
    default:
        break;
    }
}

void LoginRegisterDialog::m_registerReply(CustomNetwork::Status status)
{
    switch(status) {
    case CustomNetwork::Success: {
        MessageDialog dialog(this);
        dialog.execInformation(QStringLiteral("恭喜你, 注册成功!"), QStringLiteral("注册"));
        m_registerAccountEdit->clear();
        m_registerPasswordEdit->clear();
        m_registerUserEdit->clear();
        this->m_showMain();
        break;
    }
    case CustomNetwork::Failure:
        m_registerStatusLabel->setText(QStringLiteral("<font color=red>该手机号码已注册!</font>"));
        break;
    case CustomNetwork::Timeout:
        m_registerStatusLabel->setText(QStringLiteral("<font color=red>网络连接出错!</font>"));
        break;
    default:
        break;
    }
    this->m_registerResume();
}

void LoginRegisterDialog::m_userInfoReply(CustomNetwork::Status status)
{
    switch(status) {
    case CustomNetwork::Success:
        emit loginSuccess(m_manager->userInfo());
        this->close();
        break;
    case CustomNetwork::Failure:
        m_loginStatusLabel->setText(QStringLiteral("<font color=red>服务器错误!</font>"));
        break;
    case CustomNetwork::Timeout:
        m_loginStatusLabel->setText(QStringLiteral("<font color=red>网络连接出错!</font>"));
        break;
    default:
        break;
    }
    this->m_loginResume();
}

