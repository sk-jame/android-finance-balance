#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QDate>
#include <QJsonObject>


class Operation {
private:
    int         m_type_index;
public:
    enum EDirection{
        income,
        outcome
    };

    EDirection  dir;
    QString     type;
    QString     comment;
    qreal       amount;
    QDateTime   date_time;

    Operation() :
        dir(income),
        type(""),
        comment(""),
        amount(0),
        date_time(QDateTime::currentDateTime())
        {}

    QJsonObject toJSON(bool with_date = true){
        QJsonObject obj;
        obj["direction"] = (dir==income)?"income":"outcome";
        obj["type"] = type;
        obj["amount"] = amount;
        obj["comment"] = comment;

        if (with_date)
            obj["date"] = QDate::currentDate().toString("dd.MM.yyyy");

        return obj;
    }

    Operation(const QJsonObject& json) :
        dir((json["direction"].toString() == "income") ? (income) : (outcome)),
        type(json["type"].toString()),
        comment(json["comment"].toString()),
        amount(json["amount"].toString().toFloat()),
        date_time(QDateTime::fromString(json["date_time"].toString(), "dd.MM.yyyy HH:mm:ss"))
    {}


    int typeIndex() const {
        QStringList tmpList;
        tmpList.push_back("Отложить");
        tmpList.push_back("Развлечения");
        tmpList.push_back("Помощь");
        tmpList.push_back("Квартплата");
        tmpList.push_back("Кредиты");
        tmpList.push_back("Еда");
        tmpList.push_back("Транспорт");
        return tmpList.indexOf(type);
    }

    static QString index2type(int idx){
        QStringList tmpList;
        tmpList.push_back("Отложить");
        tmpList.push_back("Развлечения");
        tmpList.push_back("Помощь");
        tmpList.push_back("Квартплата");
        tmpList.push_back("Кредиты");
        tmpList.push_back("Еда");
        tmpList.push_back("Транспорт");
        return tmpList.at(idx);
    }
};

#endif // OPERATIONS_H
