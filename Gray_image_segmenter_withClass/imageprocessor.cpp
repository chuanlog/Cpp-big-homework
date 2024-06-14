#include "imageprocessor.h"

ImageProcessor::ImageProcessor() {}

void ImageProcessor::beGray()
{
    cvtColor(original_mat, img_gray, CV_BGR2GRAY);
}

void ImageProcessor::beSquare()
{
    int width = img_gray.cols;
    int height = img_gray.rows;

    // 计算正方形的边长，取宽和高的较大值
    int side = max(width, height);
    M=side;
    N=side;
    // 缩放原图到正方形尺寸，忽略长宽比
    cv::resize(img_gray, square, cv::Size(side, side), 0, 0, cv::INTER_LINEAR);

}

QPixmap MatToQPixmap(const Mat &mat)
{
    QImage img;
    if (mat.type() == CV_8UC1)
    { // 灰度图像
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
        img=image;
    }
    else if (mat.type() == CV_8UC3)
    { // 彩色图像
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        img=image;
    }
    else if (mat.type() == CV_8UC4)
    { // 带透明度的彩色图像
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        img = image;
    }
    return QPixmap::fromImage(img);
}
