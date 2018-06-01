#include "datacontainer.h"

QList<Operation *> DataContainer::operations() const
{
    return m_operations;
}

void DataContainer::setOperations(const QList<Operation *> &operations)
{
    m_operations = operations;
}

qreal DataContainer::totalIncome()
{
    qreal total = 0;
    foreach (Operation* op, m_operations) {
        if (op->dir == Operation::income){
            total += op->amount;
        }
    }
    return total;
}

qreal DataContainer::totalOutcome()
{
    qreal total = 0;
    foreach (Operation* op, m_operations) {
        if (op->dir == Operation::outcome){
            total += op->amount;
        }
    }
    return total;
}

qreal DataContainer::totalSaved()
{
    qreal total = 0;
    foreach (Operation* op, m_operations) {
        if (op->dir == Operation::outcome &&
            op->reasonIndex() == Operation::reason_saveMoney){
            total += op->amount;
        }
    }
    return total;
}

qreal DataContainer::totalDifference()
{
    qreal total = 0;
    foreach (Operation* op, m_operations) {
        if (op->dir == Operation::income){
            total += op->amount;
        }
        if (op->dir == Operation::outcome){
            total -= op->amount;
        }
    }
    return total;
}

QList<QVector<QVariant>* > DataContainer::getTable(TableTypes type)
{
    QList<QVector<QVariant>* > table;
    QVector<QVariant> tmp;
    split_operations();
    switch (type) {
    case DataContainer::filtering_only:
        tmp << "Date" << "Time" << "Reason" << "Amount" << "Comment";
        table.push_back(new QVector<QVariant>(tmp));
        foreach (Operation* op, m_operations) {
            tmp.clear();
            if (op->dir == Operation::outcome)
                tmp << op->date_time.date() << op->date_time.time() << op->reason << op->amount << op->comment;
            else
                tmp << op->date_time.date() << op->date_time.time() << "---" << op->amount << op->comment;
            table.push_back(new QVector<QVariant>(tmp));
        }
        break;
    case DataContainer::summary_by_dates:
        tmp << "Date" << "Direction" << "Amount";
        table.push_back(new QVector<QVariant>(tmp));
        getDailySummary(table, m_operations_income);
        getDailySummary(table, m_operations_outcome);
        break;
    case DataContainer::summary_by_monthes:
        tmp << "Date"  << "Direction" << "Amount";
        table.push_back(new QVector<QVariant>(tmp));
        getMonthlySummary(table, m_operations_income);
        getMonthlySummary(table, m_operations_outcome);
        break;
    case DataContainer::summary_by_reason:
        tmp << "Reason" << "Amount";
        table.push_back(new QVector<QVariant>(tmp));
        getSummaryByReason(table, m_operations_outcome);
        break;
    case DataContainer::balance_by_monthes:
        tmp << "Date"  << "Amount";
        table.push_back(new QVector<QVariant>(tmp));
        getMonthlyBalance(table, m_operations);
        break;
    case DataContainer::balance_by_dates:
        tmp << "Date" << "Amount";
        table.push_back(new QVector<QVariant>(tmp));
        getDailyBalance(table, m_operations);
    default:
        break;
    }
    return table;
}

void DataContainer::split_operations()
{
    m_operations_income.clear();
    m_operations_outcome.clear();
    foreach (Operation* op, m_operations) {
        if (op->dir == Operation::income)
            m_operations_income << op;
        else
            m_operations_outcome << op;
    }
}

void DataContainer::getDailySummary(QList<QVector<QVariant> *> &table, QList<Operation *> ops)
{
    if (ops.isEmpty())
        return;

    QDate tmp_date = ops.first()->date_time.date();
    qreal tmp_amount = 0;
    foreach (Operation* op, ops) {
        bool cmp_res = tmp_date == op->date_time.date();
        if (cmp_res){
            tmp_amount += op->amount;
        }

        if (!cmp_res || op == ops.last()){
            QVector<QVariant> tmp;
            tmp << tmp_date.toString("yyyy-MM-dd") << op->direction_name() << tmp_amount;
            table.push_back(new QVector<QVariant>(tmp));
            tmp_date = op->date_time.date();
            tmp_amount = op->amount;
        }
    }
}

void DataContainer::getMonthlySummary(QList<QVector<QVariant> *> &table, QList<Operation *> ops){
    if (ops.isEmpty())
        return;

    QDate tmp_date = ops.first()->date_time.date();
    qreal tmp_amount = 0;
    foreach (Operation* op, ops) {
        bool res = tmp_date.month() == op->date_time.date().month() &&
                tmp_date.year() == op->date_time.date().year();
        if (res){
            tmp_amount += op->amount;
        }
        if (!res || op == ops.last()){
            QVector<QVariant> tmp;
            tmp << tmp_date.toString("yyyy-MM") << op->direction_name() << tmp_amount;
            table.push_back(new QVector<QVariant>(tmp));
            tmp_date = op->date_time.date();
            tmp_amount = op->amount;
        }
    }
}

void DataContainer::getSummaryByReason(QList<QVector<QVariant> *> &table, QList<Operation *> ops)
{
    if (ops.isEmpty())
        return;

    QVector<qreal> amount_by_reason;
    for(int i = 0; i < Operation::reason_last; i++){
        amount_by_reason.push_back(0);
    }

    foreach (Operation* op, ops) {
        amount_by_reason[op->reasonIndex()] += op->amount;
    }

    for(int i = 0; i < amount_by_reason.count(); i++){
        QVector<QVariant> tmp;
        tmp << Operation::getReasonsNames().at(i) << amount_by_reason[i];
        table.push_back(new QVector<QVariant>(tmp));
    }
}

void DataContainer::getDailyBalance(QList<QVector<QVariant> *> &table, QList<Operation *> ops)
{
    if (ops.isEmpty())
        return;

    QDate tmp_date = ops.first()->date_time.date();
    qreal tmp_amount = 0;
    foreach (Operation* op, ops) {
        if (tmp_date == op->date_time.date()){
            if (op->dir == Operation::outcome)
                tmp_amount -= op->amount;
            else if (op->dir == Operation::income)
                tmp_amount += op->amount;
        }

        if (tmp_date != op->date_time.date() || op == ops.last()){
            QVector<QVariant> tmp;
            tmp << tmp_date.toString("yyyy-MM-dd") << tmp_amount;
            table.push_back(new QVector<QVariant>(tmp));
            tmp_date = op->date_time.date();
            if (op->dir == Operation::outcome)
                tmp_amount = -op->amount;
            else if (op->dir == Operation::income)
                tmp_amount = op->amount;
        }
    }
}

void DataContainer::getMonthlyBalance(QList<QVector<QVariant> *> &table, QList<Operation *> ops)
{
    if (ops.isEmpty())
        return;

    QDate tmp_date = ops.first()->date_time.date();
    qreal tmp_amount = 0;
    foreach (Operation* op, ops) {
        bool res = tmp_date.month() == op->date_time.date().month() &&
                tmp_date.year() == op->date_time.date().year();

        if (res){
            if (op->dir == Operation::outcome)
                tmp_amount -= op->amount;
            else if (op->dir == Operation::income)
                tmp_amount += op->amount;
        }

        if (!res || op == ops.last()){
            QVector<QVariant> tmp;
            tmp << tmp_date.toString("yyyy-MM") << tmp_amount;
            table.push_back(new QVector<QVariant>(tmp));
            tmp_date = op->date_time.date();
            tmp_amount = op->amount;
        }
    }
}

DataContainer::DataContainer(QObject *parent) : QObject(parent)
{

}
