#ifndef QUESTIONNAIREDIALOG_H
#define QUESTIONNAIREDIALOG_H

#include "sources/userclass/customdialog.h"

class QLabel;
class QPushButton;
class QuestionWidget;
class QStackedWidget;
class QGroupBox;

class QuestionnaireDialog : public CustomDialog
{
    Q_OBJECT
public:
    explicit QuestionnaireDialog(QWidget *parent = 0);

signals:

public slots:

private:
    QPushButton *m_titleButton = nullptr;
    QPushButton *m_stepOneButton = nullptr;
    QPushButton *m_stepTwoButton = nullptr;
    QPushButton *m_stepThreeButton = nullptr;
    QPushButton *m_stepFourButton = nullptr;
    QuestionWidget *m_stepOne = nullptr;
    QuestionWidget *m_stepTwo = nullptr;
    QuestionWidget *m_stepThree = nullptr;
    QuestionWidget *m_stepFour = nullptr;
    QStackedWidget *m_stackedWidget = nullptr;
    QWidget *m_homePage = nullptr;
    QGroupBox *m_questionPage = nullptr;

private slots:
    void m_showMain();
    void m_showStep(int index);

    void m_showStepOneResult(int score);
    void m_showStepTwoResult(int score);
    void m_showStepThreeResult(int score);
    void m_showStepFourResult(int score);
};

#endif // QUESTIONNAIREDIALOG_H
