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

    enum Reasons{
        reason_food,
        reason_entertainment,
        reason_charity,
        reason_saveMoney,
        reason_apartment,
        reason_credits,
        reason_transport,
        reason_last
    };

    EDirection  dir;
    QString     reason;
    QString     comment;
    qreal       amount;
    QDateTime   date_time;

    Operation() :
        dir(income),
        reason(""),
        comment(""),
        amount(0),
        date_time(QDateTime::currentDateTime())
    {}

    Operation(Operation& another) :
        dir(another.dir),
        reason(another.reason),
        comment(another.comment),
        amount(another.amount),
        date_time(another.date_time)
    {}

    Operation(const Operation& another) :
        dir(another.dir),
        reason(another.reason),
        comment(another.comment),
        amount(another.amount),
        date_time(another.date_time)
    {}

    QJsonObject toJSON(bool with_date = true){
        QJsonObject obj;
        obj["direction"] = (dir==income)?"income":"outcome";
        obj["type"] = reason;
        obj["amount"] = amount;
        obj["comment"] = comment;

        if (with_date)
            obj["date"] = QDate::currentDate().toString("dd.MM.yyyy");

        return obj;
    }

    Operation(const QJsonObject& json) :
        dir((json["direction"].toString() == "income") ? (income) : (outcome)),
        reason(json["type"].toString()),
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
            tmpList.push_back("Отложить");
            tmpList.push_back("Квартплата");
            tmpList.push_back("Кредиты");
            tmpList.push_back("Транспорт");
        }
        return tmpList;
    }

    int reasonIndex() const {
        return getReasonsNames().indexOf(reason);
    }

    const QString direction_name() {
        return (dir == income)? ("Income") : ("Outcome");
    }
};

#endif // OPERATIONS_H
