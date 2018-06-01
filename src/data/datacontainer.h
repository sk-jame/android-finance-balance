#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QVector>
#include <QVariant>
#include <QObject>
#include "operations.h"

class DataFilter
{
public:
    Operation::EDirection table;
    QPair<QDateTime, QDateTime> dateFilter;
    Operation::Reasons reasonFilter;
    enum FilterTypes {
        filter_disabled    = 0x00,
        filtered_by_reason = 0x01,
        filtered_by_date   = 0x02,
        filter_all_tables  = 0x128,
    };
    int filterType;

    inline bool checkType(FilterTypes type){
        return (filterType & type) == type;
    }
};

class DataContainer : public QObject
{
    Q_OBJECT
    QList<Operation*> m_operations;
    QList<Operation*> m_operations_income;
    QList<Operation*> m_operations_outcome;

    void split_operations();
    void getDailySummary(QList<QVector<QVariant>* >& table, QList<Operation*> ops);
    void getMonthlySummary(QList<QVector<QVariant> *> &table, QList<Operation *> ops);
    void getSummaryByReason(QList<QVector<QVariant> *> &table, QList<Operation *> ops);
    void getDailyBalance(QList<QVector<QVariant> *> &table, QList<Operation *> ops);
    void getMonthlyBalance(QList<QVector<QVariant> *> &table, QList<Operation *> ops);
public:
    enum TableTypes {
        filtering_only      = 0x00,
        summary_by_reason   = 0x04,
        summary_by_dates    = 0x08,
        balance_by_dates    = 0x16,
        summary_by_monthes  = 0x32,
        balance_by_monthes  = 0x64,
    };

    DataFilter filter;

    explicit DataContainer(QObject *parent = nullptr);

    QList<Operation *> operations() const;
    void setOperations(const QList<Operation *> &operations);

    qreal totalIncome();
    qreal totalOutcome();
    qreal totalSaved();
    qreal totalDifference();

    QList<QVector<QVariant> *> getTable(TableTypes type);
signals:

public slots:
};

#endif // DATACONTAINER_H
