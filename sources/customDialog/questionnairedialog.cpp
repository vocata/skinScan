#include "messagedialog.h"
#include "questionnairedialog.h"
#include "sources/customDialog/questionnairedialog/questionwidget.h"

#include <QButtonGroup>
#include <QGroupBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QVboxLayout>

#include <QDebug>

QuestionnaireDialog::QuestionnaireDialog(QWidget *parent) : CustomDialog(parent)
{
    m_titleButton = new QPushButton(QStringLiteral("< 返回其它测试"), this);
    m_stepOneButton = new QPushButton(QStringLiteral("干性皮肤 VS 油性皮肤"), this);
    m_stepTwoButton = new QPushButton(QStringLiteral("敏感性皮肤 VS 耐受性皮肤"), this);
    m_stepThreeButton = new QPushButton(QStringLiteral("色素沉着性皮肤 VS 非色素沉着性皮肤"), this);
    m_stepFourButton = new QPushButton(QStringLiteral("皱纹性皮肤 VS 紧致性皮肤"), this);
    m_stepOne = new QuestionWidget(":/question/text/step1");
    m_stepTwo = new QuestionWidget(":/question/text/step2");
    m_stepThree = new QuestionWidget(":/question/text/step3");
    m_stepFour = new QuestionWidget(":/question/text/step4");
    m_stackedWidget = new QStackedWidget(this);
    m_homePage = new QWidget(this);
    m_questionPage = new QGroupBox(this);

    /* title button */
    m_titleButton->setObjectName("titleButton");

    /* button */
    m_stepOneButton->setFixedSize(250, 40);
    m_stepOneButton->setObjectName("stepOneButton");

    m_stepTwoButton->setFixedSize(250, 40);
    m_stepTwoButton->setObjectName("stepTwoButton");

    m_stepThreeButton->setFixedSize(250, 40);
    m_stepThreeButton->setObjectName("stepThreeButton");

    m_stepFourButton->setFixedSize(250, 40);
    m_stepFourButton->setObjectName("stepFourButton");

    m_homePage->setObjectName("homePage");

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(m_stepOneButton, 0);
    buttonGroup->addButton(m_stepTwoButton, 1);
    buttonGroup->addButton(m_stepThreeButton, 2);
    buttonGroup->addButton(m_stepFourButton, 3);

    /* stacked widget */
    m_stackedWidget->addWidget(m_stepOne);
    m_stackedWidget->addWidget(m_stepTwo);
    m_stackedWidget->addWidget(m_stepThree);
    m_stackedWidget->addWidget(m_stepFour);

    /* layout */
    QVBoxLayout *homeBox = new QVBoxLayout(m_homePage);
    homeBox->addWidget(m_stepOneButton, 0, Qt::AlignHCenter);
    homeBox->addWidget(m_stepTwoButton, 0, Qt::AlignHCenter);
    homeBox->addWidget(m_stepThreeButton, 0, Qt::AlignHCenter);
    homeBox->addWidget(m_stepFourButton, 0, Qt::AlignHCenter);

    QVBoxLayout *questionBox = new QVBoxLayout(m_questionPage);
    questionBox->addWidget(m_stackedWidget);


    QVBoxLayout *vBox = new QVBoxLayout();
    vBox->addWidget(m_homePage);
    vBox->addWidget(m_questionPage);

    /* connect */
    connect(m_titleButton, &QPushButton::clicked, this, &QuestionnaireDialog::m_showMain);
    connect(buttonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &QuestionnaireDialog::m_showStep);
    connect(m_stepOne, &QuestionWidget::score, this, &QuestionnaireDialog::m_showStepOneResult);
    connect(m_stepTwo, &QuestionWidget::score, this, &QuestionnaireDialog::m_showStepTwoResult);
    connect(m_stepThree, &QuestionWidget::score, this, &QuestionnaireDialog::m_showStepThreeResult);
    connect(m_stepFour, &QuestionWidget::score, this, &QuestionnaireDialog::m_showStepFourResult);
    /* close */
    connect(m_stepOne, &QuestionWidget::quit, this, &QuestionnaireDialog::accept);
    connect(m_stepTwo, &QuestionWidget::quit, this, &QuestionnaireDialog::accept);
    connect(m_stepThree, &QuestionWidget::quit, this, &QuestionnaireDialog::accept);
    connect(m_stepFour, &QuestionWidget::quit, this, &QuestionnaireDialog::accept);

    /* windows Attribution */
    this->m_showMain();
    this->setWindowTitle(m_titleButton);
    this->setCentralWidgetLayout(vBox);
    this->setShadow(true);
    this->hideMinIcon();
    this->setFixedSize(700, 400);
    this->startAnimation();
    this->centralWidget()->setObjectName("centralDialog");
}

void QuestionnaireDialog::m_showMain()
{
    m_titleButton->hide();
    m_questionPage->hide();
    m_homePage->show();
    m_stepOne->clear();
    m_stepTwo->clear();
    m_stepThree->clear();
    m_stepFour->clear();
    m_stackedWidget->setCurrentIndex(0);
}

void QuestionnaireDialog::m_showStep(int index)
{
    m_homePage->hide();
    m_titleButton->show();
    m_questionPage->show();
    m_stackedWidget->setCurrentIndex(index);
}

void QuestionnaireDialog::m_showStepOneResult(int score)
{
    QString result;
    if(score > 330) {
        result = QStringLiteral("重度油性皮肤!");
    } else if(score > 260) {
        result = QStringLiteral("轻微油性皮肤!");
    } else if(score > 160) {
        result = QStringLiteral("轻微干性皮肤!");
    } else {
        result = QStringLiteral("重度干性皮肤!");
    }
    result = QStringLiteral("你的皮肤类型为: \n") + result;
    MessageDialog dialog(this);
    dialog.execInformation(result, QStringLiteral("敏感性皮肤 VS 耐受性皮肤"));
}

void QuestionnaireDialog::m_showStepTwoResult(int score)
{
    QString result;
    if(score > 330) {
        result = QStringLiteral("高敏感性皮肤!");
    } else if(score > 290) {
        result = QStringLiteral("轻敏感性皮肤!");
    } else if(score > 170) {
        result = QStringLiteral("轻耐受性皮肤!");
    } else {
        result = QStringLiteral("高耐受性皮肤!");
    }
    result = QStringLiteral("你的皮肤类型为: \n") + result;
    MessageDialog dialog(this);
    dialog.execInformation(result, QStringLiteral("色素沉着性皮肤 VS 非色素沉着性皮肤"));
}

void QuestionnaireDialog::m_showStepThreeResult(int score)
{
    QString result;
    if(score > 280) {
        result = QStringLiteral("色素沉着性皮肤!");
    } else {
        result = QStringLiteral("非色素沉着性皮肤!");
    }
    result = QStringLiteral("你的皮肤类型为: \n") + result;
    MessageDialog dialog(this);
    dialog.execInformation(result, QStringLiteral("干性皮肤 VS 油性皮肤"));
}

void QuestionnaireDialog::m_showStepFourResult(int score)
{
    QString result;
    if(score > 400) {
        result = QStringLiteral("皱纹性皮肤!");
    } else {
        result = QStringLiteral("紧致性皮肤!");
    }
    result = QStringLiteral("你的皮肤类型为: \n") + result;
    MessageDialog dialog(this);
    dialog.execInformation(result, QStringLiteral("皱纹性皮肤 VS 紧致性皮肤"));
}
