#include "mainwidget.h"
#include "mainstatusbar.h"
#include "measurewidget.h"
#include "statisticswidget.h"
#include "sources/customDialog/loginregisterdialog.h"
#include "sources/customDialog/settingdialog.h"
#include "sources/userclass/customstackedwidget.h"
#include "sources/userclass/customnetwork.h"

#include <QMenu>
#include <QPushButton>
#include <QStatusBar>
#include <QTabWidget>
#include <QTabBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QApplication>
#include <QDesktopWidget>
#include <QSettings>
#include <QDesktopServices>
#include <QUrl>




MainWidget::MainWidget(QWidget *parent) : CustomWidget(parent)
{
    m_userImage = new QPushButton(this);
    m_accountButton = new QPushButton(QStringLiteral("点击登陆"), this);
    m_userButton = new QPushButton(QStringLiteral("未登录"), this);
    m_measureButton = new QToolButton(this);
    m_statisticsButton = new QToolButton(this);
    m_historyButton = new QToolButton(this);
    m_helpButton = new QToolButton(this);
    m_aboutButton = new QToolButton(this);
    m_measureWidget = new MeasureWidget(this);
    m_statisticsWidget = new StatisticsWidget(this);
    m_stackedWidget = new CustomStackedWidget(this);
    m_statusBar = new MainStatusBar(this);
    m_manager = new CustomNetwork(this);
    m_settings = new QSettings("conf.ini", QSettings::IniFormat, this);

    /* QPushButton */
    m_infoMenu = new QMenu(this);
    m_infoMenu->setFixedWidth(150);
    m_infoMenu->setObjectName("infoMenu");
    QAction *info = new QAction(QIcon(":/menu/icon/info"), QStringLiteral("基本信息"), this);
    QAction *modifyPassword = new QAction(QStringLiteral("修改密码"), this);
    QAction *replaceAccount = new QAction(QIcon(":/menu/icon/exchange"), QStringLiteral("更换账号"), this);
    QAction *setting = new QAction(QIcon(":/menu/icon/setting"), QStringLiteral("设置"), this);
    QAction *logout = new QAction(QIcon(":/menu/icon/loginout"), QStringLiteral("注销"), this);
    m_infoMenu->addAction(info);
    m_infoMenu->addSeparator();
    m_infoMenu->addAction(modifyPassword);
    m_infoMenu->addAction(replaceAccount);
    m_infoMenu->addSeparator();
    m_infoMenu->addAction(setting);
    m_infoMenu->addSeparator();
    m_infoMenu->addAction(logout);

    m_userImage->setIcon(QIcon(":/button/icon/anonymous"));
    m_userImage->setIconSize(QSize(60, 60));
    m_userImage->setFixedSize(QSize(64, 64));
    m_userImage->setObjectName("userImage");

    m_accountButton->setFixedSize(150, 20);
    m_accountButton->setObjectName("accountButton");

    m_userButton->setFocusPolicy(Qt::NoFocus);
    m_userButton->setObjectName("userButton");

    /* QToolButton */
    m_measureButton->setIcon(QIcon(":/button/icon/measure"));
    m_measureButton->setText(QStringLiteral("皮肤检测"));
    m_measureButton->setIconSize(QSize(48, 48));
    m_measureButton->setFixedSize(QSize(82, 82));
    m_measureButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_measureButton->setCheckable(true);
    m_measureButton->setChecked(true);
    m_measureButton->setObjectName("measureButton");

    m_statisticsButton->setIcon(QIcon(":/button/icon/chart"));
    m_statisticsButton->setText(QStringLiteral("数据统计"));
    m_statisticsButton->setIconSize(QSize(48, 48));
    m_statisticsButton->setFixedSize(QSize(82, 82));
    m_statisticsButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_statisticsButton->setCheckable(true);
    m_statisticsButton->setObjectName("statisticsButton");

    m_historyButton->setIcon(QIcon(":/button/icon/history"));
    m_historyButton->setText(QStringLiteral("检测纪录"));
    m_historyButton->setIconSize(QSize(48, 48));
    m_historyButton->setFixedSize(QSize(82, 82));
    m_historyButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_historyButton->setCheckable(true);
    m_historyButton->setObjectName("historyButton");

    m_helpButton->setIcon(QIcon(":/button/icon/help"));
    m_helpButton->setText(QStringLiteral("使用说明"));
    m_helpButton->setIconSize(QSize(48, 48));
    m_helpButton->setFixedSize(QSize(82, 82));
    m_helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_helpButton->setCheckable(true);
    m_helpButton->setObjectName("helpButton");

    m_aboutButton->setIcon(QIcon(":/button/icon/about"));
    m_aboutButton->setText(QStringLiteral("关于"));
    m_aboutButton->setIconSize(QSize(48, 48));
    m_aboutButton->setFixedSize(QSize(82, 82));
    m_aboutButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_aboutButton->setCheckable(true);
    m_aboutButton->setObjectName("aboutButton");

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(m_measureButton, 0);
    buttonGroup->addButton(m_statisticsButton, 1);
    buttonGroup->addButton(m_historyButton, 2);
    buttonGroup->addButton(m_helpButton, 3);
    buttonGroup->addButton(m_aboutButton, 4);

    /* QStackedWidget */
    m_stackedWidget->addWidget(m_measureWidget);
    m_stackedWidget->addWidget(m_statisticsWidget);
    m_stackedWidget->setEffectEnable(true);
    m_stackedWidget->setObjectName("stackedWidget");

    /* QStatusBar */
    m_statusBar->setFixedHeight(30);
    m_statusBar->setObjectName("statusBar");

    /* layout */
    QVBoxLayout *buttonnBox = new QVBoxLayout();
    buttonnBox->addWidget(m_accountButton);
    buttonnBox->addWidget(m_userButton);
    buttonnBox->setContentsMargins(20, 0, 0, 0);

    QHBoxLayout *hBox = new QHBoxLayout();
    hBox->addWidget(m_userImage);
    hBox->addLayout(buttonnBox);
    hBox->addWidget(m_measureButton);
    hBox->addWidget(m_statisticsButton);
    hBox->addWidget(m_historyButton);
    hBox->addWidget(m_helpButton);
    hBox->addWidget(m_aboutButton);
    hBox->setAlignment(m_measureButton, Qt::AlignRight);
    hBox->setContentsMargins(20, 0, 200, 0);
    hBox->setSpacing(1);

    QVBoxLayout *vBox = new QVBoxLayout();
    vBox->addLayout(hBox);
    vBox->addWidget(m_stackedWidget);
    vBox->addWidget(m_statusBar);
    vBox->setContentsMargins(0, 0, 0, 1);
    vBox->setSpacing(0);

    /* recovery */
    this->m_recovery();

    /* connect */
    /* widget change */
    connect(buttonGroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [=](int index) { m_stackedWidget->setCurrentIndex(index); });
    /* image button */
    connect(m_userImage, &QPushButton::clicked, this, &MainWidget::m_memberInfo);
    /* menu */
    connect(m_accountButton, &QPushButton::clicked, this, &MainWidget::m_loginRegister);
    connect(m_infoMenu, &QMenu::aboutToHide, this, &MainWidget::setRedirection);
    /* action */
    connect(info, &QAction::triggered, this, &MainWidget::m_memberInfo);
    connect(modifyPassword, &QAction::triggered, this, &MainWidget::m_modifyPassword);
    connect(replaceAccount, &QAction::triggered, this, &MainWidget::m_loginRegister);
    connect(setting, &QAction::triggered, this, &MainWidget::m_setting);
    connect(logout, &QAction::triggered, this, &MainWidget::m_logout);
    /* stacked widget */
    connect(m_stackedWidget, &CustomStackedWidget::currentChanged, this, &MainWidget::m_stackedWidgetChange);
    /* newwork */
    connect(m_manager, &CustomNetwork::memberLoginStatus, this, &MainWidget::m_loginReply);


    /* window attribution */
    this->setObjectName("mainWidget");
    this->setCentralWidgetLayout(vBox);
    int index = QApplication::desktop()->primaryScreen();
    int width = QApplication::desktop()->screen(index)->width() * 7/10;
    int height = QApplication::desktop()->screen(index)->height() * 8/10;
    this->setMinimumSize(width, height);
    this->hideMenuIcon();
    int desktopWidget = QApplication::desktop()->screen(index)->width();
    int desktopHeight = QApplication::desktop()->screen(index)->height();
    this->move((desktopWidget - width)/2, (desktopHeight - height)/2 - 40);     //窗口居中
    this->startAnimation();
}

