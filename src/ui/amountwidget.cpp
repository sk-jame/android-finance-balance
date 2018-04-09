#include <QDebug>
#include <QMessageBox>
#include "amountwidget.h"
#include "saveddataworker.h"

AmountWidget::AmountWidget(QWidget* parent) : WidgetForStack(parent),
        labelAmount(new QLabel("Введите сумму", this)),
        labelComment(new QLabel("Введите комментарий к операции", this)),
        leAmount(new QLineEdit(this)),
        leComment(new QLineEdit(this)),
        btnBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this)),
        spacer(new QSpacerItem(40, 75)),
        lay(new QVBoxLayout(this))
{
    lay->addWidget(labelAmount);
    lay->addWidget(leAmount);
    lay->addWidget(labelComment);
    lay->addWidget(leComment);
    lay->addSpacerItem(spacer);
    lay->addWidget(btnBox);

    connect(btnBox, &QDialogButtonBox::accepted, this, &AmountWidget::onOk);
    connect(btnBox, &QDialogButtonBox::rejected, this, &AmountWidget::onCancel);
}

AmountWidget::~AmountWidget()
{
    delete labelAmount;
    delete labelComment;
    delete leAmount;
    delete leComment;
    delete btnBox;
    delete lay;
}

void AmountWidget::onOk()
{
    bool ok;
    this->m_operation.amount = leAmount->text().toFloat(&ok);
    if (!ok){
        QMessageBox::critical(this, "Херь в сумме", "Сумму в число не получается перевести");
        return;
    }
    this->m_operation.comment = leComment->text();
    qDebug() << SavedDataWorker::saveNewEntry(this->m_operation.toJSON());
    emit goHome();
}

void AmountWidget::onCancel()
{
    emit goHome();
}
