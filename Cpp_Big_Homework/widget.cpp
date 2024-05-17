#include "widget.h"
#include "ui_widget.h"
#include<opencv2/opencv.hpp>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_valueInput_horizontalSlider_valueChanged(int value)
{
    QString change=QString::number(value);
    ui->valueInput_lineEdit->setText(change);
}


void Widget::on_valueInput_lineEdit_returnPressed()
{
    QString temp=ui->valueInput_lineEdit->text();
    num=temp.toInt();
    if(num>=30)
    {
        ui->valueInput_horizontalSlider->setValue(30);
    }
    else
    {
        ui->valueInput_horizontalSlider->setValue(num);
    }
}

