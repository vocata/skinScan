#include "tablewidget.h"

#include <QHeaderView>
#include <QScrollBar>

TableWidget::TableWidget(QWidget *parent) : QWidget(parent)
{
    /* create table*/
    m_table = new QTableWidget(this);
    m_table->horizontalHeader()->setStretchLastSection(true);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->verticalScrollBar()->setObjectName("scrollBar");

    /* layout */
    QHBoxLayout *vBox = new QHBoxLayout(this);
    vBox->addWidget(m_table);
}

void TableWidget::setTable(const QString &dataName, const QStringList &otherList, const QVector<double> &data)
{
    m_table->setRowCount(data.size());
    m_table->setColumnCount(4);
    /* create header*/
    QStringList header;
    header << "时间" << "手机号码" << dataName << "设备";
    m_table->setHorizontalHeaderLabels(header);
    for(int nCount = 0; nCount < 4; ++nCount)
    {
        m_table->setColumnWidth(nCount, 167);
    }

    /* item */
    if(data.size() > 0)
    {
        for(int i = 0; i < data.size(); ++i)
        {
            for(int nCount = 0; nCount < 3; ++nCount)
            {
//                m_table->setItem(i , nCount, new QTableWidgetItem(otherList.at(i * 3 + nCount)));
                QTableWidgetItem *dataItem = new QTableWidgetItem(otherList.at(i * 3 + nCount));//central alignment
                dataItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                if(nCount == 2)
                    m_table->setItem(i, 3, dataItem);
                else
                    m_table->setItem(i, nCount, dataItem);
            }

            QTableWidgetItem *dataItem = new QTableWidgetItem(QString::number(data[i], 'g', 2));//central alignment
            dataItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            m_table->setItem(i, 2, dataItem);
        }
//        m_table->resizeColumnsToContents();
    }
}

void TableWidget::clearTable()
{
    m_table->clearContents();//清除内容
    m_table->setRowCount(0);
}
