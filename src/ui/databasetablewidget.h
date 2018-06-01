#ifndef DATABASETABLEWIDGET_H
#define DATABASETABLEWIDGET_H

#include "qtablesortwidget.h"
#include "data/datacontainer.h"
#include "data/task.h"
#include "widgetforstack.h"

class DatabaseTableWidget : public QTableSortWidget
{
    Q_OBJECT
public:
    DataContainer::TableTypes tableType_current, tableType_request;
    DataFilter filter;
    DatabaseTableWidget(QWidget* parent);
public slots:
    /**
     * @brief updateData
     * Analyze all PROPERTIES of widget, and create task to get that
     */
    void updateData();
    /**
     * @brief operationFinished
     * @param table in vectors
     * Get requested data from task, and put it to table
     */
    void operationFinished(QList<QVector<QVariant> *> data);
signals:
    void updateDataRequest(DataContainer::TableTypes type);
};

#endif // DATABASETABLEWIDGET_H
