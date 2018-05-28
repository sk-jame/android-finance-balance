#include <QMessageBox>
#include <QDebug>
#include "saveddataworker.h"
#include <QSqlQuery>

/* constants */
const QString SavedDataWorker::filename = ":/db/.balance.sqlite";

/* function implementation */
SavedDataWorker::SavedDataWorker(QObject *parent)
    : QObject(parent),
      sdb(QSqlDatabase::addDatabase("QSQLITE")),
      query(sdb)
{
    sdb.setDatabaseName(filename);
    sdb.setUserName("Alex");
    sdb.setPassword("9379992");
    if (!sdb.open()){
        qDebug() << sdb.lastError();
        return;
    }
}

SavedDataWorker::~SavedDataWorker()
{
    sdb.close();
}

QString SavedDataWorker::getFilename()
{
    return filename;
}

void SavedDataWorker::saveNewOperation(const Operation& op) {
    QString request = QString::asprintf("INSERT INTO `%s` (`date`,`time`,`source`, `amount`) VALUES ('%s','%s',%u,%i);",
                                        (op.dir == Operation::income) ? ("Income") : ("Outcome"),
                                        op.date_time.date().toString("dd.MM.yyyy").toStdString().c_str(),
                                        op.date_time.time().toString("HH:mm:ss").toStdString().c_str(),
                                        op.type,
                                        op.amount);

    if (!query.exec(request)){
        emit error(query.lastError(), query.lastError().type());
    }


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
