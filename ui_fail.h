/********************************************************************************
** Form generated from reading UI file 'fail.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAIL_H
#define UI_FAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Fail
{
public:
    QDialogButtonBox *buttonBox;
    QTextEdit *fail_message;

    void setupUi(QDialog *Fail)
    {
        if (Fail->objectName().isEmpty())
            Fail->setObjectName("Fail");
        Fail->resize(400, 300);
        buttonBox = new QDialogButtonBox(Fail);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        fail_message = new QTextEdit(Fail);
        fail_message->setObjectName("fail_message");
        fail_message->setGeometry(QRect(100, 90, 200, 70));

        retranslateUi(Fail);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Fail, qOverload<>(&QDialog::reject));
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Fail, qOverload<>(&QDialog::accept));

        QMetaObject::connectSlotsByName(Fail);
    } // setupUi

    void retranslateUi(QDialog *Fail)
    {
        Fail->setWindowTitle(QCoreApplication::translate("Fail", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Fail: public Ui_Fail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAIL_H
