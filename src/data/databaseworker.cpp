#include <QMessageBox>
#include <QDebug>
#include "databaseworker.h"
#include <QSqlQuery>

/* constants */
//const QString SavedDataWorker::filename = ":/db/.balance.sqlite";
const QString DataBaseWorker::filename = ".balance.sqlite";
const QString DataBaseWorker::income_table_name = "Income";
const QString DataBaseWorker::outcome_table_name = "Outcome";

/* function implementation */
DataBaseWorker::DataBaseWorker(TaskQueue *task_queue, QObject *parent)
    : QObject(parent),
      sdb(QSqlDatabase::addDatabase("QSQLITE")),
      query(sdb),
      m_done(false),
      m_thread(nullptr)
{
    m_good = false;
    this->task_queue = task_queue;
    if (!init_or_create_db(filename)){
        return;
    }

    connect(this, &QObject::destroyed, &m_thread, &QThread::quit);
    connect(&m_thread, &QThread::started, this, &DataBaseWorker::process);
    this->moveToThread(&m_thread);

    if (!sdb.open()){
        qDebug() << sdb.lastError();
        return;
    }

    m_good = true;
}

DataBaseWorker::~DataBaseWorker()
{
    sdb.close();
}

QString DataBaseWorker::getFilename()
{
    return filename;
}

void DataBaseWorker::start()
{
    if (m_thread.isRunning()){
        // already started
        return;
    }

    m_thread.start();
}

bool DataBaseWorker::stop(bool terminate)
{
    if (!m_thread.isRunning())
        return true;

    if (terminate)
        m_thread.terminate();
    else
        m_thread.quit();

    return m_thread.wait();
}

bool DataBaseWorker::isGood() const
{
    return m_good;
}

void DataBaseWorker::process()
{
    while(!isDone()){
        if (task_queue->hasTasks()){
            Task* task = task_queue->takeTask();
            if (task != nullptr){
                if (task->taskType() == Task::task_write){
                    SaveDataTask* s_task = (SaveDataTask*)task;
                    task->setStatus((saveNewOperation(s_task->operation()) == 0) ?
                                       (SaveDataTask::status_success) :
                                       (SaveDataTask::status_failure));
                }
                else if (task->taskType() == Task::task_read){
                    task->setStatus((readTask(((ReadDataTask*)task)) == 0) ?
                                       (SaveDataTask::status_success) :
                                       (SaveDataTask::status_failure));
                }
            }

            if (task->status() == Task::status_success){
                task_queue->addFinishedTask(task);
            }
            else if (task->attempts() >= 3){
                    qDebug()<<"Failed with that task"<<task->uid();
                    emit error("Task executing failed", task->uid());
                    emit task_failed(task);
                }
            else{
                task->attempts_inc();
                task_queue->addNewTask(task);
            }
        }
        QThread::msleep(100);
    }
}

bool DataBaseWorker::init_or_create_db(QString path)
{
    if (!create_db_file(path)){
        return false;
    }
    sdb.setDatabaseName(filename);
    if (!sdb.open()){
        qDebug()<<"Can't open db file!"<<sdb.lastError();
        return false;
    }
    bool res = execQuery("SELECT * FROM Mgmt_data");
    if (res){

    }
    else {
        return false;
    }

    if (res){
        sdb.close();
    }
    else if (!execQuery("CREATE TABLE `Income` ( `id` INTEGER, `date` TEXT, `time` TEXT, `source` INTEGER, `amount` INTEGER )")){
        return false;
    }
    else if (!execQuery("CREATE TABLE `Mgmt_data` ( `LastUpdate` TEXT, `FormatVersion` INTEGER )")){
        return false;
    }
    else if (!execQuery("CREATE TABLE `Outcome` ( `uid` INTEGER, `date` TEXT, `time` TEXT, `reason` INTEGER, `amount` INTEGER )")){
        return false;
    }

    QString req = QString::asprintf("INSERT INTO `Mgmt_data`(`LastUpdate`,`FormatVersion`) VALUES (%s,%i)",
                                    QDateTime::currentDateTime().date().toString("yyyy-MM-dd").toStdString().c_str(),
                                    (int)DB_FORMAT_VERSION);
    if (!execQuery(req)){
        return false;
    }

    sdb.close();

    return true;
}

bool DataBaseWorker::create_db_file(QString path)
{
    QFile file(path);
    if (!file.exists()){
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
            qDebug()<<__FUNCTION__<<"Unable create file"<<file.errorString();
            return false;
        }
        file.close();
    }
    return true;
}