MainWidget::~MainWidget()
{
    QSettings settings("setting.ini", QSettings::IniFormat);
    settings.beginGroup("regular");
    int selected = settings.value("login").toInt();
    settings.endGroup();

    if(selected) {
        m_manager->clear();
    }
}

void MainWidget::m_memberInfo()
{
    if(m_manager->hasMember()) {
        const QUrl memberUrl("http://www.baidu.com");
        QDesktopServices::openUrl(memberUrl);
    } else {
        this->m_loginRegister();
    }
}

void MainWidget::m_modifyPassword()
{
    const QUrl memberUrl("http://www.baidu.com");
    QDesktopServices::openUrl(memberUrl);
}

void MainWidget::m_setAccountAndUser(const QVariantMap &userInfo)
{
    m_accountButton->setText(userInfo.value("phone").toString());
    m_userButton->setText(userInfo.value("name").toString());

    if(userInfo.value("sex").toString() == QStringLiteral("男")) {
        m_userImage->setIcon(QIcon(":/button/icon/boy"));
    } else if(userInfo.value("sex").toString() == QStringLiteral("女")) {
        m_userImage->setIcon(QIcon(":/button/icon/girl"));
    } else {
        m_userImage->setIcon(QIcon(":/button/icon/anonymous"));
    }

    /* save user information */
    m_settings->beginGroup("normal");
    m_settings->setValue("account", userInfo.value("phone"));
    m_settings->setValue("user", userInfo.value("name"));
    m_settings->setValue("sex", userInfo.value("sex"));
    m_settings->endGroup();

    /* 登陆成功清除操作 */
    m_measureWidget->clear();       //清除之前登陆账户所留下来的数据
    m_statisticsWidget->clear();

    m_measureButton->click();       //回到主界面
    m_accountButton->setMenu(m_infoMenu);   //设置菜单
}

