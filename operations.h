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
    Operation() :
        m_type_index(-1),
        dir(income),
        type(""),
        comment(""),
        amount(0)
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
        m_type_index(-1),
        dir((json["direction"].toString() == "income") ? (income) : (outcome)),
        type(json["type"].toString()),
        comment(json["comment"].toString()),
        amount(json["amount"].toString().toFloat())
    {}


    int typeIndex() {
        if (m_type_index != -1 || dir == income)
            return m_type_index;

        QStringList tmpList;
        tmpList.push_back("Отложить");
        tmpList.push_back("Развлечения");
        tmpList.push_back("Помощь");
        tmpList.push_back("Квартплата");
        tmpList.push_back("Кредиты");
        tmpList.push_back("Еда");
        tmpList.push_back("Транспорт");
        m_type_index = tmpList.indexOf(type);
        return m_type_index;
    }
};

#endif // OPERATIONS_H
