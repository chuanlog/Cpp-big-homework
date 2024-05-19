#ifndef SEGMENT_FUNCTIONS_H
#define SEGMENT_FUNCTIONS_H
#include<QImage>
#include<QPixmap>
#include<Header_Diagonal_Priority.h>

//这是Diagonal_Priority算法的函数，传入参数为，epsilon值、原图地址值以及编解码时间，块数，PSNR，BPP,CR值的引用
void fun(int epsilon, Mat mat, int& time1, int& time2, int& num, double& psnr, double& bpp, double& cr, Mat& img1, Mat& img2)
{
    Mat img = mat;
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
//以下两个函数用于将Mat转化为QPixmap
//将Mat转化为QImage
QImage MatToQImage(const cv::Mat& mat)
{
    if (mat.type() == CV_8UC1)
    { // 灰度图像
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
        return image.copy();
    } else if (mat.type() == CV_8UC3)
    { // 彩色图像
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped(); // BGR 转 RGB
    } else
    {
        qWarning("Unsupported cv::Mat format!");
        return QImage();
    }
}
// 将 QImage 转换为 QPixmap
QPixmap MatToQPixmap(const cv::Mat& mat)
{
    return QPixmap::fromImage(MatToQImage(mat));
}


//以下函数用于将QPixmap转为Mat
Mat QPixmapToMat(QPixmap qpixmap)
{
    QImage qimage=qpixmap.toImage();
    cv::Mat mat;
    switch(qimage.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC4, (void*)qimage.constBits(), qimage.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC3, (void*)qimage.constBits(), qimage.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC1, (void*)qimage.constBits(), qimage.bytesPerLine());
        break;
    }
    return mat;
}



#endif // SEGMENT_FUNCTIONS_H
