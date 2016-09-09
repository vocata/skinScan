#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHBoxLayout>

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    TableWidget(QWidget *parent = 0);
    void setTable(const QString &dataName, const QStringList &otherList,const QVector<double> &data);//dataName 表头名称
    void clearTable();

private:
    QTableWidget *m_table = nullptr;

};

#endif // TABLEWIDGET_H
