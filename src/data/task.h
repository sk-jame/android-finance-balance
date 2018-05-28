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
    virtual ~Task();
    QWidget *lastWidget() const;
    QString error() const;
    void setError(const QString &error);
    TaskStatus status() const;
    void setStatus(const TaskStatus &status);
    bool isValid() const;

    virtual int taskType();
    qint32 uid() const;
    void setUid(const qint32 &uid);
    void setRemove_on_finish(bool value);
    bool shouldRemove_on_finish();
protected:
    bool m_remove_on_finish;
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
    virtual ~SaveDataTask();
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
    virtual ~ReadDataTask();
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
    QVector<Task*> _task_wait, _task_finished;
    QMutex mutex_new_op, mutex_finished;
public:
    TaskQueue();
    ~TaskQueue();
    int addNewTask(Task *task);
    void addFinishedTask(Task *task);
    Task* takeTask();
    bool hasTasks();
    QVector<Task*> getTasks();
    QVector<Task*> takeFinishedTask();

    Task* takeFinishedTask(qint32 uid);
};

#endif // TASK_H
