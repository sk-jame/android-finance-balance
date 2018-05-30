#ifndef SAVEDDATAWORKER_H
#define SAVEDDATAWORKER_H

#include "task.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QDate>
#include <QFile>
#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include "operations.h"

class DataBaseWorker : public QObject
{
    Q_OBJECT
    QSqlDatabase sdb;
    QSqlQuery query;
    TaskQueue* task_queue;
    volatile bool m_done;

    QThread m_thread;
    /**
     * @brief m_good
     * Show was init ok or not.
     */
    bool m_good;
    void process();
    bool init_or_create_db(QString path);
    bool create_db_file(QString path);
public:
    static const QString filename, income_table_name, outcome_table_name;
    DataBaseWorker(TaskQueue* task_queue, QObject* parent = Q_NULLPTR);
    virtual ~DataBaseWorker();
    static QString getFilename();
    void start();
    bool stop(bool terminate = false);

    static bool saveToJson(const QJsonObject &input, QString format);
    bool isDone() const;

    static QStringList getTableList();
    bool isGood() const;

signals:
    void error(QString text, int code = -1);
    void task_failed(Task*);
public slots:
    void setDone(bool done = true);
    void process_task();
    int saveNewOperation(const Operation *op);
    int readTask(ReadDataTask *task);
private:
    bool execQuery(QString req);
};

#endif // SAVEDDATAWORKER_H
