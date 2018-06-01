#include "databasetablewidget.h"
#include <QDebug>
#include <QMenu>

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
    emit updateDataRequest();
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
    tableType_current = tableType_request;
}


void DatabaseTableWidget::contextMenuShow(QMouseEvent *event)
{
    QMenu menu(this);
    QAction* actCpy = menu.addAction("Копировать в буфер обмена");
    QAction* actFind = menu.addAction("Найти...");
    QMenu* menu_content = menu.addMenu("Отображать...");
    QMenu* menu_tableSelect = menu_content->addMenu("Таблицу");
    QAction* actShowIncome = menu_tableSelect->addAction("Входящие");
    QAction* actShowOutcome = menu_tableSelect->addAction("Исходящие");
    QAction* actShowAll = menu_tableSelect->addAction("Всё");

    QAction* actShowOperations = menu_content->addAction("Операции");
    QAction* actShowSummaryReason = menu_content->addAction("Сумма по причинам");
    QAction* actShowDailySummary = menu_content->addAction("Итог по дням");
    QAction* actShowMonthSummary = menu_content->addAction("Итог по месяцам");
    QAction* actShowDailyBalance = menu_content->addAction("Баланс по дням");
    QAction* actShowMonthBalance = menu_content->addAction("Баланс по месяцам");


    QRect rect = menu.geometry();
    rect.moveTopLeft(event->screenPos().toPoint());
    menu.setGeometry(rect);
    QAction* res = menu.exec();
    if (res == Q_NULLPTR){
        QTableWidget::mouseReleaseEvent(event);
        return;
    }
    if (res == actCpy){
        copyToClipBoard();
        return;
    }
    else if (res == actFind){
        QTableWidgetItem* tmp_item = itemAt(event->pos());
        if (tmp_item){
            lastSearchString = tmp_item->text();
            find(lastSearchString);
        }
        showFindPopup();
        return;
    }
    else if (res == actShowAll){
        filter.filterType |= DataFilter::filter_all_tables;
    }
    else if (res == actShowDailyBalance){
        tableType_request = DataContainer::balance_by_dates;
        filter.filterType |= DataFilter::filter_all_tables;
    }
    else if (res == actShowMonthBalance){
        tableType_request = DataContainer::balance_by_monthes;
        filter.filterType |= DataFilter::filter_all_tables;
    }
    else if (res == actShowSummaryReason){
        tableType_request = DataContainer::summary_by_reason;
    }
    else if (res == actShowDailySummary){
        tableType_request = DataContainer::summary_by_dates;
        filter.filterType |= DataFilter::filter_all_tables;
    }
    else if (res == actShowMonthSummary){
        tableType_request = DataContainer::summary_by_monthes;
        filter.filterType |= DataFilter::filter_all_tables;
    }
    else if (res == actShowIncome){
        filter.table = Operation::income;
        filter.filterType &= ~DataFilter::filter_all_tables;
    }
    else if (res == actShowOutcome){
        filter.table = Operation::outcome;
        filter.filterType &= ~DataFilter::filter_all_tables;
    }
    else if (res == actShowOperations){
        tableType_request = DataContainer::filtering_only;
    }
    else {
        return;
    }
    updateData();
}
