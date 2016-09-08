#include "clickablelabel.h"
#include "questionwidget.h"

#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QStackedWidget>
#include <QTextStream>
#include <QPushButton>
#include <QButtonGroup>


QuestionWidget::QuestionWidget(const QString &fileName, QWidget *parent) : QWidget(parent)
{
    m_question = new QLabel(this);
    m_aRadio = new QRadioButton(this);
    m_bRadio = new QRadioButton(this);
    m_cRadio = new QRadioButton(this);
    m_dRadio = new QRadioButton(this);
    m_eRadio = new QRadioButton(this);
    m_aLabel = new ClickableLabel(this);
    m_bLabel = new ClickableLabel(this);
    m_cLabel = new ClickableLabel(this);
    m_dLabel = new ClickableLabel(this);
    m_eLabel = new ClickableLabel(this);
    m_preButton = new QPushButton(this);
    m_nextButton = new QPushButton(this);

    /* read question and anwser */
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        this->m_handleText(in);
        file.close();
    }

    /* label */
    m_question->setWordWrap(true);
    m_question->setAlignment(Qt::AlignTop);
    m_question->setFixedHeight(40);

    m_aLabel->setFixedHeight(20);
    m_bLabel->setFixedHeight(20);
    m_cLabel->setFixedHeight(20);
    m_dLabel->setFixedHeight(20);
    m_eLabel->setFixedHeight(20);

    /* radioButton */
    m_aRadio->setFixedSize(20, 20);
    m_bRadio->setFixedSize(20, 20);
    m_cRadio->setFixedSize(20, 20);
    m_dRadio->setFixedSize(20, 20);
    m_eRadio->setFixedSize(20, 20);

    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->addButton(m_aRadio, 10);
    m_buttonGroup->addButton(m_bRadio, 20);
    m_buttonGroup->addButton(m_cRadio, 30);
    m_buttonGroup->addButton(m_dRadio, 40);
    m_buttonGroup->addButton(m_eRadio, 25);

    /* pushButton */
    m_preButton->setText(QStringLiteral("上一题"));
    m_preButton->setFixedHeight(30);
    m_nextButton->setText(QStringLiteral("下一题"));
    m_nextButton->setFixedHeight(30);

    /* layout */
    QVBoxLayout *radioBox = new QVBoxLayout();
    radioBox->addWidget(m_aRadio);
    radioBox->addWidget(m_bRadio);
    radioBox->addWidget(m_cRadio);
    radioBox->addWidget(m_dRadio);
    radioBox->addWidget(m_eRadio);
    radioBox->setMargin(0);
    radioBox->setSpacing(20);

    QVBoxLayout *answerBox = new QVBoxLayout();
    answerBox->addWidget(m_aLabel);
    answerBox->addWidget(m_bLabel);
    answerBox->addWidget(m_cLabel);
    answerBox->addWidget(m_dLabel);
    answerBox->addWidget(m_eLabel);
    answerBox->setMargin(0);
    answerBox->setSpacing(20);

    QHBoxLayout *centralBox = new QHBoxLayout();
    centralBox->addLayout(radioBox);
    centralBox->addLayout(answerBox);

    QHBoxLayout *buttonBox = new QHBoxLayout();
    buttonBox->addWidget(m_preButton);
    buttonBox->addWidget(m_nextButton);


    QVBoxLayout *vBox = new QVBoxLayout(this);
    vBox->addWidget(m_question);
    vBox->addLayout(centralBox);
    vBox->addLayout(buttonBox);
    vBox->setAlignment(m_question, Qt::AlignTop);
    vBox->setAlignment(centralBox, Qt::AlignVCenter);
    vBox->setAlignment(buttonBox, Qt::AlignBottom);
    vBox->setMargin(10);
    vBox->setSpacing(10);

    /* connect */
    connect(m_preButton, &QPushButton::clicked, this, &QuestionWidget::m_preQuestion);
    connect(m_nextButton, &QPushButton::clicked, this, &QuestionWidget::m_nextQuestion);
    /* label clicked */
    connect(m_aLabel, &ClickableLabel::clicked, m_aRadio, &QRadioButton::setChecked);
    connect(m_bLabel, &ClickableLabel::clicked, m_bRadio, &QRadioButton::setChecked);
    connect(m_cLabel, &ClickableLabel::clicked, m_cRadio, &QRadioButton::setChecked);
    connect(m_dLabel, &ClickableLabel::clicked, m_dRadio, &QRadioButton::setChecked);
    connect(m_eLabel, &ClickableLabel::clicked, m_eRadio, &QRadioButton::setChecked);
}

void QuestionWidget::setQuestion(int index)
{
    if(index == 0) {
        m_preButton->setEnabled(false);
    } else {
        m_preButton->setEnabled(true);
    }
    if(index == m_questionsAndAnswers.count() - 1) {
        m_nextButton->setText(QStringLiteral("确定"));
    } else {
        m_nextButton->setText(QStringLiteral("下一题"));
    }

    /* 当前问题索引 */
    m_currentIndex = index;

    /* 设置新问题时默认选择 */
    m_aRadio->setChecked(true);

    /* 设置问题 */
    QStringList firstItem = m_questionsAndAnswers.value(index);
    if(firstItem.count() == 5) {
        m_question->setText(firstItem.at(0));
        m_aLabel->setText(firstItem.at(1));
        m_bLabel->setText(firstItem.at(2));
        m_cLabel->setText(firstItem.at(3));
        m_dLabel->setText(firstItem.at(4));
        m_eLabel->hide();
        m_eRadio->hide();
    }
    if(firstItem.count() == 6) {
        m_question->setText(firstItem.at(0));
        m_aLabel->setText(firstItem.at(1));
        m_bLabel->setText(firstItem.at(2));
        m_cLabel->setText(firstItem.at(3));
        m_dLabel->setText(firstItem.at(4));
        m_eLabel->setText(firstItem.at(5));
        m_eLabel->show();
        m_eRadio->show();
    }
}

void QuestionWidget::clear()
{
    this->setQuestion(0);
    m_score.clear();
}

void QuestionWidget::m_handleText(QTextStream &in)
{
    QString temp;
    int index = 0;

    while(!in.atEnd()) {
        if(in.readLine() == "#") {
            while((temp = in.readLine()) != "$") {
                m_questionsAndAnswers[index] << temp;
            }
            index++;
        }
    }

    /* 设置第一个问题 */
    this->setQuestion(m_currentIndex);
}

void QuestionWidget::m_nextQuestion()
{
    m_currentIndex++;
    if(m_currentIndex < m_questionsAndAnswers.count()){
        m_score.push_back(m_buttonGroup->checkedId());
        this->setQuestion(m_currentIndex);
    } else if(m_currentIndex == m_questionsAndAnswers.count()) {
        int sum = 0;
        for(const auto &num: m_score) {
            sum += num;
        }
        sum += m_buttonGroup->checkedId();
        m_preButton->setText(QStringLiteral("重新测试"));
        m_nextButton->setText(QStringLiteral("退出测试"));
        m_score.clear();
        emit score(sum);
    } else {
        emit quit();
        m_currentIndex = m_questionsAndAnswers.count() + 1;
    }
}

void QuestionWidget::m_preQuestion()
{
    if(m_score.isEmpty()) {
        this->setQuestion(0);
        m_preButton->setText(QStringLiteral("上一题"));
    } else {
        m_currentIndex--;
        m_score.pop_back();
        this->setQuestion(m_currentIndex);
    }
}
