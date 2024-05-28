#ifndef SEGMENT_FUNCTIONS_H
#define SEGMENT_FUNCTIONS_H
#include<QImage>
#include<QPixmap>
#include<Header_Diagonal_Priority_Horizonal_Priority.h>
#include<QPainter>

//这是进行分割算法的函数，传入参数为，epsilon值、原图地址值以及编解码时间，块数，PSNR，BPP,CR值的引用以及使用的策略ways
void fun(int epsilon, Mat mat, int& time1, int& time2, int& num, double& psnr, double& bpp, double& cr, Mat& img1, Mat& img2,int ways)
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
        if(ways==0)
        {
           RNAMCEncoding_Diagonal_Priority(img_gray, R, markMatrix, M, N, colorList, coordinateList, xigema);
        }//用对角线优先策略
        else if(ways==1)
        {
            RNAMCEncoding_Horizonal_Priority(img_gray, R, markMatrix, M, N, colorList, coordinateList, xigema);
        }//用水平优先策略

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

//此函数用于将非正方形的Qpixmap转化为正方形的Qpixmap,转化后边长为原来较长的一边
QPixmap makeSquarePixmap(const QPixmap &srcPixmap) {
    // 获取长方形 QPixmap 的宽和高
    int width = srcPixmap.width();
    int height = srcPixmap.height();

    // 计算正方形的边长，取宽和高的较大值
    int side = max(width, height);

    // 将原始 QPixmap 缩放到正方形大小，保持长宽比
    QPixmap scaledPixmap = srcPixmap.scaled(side, side, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    return scaledPixmap;
}

//此函数用于恢复为原来的大小用于保存
QPixmap OriginalSize(const QPixmap &squarePixmap, int originalWidth, int originalHeight) {
    // 将正方形 QPixmap 缩放回原来的尺寸
    QPixmap restoredPixmap = squarePixmap.scaled(originalWidth, originalHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    return restoredPixmap;
}



#endif // SEGMENT_FUNCTIONS_H
