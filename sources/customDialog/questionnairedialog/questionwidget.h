#ifndef QUESTIONWIDGET_H
#define QUESTIONWIDGET_H

#include <QMap>
#include <QWidget>

class QRadioButton;
class QLabel;
class QPushButton;
class QButtonGroup;
class QTextStream;

class QuestionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QuestionWidget(const QString &fileName, QWidget *parent = 0);

signals:
    void score(int s);
    void quit();

public slots:
    void setQuestion(int index);
    void clear();

private:
    QMap<int, QStringList> m_questionsAndAnswers;

    QLabel *m_question = nullptr;
    QRadioButton *m_aRadio = nullptr;
    QRadioButton *m_bRadio = nullptr;
    QRadioButton *m_cRadio = nullptr;
    QRadioButton *m_dRadio = nullptr;
    QRadioButton *m_eRadio = nullptr;
    QPushButton *m_preButton = nullptr;
    QPushButton *m_nextButton = nullptr;
    QButtonGroup *m_buttonGroup = nullptr;

    int m_currentIndex = 0;     //记住当前题目索引

    QList<int> m_score;

private slots:
    void m_handleText(QTextStream &in);
    void m_nextQuestion();
    void m_preQuestion();
};

#endif // QUESTIONWIDGET_H
