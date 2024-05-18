#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_valueInput_horizontalSlider_valueChanged(int value);

    void on_valueInput_lineEdit_returnPressed();

    void on_run_pushButton_clicked();

    void on_loadButton_clicked();

private:
    Ui::Widget *ui;
    int num = 0;//用于存储epsilon值输入框中的值
    QString imagePath1;
    QPixmap m1;//灰度图
    QPixmap m2;//分割图
};
#endif // WIDGET_H
