#include "stackwidget.h"
#include <QKeyEvent>
#include <QDebug>

bool StackWidget::canContinue() const
{
    return m_canContinue;
}

void StackWidget::setCanContinue(bool canContinue)
{
    m_canContinue = canContinue;
}

void StackWidget::operation_error(QString error, int code)
{
    qDebug()<<error<<code;
}

StackWidget::StackWidget(QWidget *parent)
    : QStackedWidget(parent)
{

}

