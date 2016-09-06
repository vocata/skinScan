#include "mainwidget.h"
#include "mainstatusbar.h"
#include "measurewidget.h"
#include "statisticswidget.h"
#include "sources/customDialog/loginregisterdialog.h"
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

    /* QPushButton */
    m_infoMenu = new QMenu(this);
    m_infoMenu->setFixedWidth(150);
    m_infoMenu->setObjectName("infoMenu");
    QAction *info = new QAction(QIcon(":/menu/icon/info"), QStringLiteral("基本信息"), this);
    QAction *modifyPassword = new QAction(QStringLiteral("修改密码"), this);
    QAction *replaceAccount = new QAction(QIcon(":/menu/icon/exchange"), QStringLiteral("更换账号"), this);
    QAction *logout = new QAction(QIcon(":/menu/icon/loginout"), QStringLiteral("注销"), this);
    m_infoMenu->addAction(info);
    m_infoMenu->addSeparator();
    m_infoMenu->addAction(modifyPassword);
    m_infoMenu->addAction(replaceAccount);
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
    buttonGroup->addButton(m_measureButton);
    buttonGroup->addButton(m_statisticsButton);
    buttonGroup->addButton(m_historyButton);
    buttonGroup->addButton(m_helpButton);
    buttonGroup->addButton(m_aboutButton);

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
    if(m_manager->hasMember()) {
        m_accountButton->setMenu(m_infoMenu);
        m_accountButton->setText(QSettings().value("normal/account").toString());
        m_userButton->setText(QSettings().value("normal/user").toString());

        QString sex = QSettings().value("normal/sex").toString();
        if(sex == QStringLiteral("男")) {
            m_userImage->setIcon(QIcon(":/button/icon/boy"));
        }
        if(sex == QStringLiteral("女")){
            m_userImage->setIcon(QIcon(":/button/icon/girl"));
        }
    }

    /* connect */
    /* widget change */
    connect(m_measureButton, &QToolButton::clicked, this, &MainWidget::m_stackedMeasureWidget);
    connect(m_statisticsButton, &QToolButton::clicked, this, &MainWidget::m_stackedStatisticsWidget);
    /* image button */
    connect(m_userImage, &QPushButton::clicked, this, &MainWidget::m_memberInfo);
    /* menu */
    connect(m_accountButton, &QPushButton::clicked, this, &MainWidget::m_loginRegister);
    connect(m_infoMenu, &QMenu::aboutToHide, this, &MainWidget::setRedirection);
    /* action */
    connect(info, &QAction::triggered, this, &MainWidget::m_memberInfo);
    connect(modifyPassword, &QAction::triggered, this, &MainWidget::m_modifyPassword);
    connect(replaceAccount, &QAction::triggered, this, &MainWidget::m_loginRegister);
    connect(logout, &QAction::triggered, this, &MainWidget::m_logout);


    /* window attribution */
    this->setObjectName("mainWidget");
    this->setCentralWidgetLayout(vBox);
    int index = QApplication::desktop()->primaryScreen();
    int width = QApplication::desktop()->screen(index)->width() * 7/10;
    int height = QApplication::desktop()->screen(index)->height() * 8/10;
    this->setMinimumSize(width, height);
    int desktopWidget = QApplication::desktop()->screen(index)->width();
    int desktopHeight = QApplication::desktop()->screen(index)->height();
    this->move((desktopWidget - width)/2, (desktopHeight - height)/2 - 40);     //窗口居中
    this->startAnimation();
}

void MainWidget::m_stackedMeasureWidget()
{
    m_stackedWidget->setCurrentIndex(0);
}

void MainWidget::m_stackedStatisticsWidget()
{
    m_stackedWidget->setCurrentIndex(1);
}

void MainWidget::m_stackedHistoryWidget()
{
    m_stackedWidget->setCurrentIndex(2);
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
    QSettings().setValue("normal/account", userInfo.value("phone"));
    QSettings().setValue("normal/user", userInfo.value("name"));
    QSettings().setValue("normal/sex", userInfo.value("sex"));

    m_measureWidget->clear();       //清除之前登陆账户所留下来的测量数据，更换账户和新用户登陆时有用
    m_accountButton->setMenu(m_infoMenu);

    /* login & register */
    disconnect(m_loginRegisterDialog, &LoginRegisterDialog::loginSuccess, this, &MainWidget::m_setAccountAndUser);
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

void MainWidget::m_logout()
{
    m_manager->clear();
    m_measureWidget->clear();
    m_accountButton->setMenu(nullptr);
    m_accountButton->setText(QStringLiteral("点击登陆"));
    m_userButton->setText(QStringLiteral("未登录"));
    m_userImage->setIcon(QIcon(":/button/icon/anonymous"));
}

