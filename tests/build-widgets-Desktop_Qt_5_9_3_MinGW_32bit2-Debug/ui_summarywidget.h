/********************************************************************************
** Form generated from reading UI file 'summarywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUMMARYWIDGET_H
#define UI_SUMMARYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ui/base/databasetablewidget.h"

QT_BEGIN_NAMESPACE

class Ui_SummaryWidget
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    DatabaseTableWidget *tableWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QDateEdit *deFrom;
    QDateEdit *deTo;
    QVBoxLayout *verticalLayout;
    QRadioButton *rbTableSelect_Income;
    QRadioButton *rbTableSelect_outcome;
    QRadioButton *rbTableSelect_All;
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rbShowOperations;
    QRadioButton *rbShowBalanceDaily;
    QRadioButton *rbShowBalanceMonthly;
    QRadioButton *rbShowMonthlySum;
    QRadioButton *rbShowDailySum;
    QRadioButton *rbShowReasonSum;
    QSpacerItem *verticalSpacer;
    QCheckBox *cbShowFilteres;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *SummaryWidget)
    {
        if (SummaryWidget->objectName().isEmpty())
            SummaryWidget->setObjectName(QStringLiteral("SummaryWidget"));
        SummaryWidget->resize(1050, 993);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SummaryWidget->sizePolicy().hasHeightForWidth());
        SummaryWidget->setSizePolicy(sizePolicy);
        layoutWidget = new QWidget(SummaryWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 431, 851));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
        gridLayout->setContentsMargins(5, 5, 5, 5);
        tableWidget = new DatabaseTableWidget(layoutWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);

        gridLayout->addWidget(tableWidget, 7, 0, 1, 2);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 8, 1, 1, 1);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 8, 0, 1, 1);

        deFrom = new QDateEdit(layoutWidget);
        deFrom->setObjectName(QStringLiteral("deFrom"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(deFrom->sizePolicy().hasHeightForWidth());
        deFrom->setSizePolicy(sizePolicy1);
        deFrom->setCalendarPopup(true);

        gridLayout->addWidget(deFrom, 1, 0, 1, 1);

        deTo = new QDateEdit(layoutWidget);
        deTo->setObjectName(QStringLiteral("deTo"));
        sizePolicy1.setHeightForWidth(deTo->sizePolicy().hasHeightForWidth());
        deTo->setSizePolicy(sizePolicy1);
        deTo->setCalendarPopup(true);

        gridLayout->addWidget(deTo, 1, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        rbTableSelect_Income = new QRadioButton(layoutWidget);
        buttonGroup_2 = new QButtonGroup(SummaryWidget);
        buttonGroup_2->setObjectName(QStringLiteral("buttonGroup_2"));
        buttonGroup_2->addButton(rbTableSelect_Income);
        rbTableSelect_Income->setObjectName(QStringLiteral("rbTableSelect_Income"));
        rbTableSelect_Income->setChecked(false);

        verticalLayout->addWidget(rbTableSelect_Income);

        rbTableSelect_outcome = new QRadioButton(layoutWidget);
        buttonGroup_2->addButton(rbTableSelect_outcome);
        rbTableSelect_outcome->setObjectName(QStringLiteral("rbTableSelect_outcome"));

        verticalLayout->addWidget(rbTableSelect_outcome);

        rbTableSelect_All = new QRadioButton(layoutWidget);
        buttonGroup_2->addButton(rbTableSelect_All);
        rbTableSelect_All->setObjectName(QStringLiteral("rbTableSelect_All"));
        rbTableSelect_All->setChecked(true);

        verticalLayout->addWidget(rbTableSelect_All);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy3);

        verticalLayout->addWidget(lineEdit);

        verticalSpacer_2 = new QSpacerItem(20, 24, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);


        gridLayout->addLayout(verticalLayout, 2, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        rbShowOperations = new QRadioButton(layoutWidget);
        buttonGroup = new QButtonGroup(SummaryWidget);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(rbShowOperations);
        rbShowOperations->setObjectName(QStringLiteral("rbShowOperations"));
        rbShowOperations->setChecked(true);

        verticalLayout_2->addWidget(rbShowOperations);

        rbShowBalanceDaily = new QRadioButton(layoutWidget);
        buttonGroup->addButton(rbShowBalanceDaily);
        rbShowBalanceDaily->setObjectName(QStringLiteral("rbShowBalanceDaily"));

        verticalLayout_2->addWidget(rbShowBalanceDaily);

        rbShowBalanceMonthly = new QRadioButton(layoutWidget);
        buttonGroup->addButton(rbShowBalanceMonthly);
        rbShowBalanceMonthly->setObjectName(QStringLiteral("rbShowBalanceMonthly"));

        verticalLayout_2->addWidget(rbShowBalanceMonthly);

        rbShowMonthlySum = new QRadioButton(layoutWidget);
        buttonGroup->addButton(rbShowMonthlySum);
        rbShowMonthlySum->setObjectName(QStringLiteral("rbShowMonthlySum"));

        verticalLayout_2->addWidget(rbShowMonthlySum);

        rbShowDailySum = new QRadioButton(layoutWidget);
        buttonGroup->addButton(rbShowDailySum);
        rbShowDailySum->setObjectName(QStringLiteral("rbShowDailySum"));

        verticalLayout_2->addWidget(rbShowDailySum);

        rbShowReasonSum = new QRadioButton(layoutWidget);
        buttonGroup->addButton(rbShowReasonSum);
        rbShowReasonSum->setObjectName(QStringLiteral("rbShowReasonSum"));

        verticalLayout_2->addWidget(rbShowReasonSum);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout_2, 2, 1, 1, 1);

        cbShowFilteres = new QCheckBox(layoutWidget);
        cbShowFilteres->setObjectName(QStringLiteral("cbShowFilteres"));

        gridLayout->addWidget(cbShowFilteres, 0, 0, 1, 2);

        deTo->raise();
        deFrom->raise();
        tableWidget->raise();
        pushButton->raise();
        pushButton_2->raise();
        cbShowFilteres->raise();
        QWidget::setTabOrder(cbShowFilteres, deFrom);
        QWidget::setTabOrder(deFrom, deTo);
        QWidget::setTabOrder(deTo, rbTableSelect_Income);
        QWidget::setTabOrder(rbTableSelect_Income, rbTableSelect_outcome);
        QWidget::setTabOrder(rbTableSelect_outcome, rbTableSelect_All);
        QWidget::setTabOrder(rbTableSelect_All, rbShowOperations);
        QWidget::setTabOrder(rbShowOperations, rbShowBalanceDaily);
        QWidget::setTabOrder(rbShowBalanceDaily, rbShowBalanceMonthly);
        QWidget::setTabOrder(rbShowBalanceMonthly, rbShowMonthlySum);
        QWidget::setTabOrder(rbShowMonthlySum, rbShowDailySum);
        QWidget::setTabOrder(rbShowDailySum, rbShowReasonSum);
        QWidget::setTabOrder(rbShowReasonSum, lineEdit);
        QWidget::setTabOrder(lineEdit, tableWidget);
        QWidget::setTabOrder(tableWidget, pushButton);
        QWidget::setTabOrder(pushButton, pushButton_2);

        retranslateUi(SummaryWidget);

        QMetaObject::connectSlotsByName(SummaryWidget);
    } // setupUi

    void retranslateUi(QWidget *SummaryWidget)
    {
        SummaryWidget->setWindowTitle(QApplication::translate("SummaryWidget", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SummaryWidget", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("SummaryWidget", "\320\235\320\260\320\267\320\260\320\264", Q_NULLPTR));
        rbTableSelect_Income->setText(QApplication::translate("SummaryWidget", "\320\222\321\205\320\276\320\264\321\217\321\211\320\270\320\265", Q_NULLPTR));
        rbTableSelect_outcome->setText(QApplication::translate("SummaryWidget", "\320\230\321\201\321\205\320\276\320\264\321\217\321\211\320\270\320\265", Q_NULLPTR));
        rbTableSelect_All->setText(QApplication::translate("SummaryWidget", "\320\222\321\201\320\265", Q_NULLPTR));
        label->setText(QApplication::translate("SummaryWidget", "\320\242\320\265\320\272\321\203\321\211\320\270\320\271 \321\204\320\270\320\273\321\214\321\202 (\320\277\320\276 \321\202\320\265\320\272\321\201\321\202\321\203)", Q_NULLPTR));
        rbShowOperations->setText(QApplication::translate("SummaryWidget", "\320\236\320\277\320\265\321\200\320\260\321\206\320\270\320\270", Q_NULLPTR));
        rbShowBalanceDaily->setText(QApplication::translate("SummaryWidget", "\320\221\320\260\320\273\320\260\320\275\321\201 \320\277\320\276 \320\264\320\275\321\217\320\274", Q_NULLPTR));
        rbShowBalanceMonthly->setText(QApplication::translate("SummaryWidget", "\320\221\320\260\320\273\320\260\320\275\321\201 \320\277\320\276 \320\274\320\265\321\201\321\217\321\206\320\260\320\274", Q_NULLPTR));
        rbShowMonthlySum->setText(QApplication::translate("SummaryWidget", "\320\241\321\203\320\274\320\274\320\260 \320\277\320\276 \320\274\320\265\321\201\321\217\321\206\320\260\320\274", Q_NULLPTR));
        rbShowDailySum->setText(QApplication::translate("SummaryWidget", "\320\241\321\203\320\274\320\274\320\260 \320\277\320\276 \320\264\320\275\321\217\320\274", Q_NULLPTR));
        rbShowReasonSum->setText(QApplication::translate("SummaryWidget", "\320\241\321\203\320\274\320\274\320\260 \320\277\320\276 \320\277\321\200\320\270\321\207\320\270\320\275\320\260\320\274", Q_NULLPTR));
        cbShowFilteres->setText(QApplication::translate("SummaryWidget", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\204\320\270\320\273\321\214\321\202\321\200\321\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SummaryWidget: public Ui_SummaryWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUMMARYWIDGET_H
