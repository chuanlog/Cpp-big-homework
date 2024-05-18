/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *Image_display_label_1;
    QLabel *Image_display_label_2;
    QLabel *Image_display_label_3;
    QPushButton *saveButton_1;
    QPushButton *saveButton_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QLineEdit *dataShowing_lineEdit_1;
    QLineEdit *dataShowing_lineEdit_2;
    QLineEdit *dataShowing_lineEdit_3;
    QLineEdit *dataShowing_lineEdit_4;
    QLineEdit *dataShowing_lineEdit_5;
    QLineEdit *dataShowing_lineEdit_6;
    QPushButton *loadButton;
    QSlider *valueInput_horizontalSlider;
    QPushButton *run_pushButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *valueInput_lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *clearButton;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(1200, 600);
        Widget->setMinimumSize(QSize(1200, 600));
        Widget->setMaximumSize(QSize(1200, 600));
        QFont font;
        font.setPointSize(10);
        Widget->setFont(font);
        Widget->setMouseTracking(false);
        layoutWidget1 = new QWidget(Widget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(0, 30, 931, 302));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Image_display_label_1 = new QLabel(layoutWidget1);
        Image_display_label_1->setObjectName("Image_display_label_1");
        Image_display_label_1->setMinimumSize(QSize(300, 300));
        Image_display_label_1->setMaximumSize(QSize(300, 300));
        Image_display_label_1->setStyleSheet(QString::fromUtf8("border:1px solid rgb(0,0,0);"));

        horizontalLayout->addWidget(Image_display_label_1);

        Image_display_label_2 = new QLabel(layoutWidget1);
        Image_display_label_2->setObjectName("Image_display_label_2");
        Image_display_label_2->setMinimumSize(QSize(300, 300));
        Image_display_label_2->setMaximumSize(QSize(300, 300));
        Image_display_label_2->setStyleSheet(QString::fromUtf8("border:1px solid rgb(0,0,0);"));

        horizontalLayout->addWidget(Image_display_label_2);

        Image_display_label_3 = new QLabel(layoutWidget1);
        Image_display_label_3->setObjectName("Image_display_label_3");
        Image_display_label_3->setMinimumSize(QSize(300, 300));
        Image_display_label_3->setMaximumSize(QSize(300, 300));
        Image_display_label_3->setStyleSheet(QString::fromUtf8("border:1px solid rgb(0,0,0);"));

        horizontalLayout->addWidget(Image_display_label_3);

        saveButton_1 = new QPushButton(Widget);
        saveButton_1->setObjectName("saveButton_1");
        saveButton_1->setGeometry(QRect(420, 340, 80, 30));
        saveButton_1->setMinimumSize(QSize(80, 30));
        saveButton_1->setMaximumSize(QSize(80, 30));
        saveButton_2 = new QPushButton(Widget);
        saveButton_2->setObjectName("saveButton_2");
        saveButton_2->setGeometry(QRect(750, 340, 80, 30));
        saveButton_2->setMinimumSize(QSize(80, 30));
        saveButton_2->setMaximumSize(QSize(80, 30));
        layoutWidget2 = new QWidget(Widget);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(950, 30, 221, 301));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        dataShowing_lineEdit_1 = new QLineEdit(layoutWidget2);
        dataShowing_lineEdit_1->setObjectName("dataShowing_lineEdit_1");
        dataShowing_lineEdit_1->setMinimumSize(QSize(0, 40));
        dataShowing_lineEdit_1->setMaximumSize(QSize(16777215, 40));
        dataShowing_lineEdit_1->setFocusPolicy(Qt::NoFocus);
        dataShowing_lineEdit_1->setStyleSheet(QString::fromUtf8("font: 10pt \"Microsoft YaHei UI\";"));

        verticalLayout->addWidget(dataShowing_lineEdit_1);

        dataShowing_lineEdit_2 = new QLineEdit(layoutWidget2);
        dataShowing_lineEdit_2->setObjectName("dataShowing_lineEdit_2");
        dataShowing_lineEdit_2->setMinimumSize(QSize(0, 40));
        dataShowing_lineEdit_2->setMaximumSize(QSize(16777215, 40));
        dataShowing_lineEdit_2->setFocusPolicy(Qt::NoFocus);
        dataShowing_lineEdit_2->setStyleSheet(QString::fromUtf8("font: 10pt \"Microsoft YaHei UI\";"));

        verticalLayout->addWidget(dataShowing_lineEdit_2);

        dataShowing_lineEdit_3 = new QLineEdit(layoutWidget2);
        dataShowing_lineEdit_3->setObjectName("dataShowing_lineEdit_3");
        dataShowing_lineEdit_3->setMinimumSize(QSize(0, 40));
        dataShowing_lineEdit_3->setMaximumSize(QSize(16777215, 40));
        dataShowing_lineEdit_3->setFocusPolicy(Qt::NoFocus);
        dataShowing_lineEdit_3->setStyleSheet(QString::fromUtf8("font: 10pt \"Microsoft YaHei UI\";"));

        verticalLayout->addWidget(dataShowing_lineEdit_3);

        dataShowing_lineEdit_4 = new QLineEdit(layoutWidget2);
        dataShowing_lineEdit_4->setObjectName("dataShowing_lineEdit_4");
        dataShowing_lineEdit_4->setMinimumSize(QSize(0, 40));
        dataShowing_lineEdit_4->setMaximumSize(QSize(16777215, 40));
        dataShowing_lineEdit_4->setFocusPolicy(Qt::NoFocus);
        dataShowing_lineEdit_4->setStyleSheet(QString::fromUtf8("font: 10pt \"Microsoft YaHei UI\";"));

        verticalLayout->addWidget(dataShowing_lineEdit_4);

        dataShowing_lineEdit_5 = new QLineEdit(layoutWidget2);
        dataShowing_lineEdit_5->setObjectName("dataShowing_lineEdit_5");
        dataShowing_lineEdit_5->setMinimumSize(QSize(0, 40));
        dataShowing_lineEdit_5->setMaximumSize(QSize(16777215, 40));
        dataShowing_lineEdit_5->setFocusPolicy(Qt::NoFocus);
        dataShowing_lineEdit_5->setStyleSheet(QString::fromUtf8("font: 10pt \"Microsoft YaHei UI\";"));

        verticalLayout->addWidget(dataShowing_lineEdit_5);

        dataShowing_lineEdit_6 = new QLineEdit(layoutWidget2);
        dataShowing_lineEdit_6->setObjectName("dataShowing_lineEdit_6");
        dataShowing_lineEdit_6->setMinimumSize(QSize(0, 40));
        dataShowing_lineEdit_6->setMaximumSize(QSize(16777215, 40));
        dataShowing_lineEdit_6->setFocusPolicy(Qt::NoFocus);
        dataShowing_lineEdit_6->setStyleSheet(QString::fromUtf8("font: 10pt \"Microsoft YaHei UI\";"));

        verticalLayout->addWidget(dataShowing_lineEdit_6);

        loadButton = new QPushButton(Widget);
        loadButton->setObjectName("loadButton");
        loadButton->setGeometry(QRect(100, 340, 80, 31));
        loadButton->setMinimumSize(QSize(80, 31));
        loadButton->setMaximumSize(QSize(80, 30));
        valueInput_horizontalSlider = new QSlider(Widget);
        valueInput_horizontalSlider->setObjectName("valueInput_horizontalSlider");
        valueInput_horizontalSlider->setEnabled(true);
        valueInput_horizontalSlider->setGeometry(QRect(290, 410, 621, 21));
        valueInput_horizontalSlider->setMaximum(30);
        valueInput_horizontalSlider->setPageStep(1);
        valueInput_horizontalSlider->setOrientation(Qt::Horizontal);
        run_pushButton = new QPushButton(Widget);
        run_pushButton->setObjectName("run_pushButton");
        run_pushButton->setGeometry(QRect(490, 520, 201, 41));
        run_pushButton->setStyleSheet(QString::fromUtf8("font: 12pt \"Microsoft YaHei UI\";"));
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(50, 390, 221, 131));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(0, 3));

        horizontalLayout_3->addWidget(label_2);

        valueInput_lineEdit = new QLineEdit(layoutWidget);
        valueInput_lineEdit->setObjectName("valueInput_lineEdit");
        valueInput_lineEdit->setMinimumSize(QSize(100, 30));
        valueInput_lineEdit->setMaximumSize(QSize(100, 30));

        horizontalLayout_3->addWidget(valueInput_lineEdit);

        horizontalLayout_3->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        label->setMinimumSize(QSize(0, 30));

        horizontalLayout_2->addWidget(label);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName("comboBox");
        comboBox->setMinimumSize(QSize(101, 31));
        comboBox->setMaximumSize(QSize(100, 30));

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        clearButton = new QPushButton(Widget);
        clearButton->setObjectName("clearButton");
        clearButton->setGeometry(QRect(1010, 340, 80, 30));
        clearButton->setMinimumSize(QSize(80, 30));
        clearButton->setMaximumSize(QSize(80, 30));
        label_3 = new QLabel(Widget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 10, 31, 16));
        label_4 = new QLabel(Widget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(430, 10, 51, 20));
        label_5 = new QLabel(Widget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(750, 10, 51, 20));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\347\201\260\345\272\246\345\233\276\345\203\217\345\210\206\345\211\262\345\231\250", nullptr));
        Image_display_label_1->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        Image_display_label_2->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        Image_display_label_3->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        saveButton_1->setText(QCoreApplication::translate("Widget", "\344\277\235\345\255\230", nullptr));
        saveButton_2->setText(QCoreApplication::translate("Widget", "\344\277\235\345\255\230", nullptr));
        dataShowing_lineEdit_1->setText(QCoreApplication::translate("Widget", "\347\274\226\347\240\201\345\216\213\347\274\251\350\212\261\350\264\271\357\274\232", nullptr));
        dataShowing_lineEdit_2->setText(QCoreApplication::translate("Widget", "\350\277\230\345\216\237\345\233\276\345\203\217\350\200\227\346\227\266\357\274\232", nullptr));
        dataShowing_lineEdit_3->setText(QCoreApplication::translate("Widget", "\345\235\227\346\225\260\357\274\232", nullptr));
        dataShowing_lineEdit_4->setText(QCoreApplication::translate("Widget", "PSNR\345\200\274\357\274\232", nullptr));
        dataShowing_lineEdit_5->setText(QCoreApplication::translate("Widget", "BPP\345\200\274\357\274\232", nullptr));
        dataShowing_lineEdit_6->setText(QCoreApplication::translate("Widget", "CR\345\200\274\357\274\232", nullptr));
        loadButton->setText(QCoreApplication::translate("Widget", "\345\212\240\350\275\275", nullptr));
        run_pushButton->setText(QCoreApplication::translate("Widget", "\346\211\247      \350\241\214      \347\256\227      \346\263\225", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">\350\276\223\345\205\245epsilon\345\200\274\357\274\232</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("Widget", "<html><head/><body><p><span style=\" font-weight:700;\">\351\200\211\346\213\251\344\275\240\347\232\204\347\256\227\346\263\225\357\274\232</span></p></body></html>", nullptr));
        clearButton->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">\345\216\237\345\233\276</p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">\345\210\206\345\211\262\345\233\276</p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\">\345\216\213\347\274\251\345\233\276</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
