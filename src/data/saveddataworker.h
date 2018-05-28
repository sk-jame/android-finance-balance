#ifndef SAVEDDATAWORKER_H
#define SAVEDDATAWORKER_H

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

class SavedDataWorker : QObject
{
    Q_OBJECT
    static const QString filename;
    QSqlDatabase sdb;
    QSqlQuery query;
public:
    SavedDataWorker(QObject* parent = Q_NULLPTR);
    virtual ~SavedDataWorker();
    static QString getFilename();


    static bool saveToJson(const QJsonObject &input, QString format);
signals:
    void error(QString text, int code = -1);
//    void finished()
public slots:
    void saveNewOperation(const Operation &op);
};

#endif // SAVEDDATAWORKER_H
