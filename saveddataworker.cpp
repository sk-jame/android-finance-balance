#include <QMessageBox>
#include <QDebug>
#include "saveddataworker.h"

const QString SavedDataWorker::fileFormat = ".json";

QString SavedDataWorker::getFileFormat()
{
    return fileFormat;
}

bool SavedDataWorker::saveNewEntry(const QJsonObject& input)
{
    QJsonDocument doc;
    QJsonArray j_arr;

    QFile file(QDate::currentDate().toString("MM_yyyy") + fileFormat);

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

bool SavedDataWorker::loadSavedEntries(DataCollector &collector, const QString &date_from, const QString &date_to)
{
    QJsonDocument doc;
    if (date_from == "" && date_to == ""){
        // read all files
    }
    return true;
}

SavedDataWorker::SavedDataWorker()
{

}
