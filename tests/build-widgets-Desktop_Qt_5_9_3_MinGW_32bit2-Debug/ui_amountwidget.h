/********************************************************************************
** Form generated from reading UI file 'amountwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AMOUNTWIDGET_H
#define UI_AMOUNTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AmountWidget
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *leAmount;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLineEdit *leComment;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *AmountWidget)
    {
        if (AmountWidget->objectName().isEmpty())
            AmountWidget->setObjectName(QStringLiteral("AmountWidget"));
        AmountWidget->resize(400, 300);
        widget = new QWidget(AmountWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(11, 10, 371, 281));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        leAmount = new QLineEdit(widget);
        leAmount->setObjectName(QStringLiteral("leAmount"));
        leAmount->setClearButtonEnabled(true);

        horizontalLayout->addWidget(leAmount);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        leComment = new QLineEdit(widget);
        leComment->setObjectName(QStringLiteral("leComment"));

        verticalLayout->addWidget(leComment);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AmountWidget);

        QMetaObject::connectSlotsByName(AmountWidget);
    } // setupUi

    void retranslateUi(QWidget *AmountWidget)
    {
        AmountWidget->setWindowTitle(QApplication::translate("AmountWidget", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("AmountWidget", "\320\241\321\203\320\274\320\274\320\260:", Q_NULLPTR));
        label_2->setText(QApplication::translate("AmountWidget", "\320\232\320\276\320\274\320\274\320\265\320\275\321\202\320\260\321\200\320\270\320\271:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AmountWidget: public Ui_AmountWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AMOUNTWIDGET_H