int DataBaseWorker::saveNewOperation(const Operation* op) {
    QString request = QString::asprintf("INSERT INTO %s (date,time,%s,amount) VALUES ('%s','%s',%u,%.2f);",
                                        (op->dir == Operation::income) ? ("Income") : ("Outcome"),
                                        (op->dir == Operation::income) ? ("source") : ("reason"),
                                        op->date_time.date().toString("yyyy-MM-dd").toStdString().c_str(),
                                        op->date_time.time().toString("HH:mm:ss").toStdString().c_str(),
                                        (op->dir == Operation::income) ? (0) : (op->typeIndex()),
                                        op->amount );

    if (!execQuery(request))
        return -1;

    return 0;
}

int DataBaseWorker::readTask(ReadDataTask* task) {
    QString request = QString::asprintf("SELECT * FROM Income WHERE date BETWEEN \'%s\' AND \'%s\'",
                                    task->dt_from().date().toString("yyyy-MM-dd").toStdString().c_str(),
                                    task->dt_to().date().toString("yyyy-MM-dd").toStdString().c_str());
    if (!execQuery(request))
        return -1;

    int idx_date = query.record().indexOf("date");
    int idx_time = query.record().indexOf("time");
    int idx_amount = query.record().indexOf("amount");

    while(query.next()){
        Operation op;
        op.date_time.setDate(QDate::fromString(query.value(idx_date).toString(), "yyyy-MM-dd"));
        op.date_time.setTime(QTime::fromString(query.value(idx_time).toString(), "HH:mm:ss"));
        op.dir = Operation::income;
        op.type = "";
        op.amount = query.value(idx_amount).toFloat();
        task->addOperation(op);
    }

    request = QString::asprintf("SELECT * FROM Outcome WHERE date BETWEEN \'%s\' AND \'%s\'",
                                        task->dt_from().date().toString("yyyy-MM-dd").toStdString().c_str(),
                                        task->dt_to().date().toString("yyyy-MM-dd").toStdString().c_str());
    if (!execQuery(request))
        return -1;

    int idx_reason = query.record().indexOf("reason");
    idx_date = query.record().indexOf("date");
    idx_time = query.record().indexOf("time");
    idx_amount = query.record().indexOf("amount");
    while(query.next()){
        Operation op;
        op.date_time.setDate(QDate::fromString(query.value(idx_date).toString(), "yyyy-MM-dd"));
        op.date_time.setTime(QTime::fromString(query.value(idx_time).toString(), "HH:mm:ss"));
        op.dir = Operation::outcome;
        op.type = Operation::index2type(query.value(idx_reason).toUInt());
        op.amount = query.value(idx_amount).toFloat();
        task->addOperation(op);
    }
    return 0;
}

bool DataBaseWorker::execQuery(QString req)
{
    if (!query.exec(req)){
        qDebug()<<__FUNCTION__<<req << "FAILED";
        emit error(query.lastError().text(), (int)query.lastError().type());
        return false;
    }
    qDebug()<<__FUNCTION__<<req << "SUCCESS";
    return true;
}

bool DataBaseWorker::isDone() const
{
    auto dispatcher = QThread::currentThread()->eventDispatcher();
    if (!dispatcher) return false;
    dispatcher->processEvents(QEventLoop::AllEvents);
    return m_done;
}

QStringList DataBaseWorker::getTableList()
{
    QStringList list;
    list << income_table_name << outcome_table_name;
    return list;
}

void DataBaseWorker::setDone(bool done)
{
    m_done = done;
}

void DataBaseWorker::process_task()
{
    if (task_queue->hasTasks()){
        Task* task = task_queue->takeTask();
        if (task != nullptr){
            if (task->taskType() == Task::task_write){
                SaveDataTask* s_task = (SaveDataTask*)task;
                task->setStatus((this->saveNewOperation(s_task->operation()) == 0) ?
                                   (SaveDataTask::status_success) :
                                   (SaveDataTask::status_failure));
            }
            else if (task->taskType() == Task::task_read){
                task->setStatus((this->readTask(((ReadDataTask*)task)) == 0) ?
                                   (SaveDataTask::status_success) :
                                   (SaveDataTask::status_failure));
            }
        }

        if (task->status() == Task::status_success){
            task_queue->addFinishedTask(task);
        }
        else if (task->attempts() >= 3){
            // TODO some block for exclude infinity loop
                qDebug()<<"Failed with that task"<<task->uid();
                emit error("Task executing failed", task->uid());
            }
        else{
            task->attempts_inc();
            task_queue->addNewTask(task);
        }
    }
}
