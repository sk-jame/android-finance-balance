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
public:
    class DataBaseColumns {
    private:
        bool inited = false;
    public:
        int idx_uid;
        int idx_reason;
        int idx_date;
        int idx_time;
        int idx_amount;
        int idx_comment;
        QStringList column_names;

        DataBaseColumns()
        {
            idx_reason = idx_date =  idx_time = idx_amount = idx_uid = idx_comment = -1;
            column_names << "uid" << "date" << "time" << "reason" << "amount" << "comment";
            inited = false;
        }

        void init(QSqlQuery& query)
        {
            if (inited)
                return;

            idx_reason = query.record().indexOf("reason");
            idx_date = query.record().indexOf("date");
            idx_time = query.record().indexOf("time");
            idx_amount = query.record().indexOf("amount");
            idx_comment = query.record().indexOf("comment");
            inited = true;
        }

        bool isInited()
        {
            return inited;
        }

    };
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

    static const DataBaseColumns &db_columns();
protected:
    static DataBaseColumns m_db_columns;

signals:
    void error(QString text, int code = -1);
    void task_failed(Task*);
public slots:
    void setDone(bool done = true);
    void process_task();
    int saveNewOperation(const Operation *op);
    int readTask(ReadDataTask *task);
    void clearDataBase();
private:
    void process();
    bool init_or_create_db(QString path);
    bool create_db_file(QString path);
    bool execQuery(QString req);
};

#endif // SAVEDDATAWORKER_H
