#include "incomepage.h"
#include "ui_incomepage.h"

IncomePage::IncomePage(QWidget *parent) :
    WidgetForStack(parent),
    ui(new Ui::IncomePage)
{
    ui->setupUi(this);
    setLayout(ui->verticalLayout);
    connect(ui->pbCredit, &QPushButton::clicked, this, &IncomePage::onPushButtonClicked);
    connect(ui->pbSalary, &QPushButton::clicked, this, &IncomePage::onPushButtonClicked);
    connect(ui->pbSaved, &QPushButton::clicked, this, &IncomePage::onPushButtonClicked);
}

IncomePage::~IncomePage()
{
    delete ui;
}

int IncomePage::selection() const
{
    return m_selection;
}

void IncomePage::setSelection(int selection)
{
    if (m_selection == selection)
        return;

    m_selection = selection;
    emit selectionChanged(m_selection);
}

void IncomePage::onPushButtonClicked()
{
    if (sender() == ui->pbCredit){
        setSelection(select_credit);
    }
    else if (sender() == ui->pbSaved){
        setSelection(select_saved);
    }
    else if (sender() == ui->pbSalary){
        setSelection(select_salary);
    }
    emit goNext();
}
