#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QDate>
#include <QJsonObject>


class Operation {
public:

    typedef int Reasons;

    enum Type{
        type_invalid = -1,
        type_income = 0,
        type_outcome,
        type_last
    };

    enum {
        reason_doesnt_matter = -2,       /* https://www.youtube.com/watch?v=tAGnKpE4NCI */
        reason_invalid = -1
    };


    QString     comment;
    Reasons     reason;
    qreal       amount;
    QDateTime   date_time;

    Operation() :
        comment(""),
        reason(reason_invalid),
        amount(0),
        date_time(QDateTime::currentDateTime())
    {}

    Operation(Operation& another) :
        comment(another.comment),
        reason(another.reason),
        amount(another.amount),
        date_time(another.date_time)
    {}

    Operation(const Operation& another) :
        comment(another.comment),
        reason(another.reason),
        amount(another.amount),
        date_time(another.date_time)
    {}

    virtual ~Operation() {

    }

    virtual void fromJSON(const QJsonObject& json){
        comment = (json["comment"].toString());
        reason = (json["reason"].toInt());
        amount = (json["amount"].toString().toFloat());
        date_time = (QDateTime::fromString(json["date_time"].toString(), "yyyy.MM.dd HH:mm:ss"));
    }

    virtual QJsonObject toJSON(bool with_date = true){
        QJsonObject obj;
        obj["amount"] = amount;
        obj["comment"] = comment;
        obj["reason"] = reason;
        if (with_date)
            obj["date"] = QDate::currentDate().toString("dd.MM.yyyy");

        return obj;
    }

    virtual const QString direction_name() { return ""; }
    virtual Type type() const { return type_invalid; }
    virtual const QStringList getReasonsNames() { return QStringList(); }
    virtual QString reasonName() {
        if (getReasonsNames().isEmpty())
            return "";
        return getReasonsNames().at(reason);
    }
    virtual bool isValid() {return true;}
};

class OutcomeOperation : public Operation
{
public:
    enum {
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

    OutcomeOperation() :
        Operation()
    {

    }

    ~OutcomeOperation(){

    }

    const QStringList getReasonsNames() {
        QStringList tmpList = QStringList();
        tmpList.push_back("Еда");
        tmpList.push_back("Развлечения");
        tmpList.push_back("Помощь");
        tmpList.push_back("На будущее");
        tmpList.push_back("Квартира");
        tmpList.push_back("Кредиты / Долги");
        tmpList.push_back("Транспорт");
        tmpList.push_back("Техника");
        return tmpList;
    }
    // Operation interface
public:
    const QString direction_name(){
        return "Исходящие";
    }

    Type type() const {
        return type_outcome;
    }

};

class IncomeOperation : public Operation
{
public:
    enum {
        reason_salary = 0,
        reason_credits,
        reason_saved,
        reason_last                         /* carefull with Operation::getReasonsNames */
    };

    IncomeOperation() :
        Operation()
    {

    }

    ~IncomeOperation(){

    }

    const QStringList getReasonsNames() {
        static QStringList tmpList = QStringList();
        if (tmpList.isEmpty()){
            tmpList.push_back("Зарплата/подарок");
            tmpList.push_back("Кредит/Долг");
            tmpList.push_back("Из сохранённых");
        }
        return tmpList;
    }

    // Operation interface
public:
    const QString direction_name(){
        return "Входящие";
    }

    Type type() const {
        return type_income;
    }

};

#endif // OPERATIONS_H


