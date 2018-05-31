#include "task.h"
#include <QDebug>
#include "ui/widgetforstack.h"

/*********************************** Task methods ***************************************/

Task::Task(WidgetForStack *widget) :
    m_uid(-1),
    m_remove_on_finish(false),
    m_lastWidget(widget),
    m_status(status_not_started),
    m_error(QString()),
    m_isValid(true),
    m_attempts(0)
{

}

Task::~Task()
{

}

qint32 Task::uid() const
{
    return m_uid;
}

void Task::setUid(const qint32 &uid)
{
    m_uid = uid;
}

void Task::setRemove_on_finish(bool value)
{
    m_remove_on_finish = value;
}

bool Task::shouldRemove_on_finish()
{
    return m_remove_on_finish;
}

int Task::attempts() const
{
    return m_attempts;
}

void Task::attempts_inc()
{
    m_attempts++;
}

void Task::setLastWidget(WidgetForStack *lastWidget)
{
    m_lastWidget = lastWidget;
    m_isValid = true;
}

Task::Task() :
    m_uid(-1),
    m_remove_on_finish(false),
    m_status(status_not_started),
    m_error(QString()),
    m_isValid(false),
    m_attempts(0)
{
    
}

QString Task::error() const
{
    return m_error;
}

void Task::setError(const QString &error)
{
    m_error = error;
}

Task::TaskStatus Task::status() const
{
    return m_status;
}

void Task::setStatus(const TaskStatus &status)
{
    m_status = status;
}

bool Task::isValid() const
{
    return m_isValid;
}

WidgetForStack *Task::lastWidget() const
{
    return m_lastWidget;
}

int Task::taskType(){
    return m_type;
}

/***************************** save data task ****************************************/

SaveDataTask::SaveDataTask():
    Task()
{

}

SaveDataTask::~SaveDataTask()
{
    qDebug() << __FUNCTION__ << __LINE__;
    if (m_operation)
        delete m_operation;
}

SaveDataTask::SaveDataTask(WidgetForStack *widget, const Operation &operation):
    Task(widget),
    m_operation(new Operation(operation))
{
    m_type = Task::task_write;
}

const Operation *SaveDataTask::operation() const
{
    return m_operation;
}

/******************************** Read data task ******************************/
ReadDataTask::ReadDataTask() :
    Task()
{

}

ReadDataTask::~ReadDataTask()
{
    qDebug() << __FUNCTION__ << __LINE__;
    while(m_read_data.count()){
        delete m_read_data.takeLast();
    }
    m_read_data.clear();
}

ReadDataTask::ReadDataTask(WidgetForStack *widget) :
    Task(widget)
{
    m_type = (Task::task_read);
}

void ReadDataTask::addOperation(const Operation &op)
{
    m_read_data.push_back(new Operation(op));
}

const QList<Operation *> &ReadDataTask::read_data() const
{
    return m_read_data;
}

/****************************** Execute query task ******************************/
ExecQueryTask::ExecQueryTask() : Task()
{

}

ExecQueryTask::ExecQueryTask(const QString &request)
    : Task(),
      m_request(request)
{

}

ExecQueryTask::ExecQueryTask(WidgetForStack *widget, const QString &request)
    : Task(widget),
      m_request(request)
{
    m_type = (Task::task_exec);
}

ExecQueryTask::~ExecQueryTask()
{

}

void ExecQueryTask::setQuery(const QSqlQuery &source)
{
    m_query = source;
}

const QSqlQuery &ExecQueryTask::query() const
{
    return m_query;
}

QString ExecQueryTask::request() const
{
    return m_request;
}

/*********************************** Tasks queue methods ***************************************/

TaskQueue::TaskQueue() : QObject(){
}

TaskQueue::~TaskQueue(){
    bool ret;
    ret = mutex_new_op.tryLock(5000);
    while(!_task_wait.isEmpty()){
        delete _task_wait.takeLast();
    }
    _task_wait.clear();
    if (ret)
        mutex_new_op.unlock();

    ret = mutex_finished.tryLock(5000);
    while(!_task_finished.isEmpty()){
        delete _task_finished.takeLast();
    }
    _task_finished.clear();
    if (ret)
        mutex_finished.unlock();
}

int TaskQueue::addNewTask(Task *task) {
    if (!mutex_new_op.tryLock(500))
        return -1;

    _task_wait.push_back(task);
    if (_task_wait.last()->uid() == -1){
        // TODO new uid generator
        static int id = 0;
        _task_wait.last()->setUid(id++);
    }
    mutex_new_op.unlock();
    return _task_wait.last()->uid();
}

void TaskQueue::addFinishedTask(Task *task)
{
    if (task->shouldRemove_on_finish()){
        removeTask(task);
        delete task;
        return;
    }
    mutex_finished.lock();
    _task_finished.push_back(task);
    mutex_finished.unlock();
    emit finished_task(task);
}

Task *TaskQueue::takeTask(){
    QMutexLocker(&this->mutex_new_op);
    if (!_task_wait.isEmpty()){
        return _task_wait.takeFirst();
    }
    return nullptr;
}

bool TaskQueue::hasTasks() {
    QMutexLocker(&this->mutex_new_op);
    return !_task_wait.isEmpty();
}

QVector<Task*> TaskQueue::getTasks() {
    QMutexLocker(&this->mutex_new_op);
    QVector<Task*> cpy = _task_wait;
    return cpy;
}

QVector<Task*> TaskQueue::takeFinishedTask()
{
    mutex_finished.lock();
    QVector<Task*> cpy = _task_finished;
    mutex_finished.unlock();
    return cpy;
}

Task *TaskQueue::takeFinishedTask(qint32 uid)
{
    QMutexLocker(&this->mutex_finished);
    for(int i = 0; i < _task_finished.count(); i++){
        if (_task_finished[i]->uid() == uid){
            return _task_finished.takeAt(i);
        }
    }
    return nullptr;
}

void TaskQueue::removeTask(Task *task)
{
    QMutexLocker(&this->mutex_new_op);
    _task_wait.removeAll(task);
    QMutexLocker(&this->mutex_finished);
    _task_finished.removeAll(task);
}
