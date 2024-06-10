#ifndef IMAGELOAD_H
#define IMAGELOAD_H
#include<opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include<QString>
#include<QImage>
#include<QPixmap>
#include <windows.h>
using namespace cv;
using namespace std;
/*此类用于图像从外存中的读取，最终得到的是从内存中获取的原图的Mat形式*/

class ImageLoad
{
public:
    ImageLoad();
    ImageLoad(QString imagePath1);//用图的地址初始化类
    ImageLoad(Mat img);//用Mat初始化类
    ImageLoad(QPixmap img);//用QPixmap初始化该类
    void Load(Mat img);//用Mat改变类变量
    void Load(QPixmap img);//用QPixmap改变类变量
    friend Mat QPixmapToMat1(QPixmap qpixmap);//声明为友元函数，便于使用
    Mat get_original_mat(){return original_mat;}
protected:
    Mat original_mat;//最初的图
};

//以下函数用于将QPixmap转为Mat,是类的友元函数。
Mat QPixmapToMat(QPixmap qpixmap);

#endif // IMAGELOAD_H
