#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QVector>
#include <QVariant>
#include <QObject>
#include "common/operations.h"

class DataFilter
{
public:
    Operation::Type table;
    QPair<QDateTime, QDateTime> dateFilter;
    Operation::Reasons reasonFilter;
    enum FilterFlags {
        filter_disabled    = 0x00,
        filtered_by_reason = 0x01,
        filtered_by_date   = 0x02,
        filter_show_all_tbl  = 0x10,  /* To be honest this is the worst name in the World! Cuz, this bit is mean - show 2 tables! */
        filter_all_set     = filter_show_all_tbl | filtered_by_date | filtered_by_reason
    };
    int filterFlags;


    explicit DataFilter() :
        table(Operation::type_invalid),
        reasonFilter(Operation::reason_doesnt_matter),
        filterFlags(filter_disabled)
    {

    }

    virtual bool isReasonValid() {
        if (flag(filtered_by_reason))
            return (reasonFilter > Operation::reason_invalid &&
                    reasonFilter < Operation::reason_last);
        return true;
    }

    inline bool flag(FilterFlags f) const{
        return (filterFlags & f) == f;
    }

    virtual bool isFlagValid(){
        return !(filterFlags & (~filter_all_set));
    }

    virtual bool isDataFilterValid(){
        if (flag(filtered_by_date))
            return  dateFilter.first.isValid() &&
                    dateFilter.second.isValid() &&
                    dateFilter.second > dateFilter.first;
        return true;
    }

    virtual bool isTableValid(){
        if (flag(filter_show_all_tbl))
            return true;

        return (table < Operation::type_last && table > Operation::type_invalid);
    }

    virtual bool isValid() {
        int ret = (isTableValid() | (isDataFilterValid() << 1) | (isFlagValid() << 2) | (isReasonValid() << 3));
        return ret == 0xF;
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
