#include "imageload.h"


ImageLoad::ImageLoad() {}

ImageLoad::ImageLoad(QString imagePath1)
{
    QPixmap original(imagePath1);//原图
    original_mat=QPixmapToMat(original);//原图转mat

}

ImageLoad::ImageLoad(Mat img)
{
    original_mat=img;
}

ImageLoad::ImageLoad(QPixmap img)
{
    original_mat=QPixmapToMat(img);//转为mat形式
}

void ImageLoad::Load(Mat img)
{
    original_mat=img;
}

void ImageLoad::Load(QPixmap img)
{
    original_mat=QPixmapToMat(img);//转为mat形式
}

Mat QPixmapToMat(QPixmap pixmap)
{
    QImage image = pixmap.toImage();

    if (image.format() != QImage::Format_RGB888)
        image = image.convertToFormat(QImage::Format_RGB888);

    cv::Mat mat(image.height(), image.width(), CV_8UC3, const_cast<uchar*>(image.bits()), image.bytesPerLine());

    return mat.clone();
}
