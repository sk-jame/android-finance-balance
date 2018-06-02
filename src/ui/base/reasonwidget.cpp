#include "reasonwidget.h"
#include "ui_reasonwidget.h"
#ifndef TEST
#include "common/operations.h"
#endif

ReasonWidget::ReasonWidget(QStringList _names, QWidget *parent) :
    WidgetForStack(parent),
    ui(new Ui::ReasonWidget),
    m_names(_names)
{
    ui->setupUi(this);
    foreach (QString name, m_names) {
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

QStringList ReasonWidget::names() const
{
    return m_names;
}

int ReasonWidget::checkedIndex() const
{
    return m_checkedIndex;
}

void ReasonWidget::setCheckedIndex(int checkedIndex)
{
    if (m_checkedIndex == checkedIndex)
        return;

    m_checkedIndex = checkedIndex;
    emit checkedIndexChanged(m_checkedIndex);
}

void ReasonWidget::on_buttonBox_accepted()
{
    for(int i = 0; i < radioList.count(); i++)
        if (radioList.at(i)->isChecked()){
            setCheckedIndex(i);
            break;
        }
    goNext();
}

void ReasonWidget::on_buttonBox_rejected()
{
    emit goBack();
}
