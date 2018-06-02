/********************************************************************************
** Form generated from reading UI file 'reasonwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REASONWIDGET_H
#define UI_REASONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReasonWidget
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *lay_RadioBtns;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *ReasonWidget)
    {
        if (ReasonWidget->objectName().isEmpty())
            ReasonWidget->setObjectName(QStringLiteral("ReasonWidget"));
        ReasonWidget->resize(400, 300);
        verticalLayoutWidget = new QWidget(ReasonWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 381, 281));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        groupBox = new QGroupBox(verticalLayoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayoutWidget_2 = new QWidget(groupBox);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 10, 371, 181));
        lay_RadioBtns = new QVBoxLayout(verticalLayoutWidget_2);
        lay_RadioBtns->setObjectName(QStringLiteral("lay_RadioBtns"));
        lay_RadioBtns->setContentsMargins(5, 5, 5, 5);

        verticalLayout->addWidget(groupBox);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ReasonWidget);

        QMetaObject::connectSlotsByName(ReasonWidget);
    } // setupUi

    void retranslateUi(QWidget *ReasonWidget)
    {
        ReasonWidget->setWindowTitle(QApplication::translate("ReasonWidget", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("ReasonWidget", "\320\237\321\200\320\270\321\207\320\270\320\275\320\260 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\320\270", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ReasonWidget: public Ui_ReasonWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REASONWIDGET_H