void MainWidget::m_stackedWidgetChange(int index)
{
    if(m_manager->hasMember()) {
        switch(index) {
        case 0: break;
        case 1: m_statisticsWidget->getData(); break;
        default: break;
        }
    }
}

void MainWidget::m_loginReply(CustomNetwork::Status status)
{
    switch(status) {
    case CustomNetwork::Success:
        m_statusBar->showMessage(QStringLiteral("登陆成功!"), 2000);
        m_manager->downloadUserData();
        break;
    case CustomNetwork::Failure:
        break;
    case CustomNetwork::Timeout:
        break;
    default:
        break;
    }
}

void MainWidget::m_recovery()
{
    if(m_manager->hasMember()) {
        m_settings->beginGroup("normal");

        m_accountButton->setMenu(m_infoMenu);
        m_accountButton->setText(m_settings->value("account").toString());
        m_userButton->setText(m_settings->value("user").toString());

        QString sex = m_settings->value("sex").toString();
        if(sex == QStringLiteral("男")) {
            m_userImage->setIcon(QIcon(":/button/icon/boy"));
        }
        if(sex == QStringLiteral("女")){
            m_userImage->setIcon(QIcon(":/button/icon/girl"));
        }

        m_settings->endGroup();
    }
}

void MainWidget::m_loginRegister()
{
    m_loginRegisterDialog = new LoginRegisterDialog(this);
    m_loginRegisterDialog->setWindowModality(Qt::WindowModal);
    m_loginRegisterDialog->setAttribute(Qt::WA_DeleteOnClose);
    m_loginRegisterDialog->show();
    /* login & register */
    connect(m_loginRegisterDialog, &LoginRegisterDialog::loginSuccess, this, &MainWidget::m_setAccountAndUser);
}

void MainWidget::m_setting()
{
    SettingDialog *dialog = new SettingDialog(this);
    dialog->setWindowModality(Qt::WindowModal);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void MainWidget::m_logout()
{
    m_measureButton->click();       //回到主界面
    m_manager->clear();
    m_measureWidget->clear();
    m_statisticsWidget->clear();
    m_accountButton->setMenu(nullptr);
    m_accountButton->setText(QStringLiteral("点击登陆"));
    m_userButton->setText(QStringLiteral("未登录"));
    m_userImage->setIcon(QIcon(":/button/icon/anonymous"));
}

