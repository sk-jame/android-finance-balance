#include <QMessageBox>
#include <QDebug>
#include "saveddataworker.h"
#include <QSqlQuery>

/* constants */
//const QString SavedDataWorker::filename = ":/db/.balance.sqlite";
const QString SavedDataWorker::filename = "../.balance.sqlite";

/* function implementation */
SavedDataWorker::SavedDataWorker(TaskQueue *task_queue, QObject *parent)
    : QObject(parent),
      sdb(QSqlDatabase::addDatabase("QSQLITE")),
      query(sdb),
      m_done(false),
      m_thread(nullptr)
{
    this->task_queue = (task_queue);
    sdb.setDatabaseName(filename);
//    sdb.setUserName("Alex");
//    sdb.setPassword("9379992");
    if (!sdb.open()){
        qDebug() << sdb.lastError();
        return;
    }
}

SavedDataWorker::~SavedDataWorker()
{
    m_done = false;
    if (m_thread != nullptr){
        m_thread->quit();
        m_thread->wait();
        delete m_thread;
    }

    sdb.close();
}

QString SavedDataWorker::getFilename()
{
    return filename;
}

void SavedDataWorker::start()
{
    if (m_thread != nullptr){
        // already started
        return;
    }

    m_thread = new QThread;
    QObject::connect(m_thread, &QThread::started, this, &SavedDataWorker::process);
    this->moveToThread(m_thread);
    m_thread->start();
}

void SavedDataWorker::process()
{
    while(!isDone()){
        if (task_queue->hasTasks()){
            Task* task = task_queue->takeTask();
            if (task != nullptr){
                if (task->taskType() == Task::task_write){
                    SaveDataTask* s_task = (SaveDataTask*)task;
                    task->setStatus((saveNewOperation(&s_task->operation()) == 0) ?
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
            else{
                // TODO some block for exclude infinity loop
                task_queue->addNewTask(task);
            }
        }
        QThread::sleep(1);
    }
}

int SavedDataWorker::saveNewOperation(Operation* op) {
    QString request = QString::asprintf("INSERT INTO %s (date,time,%s,amount) VALUES ('%s','%s',%u,%.2f);",
                                        (op->dir == Operation::income) ? ("Income") : ("Outcome"),
                                        (op->dir == Operation::income) ? ("source") : ("reason"),
                                        op->date_time.date().toString("yyyy-MM-dd").toStdString().c_str(),
                                        op->date_time.time().toString("HH:mm:ss").toStdString().c_str(),
                                        (op->dir == Operation::income) ? (0) : (op->typeIndex()),
                                        op->amount );

    if (!query.exec(request)){
        emit error(query.lastError().text(), (int)query.lastError().type());
        return -1;
    }
    return 0;
}

int SavedDataWorker::readTask(ReadDataTask* task) {
    QString request = QString::asprintf("SELECT * FROM Income WHERE date BETWEEN %s AND %s",
                                    task->dt_from().date().toString("yyyy-MM-dd").toStdString().c_str(),
                                    task->dt_to().date().toString("yyyy-MM-dd").toStdString().c_str());
    if (!query.exec(request)){
        emit error(query.lastError().text(), (int)query.lastError().type());
        return -1;
    }
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

    request = QString::asprintf("SELECT * FROM Outcome WHERE date BETWEEN %s AND %s",
                                        task->dt_from().date().toString("dd.MM.yyyy").toStdString().c_str(),
                                        task->dt_to().date().toString("dd.MM.yyyy").toStdString().c_str());
    if (!query.exec(request)){
        emit error(query.lastError().text(), (int)query.lastError().type());
        return -1;
    }

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

bool SavedDataWorker::isDone() const
{
    return m_done;
}

void SavedDataWorker::setDone(bool done)
{
    m_done = done;
}

bool SavedDataWorker::saveToJson(const QJsonObject& input, QString format)
{

    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("balance.sqlite");

    if (!sdb.open()) {
        QMessageBox::critical(nullptr, "Не могу открыть файл для сохранения", "Херь какая-то, не получается открыть файл для дозаписи в него(или создать)");
        return false;
    }

    QJsonDocument doc;
    QJsonArray j_arr;

    QFile file(QDate::currentDate().toString("MM_yyyy") + format);

    if (file.exists()){
        if (!file.open(QIODevice::ReadOnly)){
            // TODO сделать какую-нибудь обработку ошибки. Хотя я вообще х3 что делать)
        }
        QByteArray array = file.readAll();
        file.close();
        doc = QJsonDocument::fromJson(array);
        j_arr = doc.array();
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QMessageBox::critical(nullptr, "Не могу открыть файл для сохранения", "Херь какая-то, не получается открыть файл для дозаписи в него(или создать)");
        return false;
    }

    j_arr.append(input);
    QJsonDocument newdoc(j_arr);
    qDebug()<<j_arr;
    file.write(newdoc.toJson());
    file.close();
    return true;
}
