#ifndef SAVEFUNCTIONS_H
#define SAVEFUNCTIONS_H
#include<QPixmap>
/*用来保存的函数*/
//此函数用于恢复为原来的大小用于保存
QPixmap OriginalSize(const QPixmap &squarePixmap, int originalWidth, int originalHeight) {
    // 将正方形 QPixmap 缩放回原来的尺寸
    QPixmap restoredPixmap = squarePixmap.scaled(originalWidth, originalHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    return restoredPixmap;
}


#endif // SAVEFUNCTIONS_H
