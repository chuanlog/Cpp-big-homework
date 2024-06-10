#pragma once
#include<opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <windows.h>
using namespace cv;
using namespace std;
//颜色表类
class Color
{
    Point lt;
    Point rb;
    Scalar grey;
public:
    Color() { grey[0] = grey[1] = grey[2] = grey[3] = -1; }
    void setLt(Point lt) { this->lt = lt; }
    void setRb(Point rb) { this->rb = rb; }
    Point getLt() { return lt; }
    Point getRb() { return rb; }
    void setGrey(Scalar grey) { this->grey = grey; }
    Scalar getGrey() { return grey; }
};
