#ifndef QUESTIONNAIREDIALOG_H
#define QUESTIONNAIREDIALOG_H

#include "sources/userclass/customdialog.h"

class QLabel;
class QPushButton;
class QStackedWidget;

class QuestionnaireDialog : public CustomDialog
{
    Q_OBJECT
public:
    explicit QuestionnaireDialog(QWidget *parent = 0);

signals:

public slots:
};

#endif // QUESTIONNAIREDIALOG_H
