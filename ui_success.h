/********************************************************************************
** Form generated from reading UI file 'success.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUCCESS_H
#define UI_SUCCESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Success
{
public:
    QDialogButtonBox *buttonBox;
    QTextEdit *textEdit;

    void setupUi(QDialog *Success)
    {
        if (Success->objectName().isEmpty())
            Success->setObjectName("Success");
        Success->resize(400, 300);
        buttonBox = new QDialogButtonBox(Success);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        textEdit = new QTextEdit(Success);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(100, 90, 200, 70));

        retranslateUi(Success);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Success, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Success, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Success);
    } // setupUi

    void retranslateUi(QDialog *Success)
    {
        Success->setWindowTitle(QCoreApplication::translate("Success", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Success: public Ui_Success {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUCCESS_H
