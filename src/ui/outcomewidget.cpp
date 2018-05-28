#include "outcomewidget.h"

OutcomeWidget::OutcomeWidget(QWidget *parent)
    : WidgetForStack(parent)
{
    //Отложить
    radioList.push_back(new QRadioButton("Отложить", this));
    radioList.push_back(new QRadioButton("Развлечения", this));
    radioList.push_back(new QRadioButton("Помощь", this));
    radioList.push_back(new QRadioButton("Квартплата", this));
    radioList.push_back(new QRadioButton("Кредиты", this));
    radioList.push_back(new QRadioButton("Еда", this));
    radioList.push_back(new QRadioButton("Транспорт", this));
    radioList.at(0)->setChecked(true);
    btnBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    lay = new QVBoxLayout(this);
    foreach(QRadioButton* btn, radioList){
        lay->addWidget(btn);
    }
    lay->addSpacerItem(new QSpacerItem(20, 70));
    lay->addWidget(btnBox);
    connect(btnBox, &QDialogButtonBox::accepted, this, &OutcomeWidget::onOk);
    connect(btnBox, &QDialogButtonBox::rejected, this, &OutcomeWidget::onCancel);
}

OutcomeWidget::~OutcomeWidget()
{
    delete lay;
    delete btnBox;
    while(!radioList.isEmpty()) delete radioList.takeLast();
}

void OutcomeWidget::onOk()
{
    this->m_operation.dir = Operation::outcome;
    foreach(QRadioButton* btn, radioList){
        if (btn->isChecked()){
            this->m_operation.type = btn->text();
            break;
        }
    }
    emit goNext();
}

void OutcomeWidget::onCancel()
{
    this->m_operation.type = "";
    emit goHome();
}
