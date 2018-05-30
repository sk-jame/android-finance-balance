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
            op->typeIndex() == Operation::type_saveMoney){
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

DataContainer::DataContainer(QObject *parent) : QObject(parent)
{

}
