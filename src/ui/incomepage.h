#ifndef INCOMEPAGE_H
#define INCOMEPAGE_H

#include "base/widgetforstack.h"

namespace Ui {
class IncomePage;
}

class IncomePage : public WidgetForStack
{
    Q_OBJECT
    Q_PROPERTY(int selection READ selection WRITE setSelection NOTIFY selectionChanged)
public:
    enum {
        select_salary = 0,
        select_saved,
        select_credit
    };

    explicit IncomePage(QWidget *parent = 0);
    ~IncomePage();
    int selection() const;
public slots:
    void setSelection(int selection);
signals:
    void selectionChanged(int selection);
private slots:
    void onPushButtonClicked();
private:
    Ui::IncomePage *ui;
    int m_selection;
};

#endif // INCOMEPAGE_H
