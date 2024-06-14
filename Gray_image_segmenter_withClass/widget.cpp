#include "widget.h"
#include "ui_widget.h"
#include"Algo.h"
#include<QMessageBox>
#include<QtConcurrent/QtConcurrent>
#include<QFileDialog>
#include<iostream>
#include"saveFunctions.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->valueInput_horizontalSlider,SIGNAL(sliderReleased()),this,SLOT(on_run_pushButton_clicked()));

    //ui美化
    ui->Image_display_label_1->setStyleSheet("border:2px solid rgb(0,0,0);;border-radius:10px;padding:2px 4px;");
    ui->Image_display_label_2->setStyleSheet("border:2px solid rgb(0,0,0);;border-radius:10px;padding:2px 4px;");
    ui->Image_display_label_3->setStyleSheet("border:2px solid rgb(0,0,0);;border-radius:10px;padding:2px 4px;");
    ui->state_showing_label->setStyleSheet("border:1px solid rgb(0,0,0);;border-radius:3px;padding:2px 4px;");
    // 设置按钮样式及悬浮、按下时的状态
    ui->run_pushButton->setStyleSheet("QPushButton{color: white;background-color: rgb(25, 117, 197);border:2px groove gray;border-radius:5px;padding:2px 4px;border-style: outset;}"
        "QPushButton:hover{background-color:rgb(41, 116, 195); color: black;}"
        "QPushButton:pressed{background-color:rgb(50, 150, 200);border-style: inset;}");
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
    int num1=num;
    if(num>=30)
    {
        ui->valueInput_horizontalSlider->setValue(30);
        num=num1;
        ui->valueInput_lineEdit->setText(temp);
    }
    else
    {
        ui->valueInput_horizontalSlider->setValue(num);
    }
}

//执行算法按钮
void Widget::on_run_pushButton_clicked()
{
    if(imagePath1.isNull())
    {
       QMessageBox::warning(nullptr, "warning", "未导入图片");
        return;
    }

    /*ui->Image_display_label_2->clear();
    ui->Image_display_label_3->clear();*/

    QFont f("YaHei",11);
    ui->state_showing_label->setFont(f);

    //通过强制刷新界面解决setText一句被挂起的问题，
    show();
    qApp->processEvents();
    ui->state_showing_label->setText("运行状态：正在执行算法，请稍等");
    show();
    qApp->processEvents();

    QString temp=ui->valueInput_lineEdit->text();
    num=temp.toInt();
    int Epsilon=num;
    Algo rnam(imagePath1,op,Epsilon);
    rnam.beGray();//转灰度图
    rnam.beSquare();//进行缩放
    rnam.run();//执行算法
    ui->state_showing_label->setText("算法执行成功！");

    m1=MatToQPixmap(rnam.get_img1());
    m2=MatToQPixmap(rnam.get_img2());
    ui->Image_display_label_2->setPixmap(m1);//压缩图
    ui->Image_display_label_2->setScaledContents(true);
    ui->Image_display_label_3->setPixmap(m2);//分割图
    ui->Image_display_label_3->setScaledContents(true);

    QString tem;
    tem="编码压缩花费：";
    tem+=QString::number(rnam.get_time1());
    tem+="ms";
    ui->dataShowing_lineEdit_1->setText(tem);
    tem.clear();

    tem="还原图像耗时：";
    tem+=QString::number(rnam.get_time2());
    tem+="ms";
    ui->dataShowing_lineEdit_2->setText(tem);
    tem.clear();

    tem="块数：";
    tem+=QString::number(rnam.get_nums());
    ui->dataShowing_lineEdit_3->setText(tem);
    tem.clear();

    tem="PSNR值：";
    tem+=QString::number(rnam.get_psnr());
    ui->dataShowing_lineEdit_4->setText(tem);
    tem.clear();

    tem="BPP值：";
    tem+=QString::number(rnam.get_bpp());
    ui->dataShowing_lineEdit_5->setText(tem);
    tem.clear();

    tem="CR值：";
    tem+=QString::number(rnam.get_cr());
    ui->dataShowing_lineEdit_6->setText(tem);
    tem.clear();

    //把为显示而压缩为正方形的图片恢复为原来的尺寸
    QPixmap original(imagePath1);
    m1= OriginalSize(m1,original.width(),original.height());
    m2= OriginalSize(m2,original.width(),original.height());

    //以下是debug语句书写处
}



void Widget::on_loadButton_clicked()
{
    //定义QString变量imagePath1来接收图片的地址，这个地址是由用户自己上传的。请注意imagePath1是在头文件中已经声明的。
    imagePath1 = QFileDialog::getOpenFileName(this, "选择图片", "", "图片文件 (*.jpg *.jpeg *.png *.bmp)");
    if (!imagePath1.isEmpty()) {
        QPixmap originalPixmap(imagePath1);
        ui->Image_display_label_1->setPixmap(originalPixmap);
        ui->Image_display_label_1->setScaledContents(true);        //在Image_display_label_1中显示，并且通过setScaledContents函数使其尺寸自适应
    }
}


void Widget::on_saveButton_1_clicked()
{
    QString dir=QFileDialog::getSaveFileName(this,tr("保存图片"),"",tr("Images (*.jpg *.jpeg *.png *.bmp)"));
    m1.save(dir);
}


void Widget::on_saveButton_2_clicked()
{
    QString dir=QFileDialog::getSaveFileName(this,tr("保存图片"),"",tr("Images (*.jpg *.jpeg *.png *.bmp)"));
    m2.save(dir);
}


void Widget::on_clearButton_clicked()
{
    ui->Image_display_label_1->clear();
    ui->Image_display_label_2->clear();
    ui->Image_display_label_3->clear();
    ui->dataShowing_lineEdit_1->setText("解码压缩花费：");
    ui->dataShowing_lineEdit_2->setText("还原图像耗时：");
    ui->dataShowing_lineEdit_3->setText("块数：");
    ui->dataShowing_lineEdit_4->setText("PSNR值：");
    ui->dataShowing_lineEdit_5->setText("BPP值：");
    ui->dataShowing_lineEdit_6->setText("CR值：");
    num=0;
    m1 = QPixmap();
    m2 = QPixmap();
    imagePath1.clear();
}


void Widget::on_comboBox_activated(int index)
{
    op=index;
}

