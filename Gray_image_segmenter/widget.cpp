#include "widget.h"
#include "ui_widget.h"
#include"segment_functions.h"
#include<QMessageBox>
#include<QtConcurrent/QtConcurrent>
#include<QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
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
    if(scaledPixmap.isNull())
    {
       QMessageBox::warning(nullptr, "warning", "未导入图片");
        return;
    }


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
    Mat img1,img2;
    int time1,time2,nums;
    double psnr,bpp,cr;
    Mat mat=QPixmapToMat(scaledPixmap);

    fun(Epsilon,mat,time1,time2,nums,psnr,bpp,cr,img1,img2);

    m1=MatToQPixmap(img1);
    m2=MatToQPixmap(img2);

    ui->state_showing_label->setFont(f);
    ui->state_showing_label->setText("运行状态：算法执行成功!");

    ui->Image_display_label_2->setPixmap(m1);
    ui->Image_display_label_2->setScaledContents(true);
    ui->Image_display_label_3->setPixmap(m2);
    ui->Image_display_label_3->setScaledContents(true);

    QString tem;
    tem="编码压缩花费：";
    tem+=QString::number(time1);
    tem+="ms";
    ui->dataShowing_lineEdit_1->setText(tem);
    tem.clear();

    tem="还原图像耗时：";
    tem+=QString::number(time2);
    tem+="ms";
    ui->dataShowing_lineEdit_2->setText(tem);
    tem.clear();

    tem="块数：";
    tem+=QString::number(nums);
    ui->dataShowing_lineEdit_3->setText(tem);
    tem.clear();

    tem="PSNR值：";
    tem+=QString::number(psnr);
    ui->dataShowing_lineEdit_4->setText(tem);
    tem.clear();

    tem="BPP值：";
    tem+=QString::number(bpp);
    ui->dataShowing_lineEdit_5->setText(tem);
    tem.clear();

    tem="CR值：";
    tem+=QString::number(bpp);
    ui->dataShowing_lineEdit_6->setText(tem);
    tem.clear();
}



void Widget::on_loadButton_clicked()
{
    //定义QString变量imagePath1来接收图片的地址，这个地址是由用户自己上传的。请注意imagePath1是在头文件中已经声明的。
    imagePath1 = QFileDialog::getOpenFileName(this, "选择图片", "", "图片文件 (*.jpg *.jpeg *.png *.bmp)");
    if (!imagePath1.isEmpty()) {
        QPixmap originalPixmap(imagePath1);
        ui->Image_display_label_1->setPixmap(originalPixmap);
        ui->Image_display_label_1->setScaledContents(true);        //在Image_display_label_1中显示，并且通过setScaledContents函数使其尺寸自适应
        int targetSize=300;
        scaledPixmap=originalPixmap.scaled(targetSize,targetSize,Qt::KeepAspectRatio);
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
    scaledPixmap=QPixmap();
    imagePath1.clear();
}


void Widget::on_comboBox_activated(int index)
{
    op=index;
}

