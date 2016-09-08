#include "messagedialog.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

MessageDialog::MessageDialog(QWidget *parent) : CustomDialog(parent)
{
    m_okButton = new QPushButton(QStringLiteral("确定"), this);
    m_yesButton = new QPushButton(QStringLiteral("是"), this);
    m_noButton = new QPushButton(QStringLiteral("否"), this);
    m_messageIcon = new QPushButton(this);
    m_messageLabel = new QLabel(this);

    /* pushButton */
    m_okButton->setFixedSize(80, 30);
    m_okButton->setIcon(QIcon(":/message/icon/yes"));
    m_okButton->setIconSize(QSize(25, 25));
    m_okButton->setObjectName("okButton");

    m_yesButton->setFixedSize(80, 30);
    m_yesButton->setIcon(QIcon(":/message/icon/yes"));
    m_yesButton->setIconSize(QSize(25, 25));
    m_yesButton->setObjectName("yesButton");

    m_noButton->setFixedSize(80, 30);
    m_noButton->setIcon(QIcon(":/message/icon/no"));
    m_noButton->setIconSize(QSize(25, 25));
    m_noButton->setObjectName("noButton");

    /* icon */
    m_messageIcon->setFocusPolicy(Qt::NoFocus);
    m_messageIcon->setFixedSize(56, 56);
    m_messageIcon->setObjectName("messageIcon");

    /* layout */
    QHBoxLayout *msgBox = new QHBoxLayout();
    msgBox->addWidget(m_messageIcon);
    msgBox->addWidget(m_messageLabel);
    msgBox->setSpacing(5);

    QHBoxLayout *buttonBox = new QHBoxLayout();
    buttonBox->addWidget(m_okButton);
    buttonBox->addWidget(m_yesButton);
    buttonBox->addWidget(m_noButton);

    QVBoxLayout *vBox = new QVBoxLayout();
    vBox->addLayout(msgBox);
    vBox->addLayout(buttonBox);
    vBox->setSpacing(20);

    /* connect */
    connect(m_okButton, &QPushButton::clicked, this, &MessageDialog::m_okButtonClicked);
    connect(m_yesButton, &QPushButton::clicked, this, &MessageDialog::m_yesButtonClicked);
    connect(m_noButton, &QPushButton::clicked, this, &MessageDialog::m_noButtonClicked);

    /* windows attribution */
    this->setCentralWidgetLayout(vBox);
    this->setShadow(true);
    this->hideMinIcon();
    this->startAnimation();
    this->centralWidget()->setObjectName("centralDialog");
}

void MessageDialog::execWarning(const QString &msg, const QString title)
{
    m_messageIcon->setIcon(QIcon(":/message/icon/warning"));
    m_messageIcon->setIconSize(QSize(52, 52));

    m_messageLabel->setText(msg);
    this->setWindowTitle(new QLabel(title));

    m_yesButton->hide();
    m_noButton->hide();

    /* beep */
    QApplication::beep();

    this->exec();
}

void MessageDialog::execInformation(const QString &msg, const QString title)
{
    m_messageIcon->setIcon(QIcon(":/message/icon/information"));
    m_messageIcon->setIconSize(QSize(52, 52));

    m_messageLabel->setText(msg);
    this->setWindowTitle(new QLabel(title));

    m_yesButton->hide();
    m_noButton->hide();

    /* beep */
    QApplication::beep();

    this->exec();
}

void MessageDialog::m_okButtonClicked()
{
    this->done(Ok);
}

void MessageDialog::m_yesButtonClicked()
{
    this->done(Yes);
}

void MessageDialog::m_noButtonClicked()
{
    this->done(No);
}
