#include "amountwidget.h"
#include "data/task.h"
#include "ui_amountwidget.h"
#include <QMessageBox>
#include <QDebug>

AmountWidget::AmountWidget(QString _text, QWidget *parent) :
    WidgetForStack(parent),
    ui(new Ui::AmountWidget)
{
    ui->setupUi(this);
    connect(this, &AmountWidget::textChanged, ui->label, &QLabel::setText);
    setText(_text);
}

AmountWidget::~AmountWidget()
{
    delete ui;
}

QString AmountWidget::text() const
{
    return m_text;
}

qreal AmountWidget::amount() const
{
    return m_amount;
}

QString AmountWidget::comment() const
{
    return m_comment;
}

void AmountWidget::setText(QString text)
{
    if (m_text == text)
        return;

    m_text = text;
    emit textChanged(m_text);
}

void AmountWidget::setComment(QString comment)
{
    if (m_comment == comment)
        return;

    m_comment = comment;
    emit commentChanged(m_comment);
}

void AmountWidget::setAmount(qreal amount)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_amount, amount))
        return;

    m_amount = amount;
    emit amountChanged(m_amount);
}

void AmountWidget::on_buttonBox_accepted()
{
    bool ok;
    qreal value = ui->leAmount->text().toFloat(&ok);
    if (!ok){
        QMessageBox::critical(this, "Херь в сумме", "Сумму в число не получается перевести");
        return;
    }

    setAmount(value);
    setComment(ui->leComment->text());
    emit goNext();
}

void AmountWidget::on_buttonBox_rejected()
{
    emit goBack();
}
