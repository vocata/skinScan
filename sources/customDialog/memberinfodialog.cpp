#include "memberinfodialog.h"
#include "sources/customDialog/memberinfodialog/editwidget.h"
#include "sources/customDialog/memberinfodialog/infowidget.h"

#include <QHBoxLayout>
#include <QToolButton>
#include <QStackedWidget>
#include <QLabel>
#include <QPushButton>

MemberInfoDialog::MemberInfoDialog(QWidget *parent) : CustomDialog(parent)
{
    m_icon = new QPushButton(this);
    m_infoWidget = new InfoWidget(this);
    m_editWidget = new EditWidget(this);
    m_stackedWidget = new QStackedWidget(this);
    m_editButton = new QToolButton(this);
    m_confirmButton = new QToolButton(this);
    m_cancelButton = new QToolButton(this);
    m_manager = new CustomNetwork(this);

    /* titleLabel */
    QLabel *titleLabel = new QLabel(QStringLiteral("个人资料"), this);

    /* pushButton */
    m_icon->setIconSize(QSize(60, 60));
    m_icon->setFixedSize(QSize(64, 64));

    /* toolButton */
    m_editButton->setText(QStringLiteral("编辑资料"));
    m_editButton->show();
    m_editButton->setFixedSize(60, 25);

    m_confirmButton->setText(QStringLiteral("保存"));
    m_confirmButton->hide();
    m_confirmButton->setFixedSize(40, 25);

    m_cancelButton->setText(QStringLiteral("取消"));
    m_cancelButton->hide();
    m_cancelButton->setFixedSize(40, 25);

    /* stackedWidget */
    m_stackedWidget->addWidget(m_infoWidget);
    m_stackedWidget->addWidget(m_editWidget);
    m_stackedWidget->setCurrentIndex(0);

    /* layout */
    QHBoxLayout *buttonBox = new QHBoxLayout();
    buttonBox->addWidget(m_icon, 0, Qt::AlignLeft);
    buttonBox->addWidget(m_editButton, 0, Qt::AlignRight | Qt::AlignBottom);
    buttonBox->addWidget(m_confirmButton, 0, Qt::AlignRight | Qt::AlignBottom);
    buttonBox->addWidget(m_cancelButton, 0, Qt::AlignBottom);

    QVBoxLayout *vBox = new QVBoxLayout();
    vBox->addLayout(buttonBox);
    vBox->addWidget(m_stackedWidget);

    /* connect */
    connect(m_editButton, &QToolButton::clicked, this, &MemberInfoDialog::m_edit);
    connect(m_confirmButton, &QToolButton::clicked, this, &MemberInfoDialog::m_save);
    connect(m_cancelButton, &QToolButton::clicked, this, &MemberInfoDialog::m_cancel);
    /* widget */
    connect(m_editWidget, &EditWidget::infoEdited, m_confirmButton, &QToolButton::setEnabled);
    /* network */
    connect(m_manager, &CustomNetwork::getUserInfoStatus, this, &MemberInfoDialog::m_getUserInfoReply);
    connect(m_manager, &CustomNetwork::updateUserInfoStatus, this, &MemberInfoDialog::m_updateUserInfoReply);
    connect(this, &MemberInfoDialog::animationFinish, m_manager, &CustomNetwork::getUserInfo);

    this->setWindowTitle(titleLabel);
    this->setCentralWidgetLayout(vBox);
    this->setShadow(true);
    this->hideMinIcon();
    this->setFixedSize(300, 400);
    this->startAnimation();
    this->centralWidget()->setObjectName("centralDialog");
}

void MemberInfoDialog::m_edit()
{
    this->m_showEditWidget();
}

void MemberInfoDialog::m_save()
{
    m_editWidget->save();
    m_manager->updateUserInfo(m_editWidget->getInfo());
}

void MemberInfoDialog::m_cancel()
{
    m_editWidget->cancel();

    this->m_showInfoWidget();
}

void MemberInfoDialog::m_showEditWidget()
{
    m_confirmButton->setEnabled(false);
    m_editButton->hide();
    m_confirmButton->show();
    m_cancelButton->show();

    m_stackedWidget->setCurrentIndex(1);
}

void MemberInfoDialog::m_showInfoWidget()
{
    m_editButton->show();
    m_confirmButton->hide();
    m_cancelButton->hide();

    m_stackedWidget->setCurrentIndex(0);
}

void MemberInfoDialog::m_setIcon()
{
    QString sex = m_manager->userInfo().value("sex").toString();
    if(sex == QStringLiteral("男")) {
        m_icon->setIcon(QIcon(":/button/icon/boy"));
    } else if(sex == QStringLiteral("女")){
        m_icon->setIcon(QIcon(":/button/icon/girl"));
    } else {
        m_icon->setIcon(QIcon(":/button/icon/anonymous"));
    }
}

void MemberInfoDialog::m_getUserInfoReply(CustomNetwork::Status status)
{
    switch(status) {
    case CustomNetwork::Success:
        m_infoWidget->setInfo(m_manager->userInfo());
        m_editWidget->setInfo(m_manager->userInfo());
        this->m_setIcon();
        emit infoChanged();
        break;
    case CustomNetwork::Failure: break;
    case CustomNetwork::Timeout: break;
    default: break;
    }
}

void MemberInfoDialog::m_updateUserInfoReply(CustomNetwork::Status status)
{
    switch(status) {
    case CustomNetwork::Success:
        this->m_showInfoWidget();
        m_manager->getUserInfo();       //更新setting,改变头像
        break;
    case CustomNetwork::Failure: break;
    case CustomNetwork::Timeout: break;
    default: break;
    }
}
