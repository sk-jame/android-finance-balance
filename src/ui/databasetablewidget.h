#ifndef DATABASETABLEWIDGET_H
#define DATABASETABLEWIDGET_H

#include "qtablesortwidget.h"
#include "data/datacontainer.h"
#include "data/task.h"
#include "widgetforstack.h"

class DatabaseTableWidget : public QTableSortWidget
{
    Q_OBJECT

    Q_PROPERTY(ShowTypes showType READ showType WRITE setShowType NOTIFY showTypeChanged)
    Q_PROPERTY(QString table READ table WRITE setTable NOTIFY tableNameChanged)
    Q_PROPERTY(QPair<QDateTime, QDateTime> dateFilter READ dateFilter WRITE setDateFilter NOTIFY dateFilterChanged)
    Q_PROPERTY(Operation::Reasons reasonFilter READ reasonFilter WRITE setReasonFilter NOTIFY reasonFilterChanged)

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
    void operationFinished(QList<QVector<QVariant> > data);
signals:
    void updateDataRequest(DataContainer::TableTypes type);
};

#endif // DATABASETABLEWIDGET_H
