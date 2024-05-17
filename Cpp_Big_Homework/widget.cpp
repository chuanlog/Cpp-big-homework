#include "widget.h"
#include "ui_widget.h"
#include<QMessageBox>
#include<opencv2/opencv.hpp>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //链接slider上鼠标释放的信号和执行算法按键的槽函数，使slider的值改变一次，就计算一次
    connect(ui->valueInput_horizontalSlider,SIGNAL(sliderReleased()),this,SLOT(on_run_pushButton_clicked()));
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



void Widget::on_run_pushButton_clicked()
{
    QMessageBox::information(this, "Information", "测试功能 coding by clog");
}

