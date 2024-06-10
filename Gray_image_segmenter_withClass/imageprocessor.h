#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include<imageload.h>
#include<QMessagebox.h>
/*此类由ImageLoad类派生*/
class ImageProcessor: public ImageLoad//公有继承ImageLoad用于处理原始图的Mat,使其成为算法的输入
{
public:
    ImageProcessor();//默认构造函数
    ImageProcessor(QString imagepath):ImageLoad(imagepath){}//用图片路径参数初始化该类
    ImageProcessor(Mat img):ImageLoad(img)
    {}//用Mat初始化类
    ImageProcessor(QPixmap img):ImageLoad(img){}//用QPixmap初始化该类
    void beGray();//把原图转为灰色并存在img_gray中
    void beSquare();//把灰度图缩放为正方形并存在img_gray中
    Mat get_img_gray(){return img_gray;}
    Mat get_square(){return square;}
    friend QPixmap MatToQPixmap1(const cv::Mat& mat);
protected:
    Mat img_gray;//彩色图转成的灰度图
    Mat square;//被缩放为正方形的图，具体缩放方法见相关函数注释
    int M;//行数
    int N;//列数
};

// 将Mat转换为QPixmap，友元函数
QPixmap MatToQPixmap(const cv::Mat& mat);


#endif // IMAGEPROCESSOR_H
