#ifndef AMOUNTWIDGET_H
#define AMOUNTWIDGET_H

#include "widgetforstack.h"

namespace Ui {
class AmountWidget;
}

class AmountWidget : public WidgetForStack
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(qreal amount READ amount NOTIFY amountChanged)
    Q_PROPERTY(QString comment READ comment NOTIFY commentChanged)
public:
    explicit AmountWidget(QString _text, QWidget *parent = 0);
    ~AmountWidget();
    QString text() const;
    qreal amount() const;
    QString comment() const;
public slots:
    void setText(QString text);
signals:
    void notify(QString str);
    void textChanged(QString text);
    void amountChanged(qreal amount);
    void commentChanged(QString comment);
protected slots:
    void setComment(QString comment);
    void setAmount(qreal amount);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
private:
    Ui::AmountWidget *ui;
    QString m_text;
    qreal m_amount;
    QString m_comment;
};

#endif // AMOUNTWIDGET_H
