#include "reasonwidget.h"
#include "ui_reasonwidget.h"
#ifndef TEST
#include "common/operations.h"
#endif

ReasonWidget::ReasonWidget(QWidget *parent) :
    WidgetForStack(parent),
    ui(new Ui::ReasonWidget)
{
    ui->setupUi(this);
#ifdef TEST
    QStringList names = QStringList();
    names.push_back("Еда");
    names.push_back("Развлечения");
    names.push_back("Помощь");
    names.push_back("На будущее");
    names.push_back("Квартира");
    names.push_back("Кредиты / Долги");
    names.push_back("Транспорт");
    names.push_back("Техника");
#else
    QStringList names = Operation::getReasonsNames();
#endif
    foreach (QString name, names) {
        QRadioButton* rb = new QRadioButton(name, this);
        radioList << rb;
        ui->lay_RadioBtns->addWidget(rb);
    }
    setLayout(ui->verticalLayout);
    ui->groupBox->setLayout(ui->lay_RadioBtns);
    radioList.first()->setChecked(true);
}

ReasonWidget::~ReasonWidget()
{
    delete ui;
}
