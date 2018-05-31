#ifndef TASK_H
#define TASK_H

#include "operations.h"
#include <QMutexLocker>
#include <QList>
#include <QVector>
#include <QObject>

class WidgetForStack;
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
    Task(WidgetForStack* widget);
    virtual ~Task();
    WidgetForStack *lastWidget() const;
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
    int attempts() const;
    void attempts_inc();
protected:
    bool m_remove_on_finish;
    TaskType m_type;
    WidgetForStack* m_lastWidget;
    TaskStatus m_status;
    QString m_error;
    bool m_isValid;
    int m_attempts;

};

class SaveDataTask : public Task
{
public:
    SaveDataTask();
    virtual ~SaveDataTask();
    explicit SaveDataTask(WidgetForStack* widget, const Operation& operation);
    const Operation* operation() const ;
private:
    Operation* m_operation;
};

class ReadDataTask : public Task
{
    QList<Operation*> m_read_data;
    QDateTime m_dt_from, m_dt_to;
public:
    ReadDataTask();
    virtual ~ReadDataTask();
    explicit ReadDataTask(WidgetForStack* widget);
    void addOperation(const Operation& op);
    const QList<Operation *> &read_data() const;

    QDateTime dt_from() const;
    void setDt_from(const QDateTime &dt_from);
    QDateTime dt_to() const;
    void setDt_to(const QDateTime &dt_to);
};

class TaskQueue : public QObject
{
    Q_OBJECT
    QVector<Task*> _task_wait, _task_finished;
    QMutex mutex_new_op, mutex_finished;
public:
    TaskQueue();
    /**
     * @brief ~TaskQueue
     * It thing that all task in _task_wait and _task_finished
     * are ALLOCATED and can be RELEASED!
     * Task which have m_remove_on_finish flag in 1 - not exists
     * in _task_finished and _task_wait lists after executing them
     */
    virtual ~TaskQueue();
    int addNewTask(Task *task);
    void addFinishedTask(Task *task);
    Task* takeTask();
    bool hasTasks();
    QVector<Task*> getTasks();
    QVector<Task*> takeFinishedTask();
    Task* takeFinishedTask(qint32 uid);
public slots:
    void removeTask(Task* task);
signals:
    void finished_task(Task*);

};

#endif // TASK_H
