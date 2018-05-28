#include "task.h"

/*********************************** Task methods ***************************************/

Task::Task(QWidget *widget) :
    m_lastWidget(widget),
    m_status(status_not_started),
    m_error(QString()),
    m_isValid(true),
    m_uid(-1)
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

Task::Task() :
    m_isValid(false)
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

QWidget *Task::lastWidget() const
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

SaveDataTask::SaveDataTask(QWidget *widget, const Operation &operation):
    Task(widget),
    m_operation(operation)
{
    m_type = Task::task_write;
}

Operation &SaveDataTask::operation()
{
    return m_operation;
}

/*********************************** Tasks queue methods ***************************************/

TaskQueue::TaskQueue(){
}

TaskQueue::~TaskQueue(){
    mutex_new_op.lock();
    _task_wait.clear();
    mutex_new_op.unlock();
    mutex_finished.lock();
    _task_finished.clear();
    mutex_finished.unlock();
}

int TaskQueue::addNewTask(const Task *task) {
    mutex_new_op.lock();
    _task_wait.push_back(*task);
    if (_task_wait.last().uid() == -1){
        // TODO generate new uid;
        static int id = 0;
        _task_wait.last().setUid(id++);
    }
    mutex_new_op.unlock();
    return _task_wait.last().uid();
}

void TaskQueue::addFinishedTask(const Task &task)
{
    mutex_finished.lock();
    _task_finished.push_back(task);
    mutex_finished.unlock();
}

Task TaskQueue::takeTask(){
    QMutexLocker(&this->mutex_new_op);
    mutex_new_op.lock();
    if (!_task_wait.isEmpty()){
        return _task_wait.takeFirst();
    }
    mutex_new_op.unlock();
    return Task();
}

bool TaskQueue::hasTasks() {
    return !_task_wait.isEmpty();
}

QVector<Task> TaskQueue::getTasks() {
    mutex_new_op.lock();
    QVector<Task> cpy = _task_wait;
    mutex_new_op.unlock();
    return cpy;
}

QVector<Task> TaskQueue::getFinishedTask()
{
    mutex_finished.lock();
    QVector<Task> cpy = _task_finished;
    mutex_finished.unlock();
    return cpy;
}

Task TaskQueue::getFinishedTask(qint32 uid)
{
    QMutexLocker(&this->mutex_finished);
    for(int i = 0; i < _task_finished.count(); i++){
        if (_task_finished[i].uid() == uid){
            return _task_finished.takeAt(i);
        }
    }
    return Task();
}

/******************************** Read data task ******************************/
QDateTime ReadDataTask::dt_from() const
{
    return m_dt_from;
}

void ReadDataTask::setDt_from(const QDateTime &dt_from)
{
    m_dt_from = dt_from;
}

QDateTime ReadDataTask::dt_to() const
{
    return m_dt_to;
}

void ReadDataTask::setDt_to(const QDateTime &dt_to)
{
    m_dt_to = dt_to;
}

ReadDataTask::ReadDataTask() :
    Task()
{

}

ReadDataTask::ReadDataTask(QWidget *widget) :
    Task(widget)
{
    m_type = (Task::task_read);
}

void ReadDataTask::addOperation(const Operation &op)
{
    m_read_data.push_back(op);
}

QList<Operation> ReadDataTask::read_data() const
{
    return m_read_data;
}
