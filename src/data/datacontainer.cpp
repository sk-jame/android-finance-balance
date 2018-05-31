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
        if (op->dir == Operation::income &&
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

QList<QVector<QVariant> > DataContainer::getTable(TableTypes type) const
{
    QList<QVector<QVariant> > table;
    QVector<QVariant> tmp;
    QDate tmp_date;
    qreal tmp_amount = 0;
    QVector<qreal> amount_by_reason;

    switch (type) {
    case DataContainer::filtering_only:
        tmp << "Date" << "Time" << "Reason" << "Amount" << "Comment";
        table.push_back(tmp);
        foreach (Operation* op, m_operations) {
            tmp.clear();
            tmp << op->date_time.date() << op->date_time.time() << op->reason << op->amount << op->comment;
            table.push_back(tmp);
        }
        break;
    case DataContainer::summary_by_dates:
        tmp << "Date" << "Direction" << "Amount";
        table.push_back(tmp);
        tmp_date = m_operations.first()->date_time.date();
        tmp_amount = 0;
        foreach (Operation* op, m_operations) {
            if (op->dir == Operation::outcome)
                continue;
            if (tmp_date == op->date_time.date()){
                tmp_amount += op->amount;
            }
            else{
                tmp.clear();
                tmp << tmp_date.date() << "Outcome" << tmp_amount;
                table.push_back(tmp);
                tmp_date = op->date_time.date();
                tmp_amount = op->amount;
            }
        }
        tmp_date = m_operations.first()->date_time.date();
        tmp_amount = 0;
        foreach (Operation* op, m_operations) {
            if (op->dir == Operation::income)
                continue;
            if (tmp_date == op->date_time.date()){
                tmp_amount += op->amount;
            }
            else{
                tmp.clear();
                tmp << tmp_date.date() << "Income" << tmp_amount;
                table.push_back(tmp);
                tmp_date = op->date_time.date();
                tmp_amount = op->amount;
            }
        }
        break;
    case DataContainer::summary_by_monthes:
        tmp << "Date"  << "Direction" << "Amount";
        table.push_back(tmp);
        tmp_amount = 0;
        tmp_date.month() = m_operations.first()->date_time.date();
        foreach (Operation* op, m_operations) {
            if (op->dir == Operation::outcome)
                continue;

            if (tmp_date.month() == op->date_time.date().month() &&
                tmp_date.year() == op->date_time.date().year()){

                tmp_amount += op->amount;
            }
            else{
                tmp.clear();
                tmp << tmp_date.date() << "Outcome" << tmp_amount;
                table.push_back(tmp);
                tmp_date = op->date_time.date();
                tmp_amount = op->amount;
            }
        }

        tmp_amount = 0;
        tmp_date.month() = m_operations.first()->date_time.date();
        foreach (Operation* op, m_operations) {
            if (op->dir == Operation::income)
                continue;
            if (tmp_date.month() == op->date_time.date().month() &&
                tmp_date.year() == op->date_time.date().year()){

                tmp_amount += op->amount;
            }
            else{
                tmp.clear();
                tmp << tmp_date.date() << "Income" << tmp_amount;
                table.push_back(tmp);
                tmp_date = op->date_time.date();
                tmp_amount = op->amount;
            }
        }

        break;
    case DataContainer::summary_by_reason:
        tmp << "Reason" << "Amount";
        table.push_back(tmp);
        amount_by_reason.reserve(Operation::reason_last);
        for(int i = 0; i < Operation::reason_last; i++){
            amount_by_reason[i] = 0;
        }

        foreach (Operation* op, m_operations) {
            if (op->dir == Operation::income)
                amount_by_reason[op->reasonIndex()] += op->amount;
        }

        for(int i = 0; i < amount_by_reason.count(); i++){
            tmp.clear();
            tmp << Operation::getReasonsNames() << amount_by_reason[i];
            table.push_back(tmp);
        }
        break;
    case DataContainer::balance_by_monthes:
        tmp << "Date"  << "Amount";
        table.push_back(tmp);
        tmp_amount = 0;
        tmp_date.month() = m_operations.first()->date_time.date();
        foreach (Operation* op, m_operations) {
            if (tmp_date.month() == op->date_time.date().month() &&
                tmp_date.year() == op->date_time.date().year()){
                if (op->dir == Operation::outcome)
                    tmp_amount -= op->amount;
                else if (op->dir == Operation::income)
                    tmp_amount += op->amount;
            }
            else{
                tmp.clear();
                tmp << tmp_date.date() << "Outcome" << tmp_amount;
                table.push_back(tmp);
                tmp_date = op->date_time.date();
                tmp_amount = op->amount;
            }
        }
        break;
    case DataContainer::balance_by_dates:
        tmp << "Date" << "Amount";
        table.push_back(tmp);
        tmp_date = m_operations.first()->date_time.date();
        tmp_amount = 0;
        foreach (Operation* op, m_operations) {
            if (tmp_date == op->date_time.date()){
                if (op->dir == Operation::outcome)
                    tmp_amount -= op->amount;
                else if (op->dir == Operation::income)
                    tmp_amount += op->amount;
            }
            else{
                tmp.clear();
                tmp << tmp_date.date() << tmp_amount;
                table.push_back(tmp);
                tmp_date = op->date_time.date();
                if (op->dir == Operation::outcome)
                    tmp_amount = -op->amount;
                else if (op->dir == Operation::income)
                    tmp_amount = op->amount;
            }
        }
    default:
        break;
    }
    return table;
}

DataContainer::DataContainer(QObject *parent) : QObject(parent)
{

}
