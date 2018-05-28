#include <QDebug>
#include <QMessageBox>
#include "incomewidget.h"
#include "data/saveddataworker.h"

IncomeWidget::IncomeWidget(QWidget* parent) : WidgetForStack(parent),
        labelAmount(new QLabel("Введите сумму", this)),
        labelComment(new QLabel("Введите комментарий к операции", this)),
        leAmount(new QLineEdit(this)),
        leComment(new QLineEdit(this)),
        cbFromSaved(new QCheckBox("Забрать эти деньги из отложенных\nв активный баланс",this)),
        btnBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this)),
        lay(new QVBoxLayout(this))
{
    lay->addWidget(labelAmount);
    lay->addWidget(leAmount);
    lay->addWidget(cbFromSaved);
    lay->addWidget(labelComment);
    lay->addWidget(leComment);
    lay->addSpacerItem(new QSpacerItem(400, 100));
    lay->addWidget(btnBox);

    connect(btnBox, &QDialogButtonBox::accepted, this, &IncomeWidget::onOk);
    connect(btnBox, &QDialogButtonBox::rejected, this, &IncomeWidget::onCancel);
}

IncomeWidget::~IncomeWidget()
{
    delete labelAmount;
    delete labelComment;
    delete leAmount;
    delete leComment;
    delete btnBox;
    delete lay;
}

void IncomeWidget::onOk()
{
    bool ok;
    this->m_operation.amount = leAmount->text().toFloat(&ok);
    if (!ok){
        QMessageBox::critical(this, "Херь в сумме", "Сумму в число не получается перевести из строки в число");
        return;
    }
    this->m_operation.type.clear();
    this->m_operation.dir = Operation::income;
    this->m_operation.comment = leComment->text();
//    qDebug() << SavedDataWorker::saveNewEntry(this->m_operation.toJSON());

    if (cbFromSaved->isChecked()){
        this->m_operation.type = "Отложить";
        this->m_operation.dir = Operation::outcome;
        this->m_operation.comment = leComment->text();
        this->m_operation.amount = this->m_operation.amount * -1;
//        qDebug() << SavedDataWorker::saveNewEntry(this->m_operation.toJSON());
    }

    // TODO save to db
    emit goHome();
}

void IncomeWidget::onCancel()
{
    emit goHome();
}
