#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QDate>
#include <QJsonObject>


class Operation {
private:
    int         m_type_index;
public:
    enum Type{
        type_invalid = -1,
        type_income = 0,
        type_outcome,
        type_last
    };

    enum Reasons{
        reason_doesnt_matter = -2,       /* https://www.youtube.com/watch?v=tAGnKpE4NCI */
        reason_invalid = -1,
        reason_food = 0,
        reason_entertainment,
        reason_charity,
        reason_saveMoney,
        reason_apartment,
        reason_credits,
        reason_transport,
        reason_technics,
        reason_last                         /* carefull with Operation::getReasonsNames */
    };

    Type  type;
    QString     reason;
    QString     comment;
    qreal       amount;
    QDateTime   date_time;

    Operation() :
        type(type_income),
        reason(""),
        comment(""),
        amount(0),
        date_time(QDateTime::currentDateTime())
    {}

    Operation(Operation& another) :
        type(another.type),
        reason(another.reason),
        comment(another.comment),
        amount(another.amount),
        date_time(another.date_time)
    {}

    Operation(const Operation& another) :
        type(another.type),
        reason(another.reason),
        comment(another.comment),
        amount(another.amount),
        date_time(another.date_time)
    {}

    QJsonObject toJSON(bool with_date = true){
        QJsonObject obj;
        obj["direction"] = (type==type_income)?"income":"outcome";
        obj["type"] = reason;
        obj["amount"] = amount;
        obj["comment"] = comment;

        if (with_date)
            obj["date"] = QDate::currentDate().toString("dd.MM.yyyy");

        return obj;
    }

    Operation(const QJsonObject& json) :
        type((json["type"].toString() == "income") ? (type_income) : (type_outcome)),
        reason(json["reason"].toString()),
        comment(json["comment"].toString()),
        amount(json["amount"].toString().toFloat()),
        date_time(QDateTime::fromString(json["date_time"].toString(), "dd.MM.yyyy HH:mm:ss"))
    {}

    static const QStringList getReasonsNames() {
        static QStringList tmpList = QStringList();
        if (tmpList.isEmpty()){
            tmpList.push_back("Еда");
            tmpList.push_back("Развлечения");
            tmpList.push_back("Помощь");
            tmpList.push_back("На будущее");
            tmpList.push_back("Квартира");
            tmpList.push_back("Кредиты / Долги");
            tmpList.push_back("Транспорт");
            tmpList.push_back("Техника");
        }
        return tmpList;
    }

    int reasonIndex() const {
        return getReasonsNames().indexOf(reason);
    }

    const QString direction_name() {
        return (type == type_income)? ("Income") : ("Outcome");
    }
};

#endif // OPERATIONS_H
