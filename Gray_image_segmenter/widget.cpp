#include "widget.h"
#include "ui_widget.h"
#include"segment_functions.h"
#include<QMessageBox>
#include<QFileDialog>

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

//执行算法按钮
void Widget::on_run_pushButton_clicked()
{
    QString temp=ui->valueInput_lineEdit->text();
    num=temp.toInt();
    int Epsilon=num;
    string adress=imagePath1.toStdString();
    Mat img1,img2;
    int time1,time2,num;
    double psnr,bpp,cr;
    fun(Epsilon,adress,time1,time2,num,psnr,bpp,cr,img1,img2);
    QPixmap m1,m2;
    m1=MatToQPixmap(img1);
    m2=MatToQPixmap(img2);
    ui->Image_display_label_2->setPixmap(m1);
    ui->Image_display_label_2->setScaledContents(true);
    ui->Image_display_label_3->setPixmap(m2);
    ui->Image_display_label_3->setScaledContents(true);
}



void Widget::on_loadButton_clicked()
{
    //声明QString变量imagePath来接收图片的地址，这个地址是由用户自己上传的
    imagePath1 = QFileDialog::getOpenFileName(this, "选择图片", "", "图片文件 (*.jpg *.jpeg *.png)");
    if (!imagePath1.isEmpty()) {
        QPixmap pixmap(imagePath1);
        ui->Image_display_label_1->setPixmap(pixmap);
        ui->Image_display_label_1->setScaledContents(true);        //在Image_display_label_1中显示，并且通过setScaledContents函数使其尺寸自适应
    }
}

