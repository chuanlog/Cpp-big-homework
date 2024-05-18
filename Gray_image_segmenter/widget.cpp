#include "widget.h"
#include "ui_widget.h"
#include"Header_Diagonal_Priority.h"
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
    QMessageBox::information(this,"information","test coding by 陈永川");
}
//这是Diagonal_Priority算法的函数，传入参数为，epsilon值、原图地址值以及编解码时间，块数，PSNR，BPP,CR值的引用
void fun(int epsilon, string address, int& time1, int& time2, int& num, double& psnr, double& bpp, double& cr, Mat& img1, Mat& img2)
{
    Mat img = imread(address);
    if (!img.empty()) {
        /*一，分割同类块及编码*/
        int M = img.rows;
        int N = img.cols;

        Mat img_gray = img;
        cvtColor(img, img_gray, CV_BGR2GRAY);
        Mat markMatrix = Mat::zeros(M, N, CV_8UC1);
        Mat R = Mat::zeros(M, N, CV_8UC1);

        vector<Color> colorList;
        vector<char> coordinateList;
        int xigema = epsilon;
        MyTimer mt;
        mt.Start();
        /*分块*/
        RNAMCEncoding(img_gray, R, markMatrix, M, N, colorList, coordinateList, xigema);

        /*矩阵编码*/
        EnCode(R, M, N, coordinateList);
        mt.End();

        time1 = mt.costTime;
        mt.Reset();

        /*二，还原图像矩阵及图像*/
        Mat T = Mat::zeros(M, N, CV_8UC1);

        mt.Start();
        Decode(T, M, N, coordinateList);
        RNAMCDecoding(T, M, N, colorList, coordinateList);
        mt.End();
        time2 = mt.costTime;
        mt.Reset();

        num = colorList.size();
        psnr = PSNR(img_gray, T, M, N);
        bpp = BPP(colorList, M, N, coordinateList);
        cr = 8.0 / bpp;

        img1 = T;

        /*分割图*/
        Mat display(M, N, CV_8UC1, Scalar::all(255));
        segmentDisplay(display, colorList);
        img2 = display;
        img.release();
        img_gray.release();
        display.release();
        T.release();
    }
}




void Widget::on_loadButton_clicked()
{
    //声明QString变量imagePath来接收图片的地址，这个地址是由用户自己上传的
    QString imagePath = QFileDialog::getOpenFileName(this, "选择图片", "", "图片文件 (*.jpg *.jpeg *.png)");
    if (!imagePath.isEmpty()) {
        QPixmap pixmap(imagePath);
        ui->Image_display_label_1->setPixmap(pixmap);
        ui->Image_display_label_1->setScaledContents(true);        //在Image_display_label_1中显示，并且通过setScaledContents函数使其尺寸自适应
    }
}

