#ifndef SAVEDDATAWORKER_H
#define SAVEDDATAWORKER_H

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QDate>
#include <QFile>
#include "datacollector.h"

// сделать динамическую типизацию платежей, после чтения из файла, для поиска, сортировок и пр.
// нужен ещё один класс для работы с прочитанной "базой". А то упячка, а не класс получиться.
class SavedDataWorker
{
    static const QString fileFormat;
public:
    SavedDataWorker();
    static QString getFileFormat();
    static bool saveNewEntry(const QJsonObject &input);
    static bool loadSavedEntries(DataCollector &collector, const QString& date_from = "", const QString &date_to = "");

};

#endif // SAVEDDATAWORKER_H
