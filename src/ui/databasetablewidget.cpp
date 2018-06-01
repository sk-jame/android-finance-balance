#include "databasetablewidget.h"
#include <QDebug>

DatabaseTableWidget::DatabaseTableWidget(QWidget *parent)
    : QTableSortWidget(parent),
      tableType_current(DataContainer::filtering_only),
      tableType_request(DataContainer::filtering_only)
{
    filter.filterType = DataFilter::filter_disabled;
    this->setEnabled(true);
}

void DatabaseTableWidget::updateData()
{
    // TODO
    emit updateDataRequest(tableType_request);
}

void DatabaseTableWidget::operationFinished(QList<QVector<QVariant>* > data)
{
    if (data.empty()){
        qDebug() << __FUNCTION__ << "QList<QVector<QVariant> > data is empty!";
        return;
    }
    this->setSortingEnabled(false);
    this->clear();
    this->setRowCount(data.count() - 1);
    this->setColumnCount(data.first()->count());
    {
        QStringList list;
        for(int i = 0; i < data.first()->count(); i++){
            list << data.first()->at(i).toString();
        }
        setHorizontalHeaderLabels(list);
    }
    for(int i = 1; i < data.count(); i++){
        for(int j = 0; j < data.at(i)->count(); j++)
            this->setItem(i - 1, j, new QTableWidgetItem(data.at(i)->at(j).toString()));
    }

    this->update();
//    this->hide();
//    this->show();
    this->setSortingEnabled(true);
}
