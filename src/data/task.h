#ifndef TASK_H
#define TASK_H

#include <QObject>
#include "operations.h"
#include <QWidget>

class Task
{
    QWidget* m_lastWidget;
    Operation m_operation;
    TaskStatus m_status;
    QString m_error;
public:
    enum TaskStatus {
        status_not_started,
        status_success,
        status_failure,
        status_already_exist
    };

    explicit Task(QWidget* widget, Operation& operation);

    QWidget *lastWidget() const;
    Operation operation() const;
    bool finished() const;
    QString error() const;
    void setError(const QString &error);
    TaskStatus status() const;
    void setStatus(const TaskStatus &status);
};

Operation Task::operation() const
{
    return m_operation;
}

bool Task::finished() const
{
return m_finished;
}

QString Task::error() const
{
return m_error;
}

void Task::setError(const QString &error)
{
m_error = error;
}

TaskStatus Task::status() const
{
return m_status;
}

void Task::setStatus(const TaskStatus &status)
{
m_status = status;
}

Task::Task(QWidget *widget, Operation &operation):
    m_lastWidget(widget),
    m_operation(operation),
    m_status(status_not_started),
    m_error(QString())
{

}

QWidget *Task::lastWidget() const
{
    return m_lastWidget;
}

#endif // TASK_H
