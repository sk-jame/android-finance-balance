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

class SavedDataWorker : public QObject
{
    Q_OBJECT
    static const QString filename;
    QSqlDatabase sdb;
    QSqlQuery query;
    TaskQueue* task_queue;
    bool m_done;

    QThread* m_thread;

    void process();
public:
    SavedDataWorker(TaskQueue* task_queue, QObject* parent = Q_NULLPTR);
    virtual ~SavedDataWorker();
    static QString getFilename();
    void start();

    static bool saveToJson(const QJsonObject &input, QString format);
    bool isDone() const;
    void setDone(bool done);

signals:
    void error(QString text, int code = -1);
//    void finished()
public slots:
    int saveNewOperation(Operation *op);
    int readTask(ReadDataTask *task);
};

#endif // SAVEDDATAWORKER_H
