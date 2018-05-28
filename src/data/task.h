#ifndef TASK_H
#define TASK_H

#include <QMutexLocker>
#include <QList>
#include <QObject>
#include "operations.h"
#include <QWidget>

class Task
{
private:
    qint32 m_uid;
public:
    enum TaskStatus {
        status_not_started,
        status_success,
        status_failure,
        status_already_exist
    };

    enum TaskType {
        task_write = 0,
        task_read
    };

    Task();
    Task(QWidget* widget);
    QWidget *lastWidget() const;
    QString error() const;
    void setError(const QString &error);
    TaskStatus status() const;
    void setStatus(const TaskStatus &status);
    bool isValid() const;

    virtual int taskType();
    qint32 uid() const;
    void setUid(const qint32 &uid);

protected:
    TaskType m_type;
    QWidget* m_lastWidget;
    TaskStatus m_status;
    QString m_error;
    bool m_isValid;
};

class SaveDataTask : public Task
{
public:
    SaveDataTask();
    explicit SaveDataTask(QWidget* widget, const Operation& operation);
    Operation &operation();
private:
    Operation m_operation;
};

class ReadDataTask : public Task
{
    QList<Operation> m_read_data;
    QDateTime m_dt_from, m_dt_to;
public:
    ReadDataTask();
    explicit ReadDataTask(QWidget* widget);
    void addOperation(const Operation& op);
    QList<Operation> read_data() const;

    QDateTime dt_from() const;
    void setDt_from(const QDateTime &dt_from);
    QDateTime dt_to() const;
    void setDt_to(const QDateTime &dt_to);
};

class TaskQueue
{
    QVector<Task> _task_wait, _task_finished;
    QMutex mutex_new_op, mutex_finished;
public:
    TaskQueue();
    ~TaskQueue();
    int addNewTask(const Task *task);
    void addFinishedTask(const Task &task);
    Task takeTask();
    bool hasTasks();
    QVector<Task> getTasks();
    QVector<Task> getFinishedTask();

    Task getFinishedTask(qint32 uid);
};

#endif // TASK_H
