#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QObject>
#include "operations.h"

class DataContainer : public QObject
{
    Q_OBJECT
    QList<Operation*> m_operations;
public:
    explicit DataContainer(QObject *parent = nullptr);

    QList<Operation *> operations() const;
    void setOperations(const QList<Operation *> &operations);

    qreal totalIncome();
    qreal totalOutcome();
    qreal totalSaved();
    qreal totalDifference();
signals:

public slots:
};

#endif // DATACONTAINER_H
