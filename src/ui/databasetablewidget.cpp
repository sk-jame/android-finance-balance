#include "databasetablewidget.h"

DatabaseTableWidget::DatabaseTableWidget(QWidget *parent)
    : QTableSortWidget(parent),
      tableType_current(DataContainer::filtering_only)
{
    filter.filterType = DataFilter::filter_disabled;
}

void DatabaseTableWidget::updateData()
{
// TODO
    emit updateDataRequest(tableType_request);
}

void DatabaseTableWidget::operationFinished(QList<QVector<QVariant> > data)
{
    this->clear();
    {
        QStringList list;
        foreach (QVariant v, data.first()) {
            list << v.toString();
        }
        setHorizontalHeaderLabels(list);
    }

    for(int i = 1; i < data.count(); i++){
        for(int j = 0; j < data.at(i).count(); j++)
            this->setItem(i, j, new QTableWidgetItem(data.at(i).at(j).toString()));
    }

    this->hide();
    this->show();
}
