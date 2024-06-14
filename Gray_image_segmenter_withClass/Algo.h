#ifndef ALGO_H
#define ALGO_H
#include"imageprocessor.h"
#include<opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include"Color.h"
#include"MyTimer.h"
/*此类由ImageProcessor派生，用于实现算法*/
class Algo:public ImageProcessor
{
public:
    Algo();//默认构造函数
    Algo(QString imagePath1,int ways=0,int Eplison=10):ImageProcessor(imagePath1)
    {
        way=ways;
        epliosn=Eplison;
    }//用图片路径初始化该类
    Algo(Mat img,int ways=0,int Eplison=10):ImageProcessor(img)
    {
        way=ways;
        epliosn=Eplison;
    }//用Mat初始化该类
    Algo(QPixmap img,int ways=0,int Eplison=10):ImageProcessor(img)
    {
        way=ways;
        epliosn=Eplison;
    }//用QPixmap参数初始化该类
    /*以上是一些构造函数*/

    void run();//执行算法
    Mat get_img1(){return img1;}
    Mat get_img2(){return img2;}
    long get_time1(){return time1;}
    long get_time2(){return time2;}
    int get_nums(){return nums;}
    double get_psnr(){return psnr;}
    double get_bpp(){return bpp;}
    double get_cr(){return cr;}

protected:
    Mat markMatrix;//标记矩阵，用来标记那些地方处理过
    Mat R;//用于存储编码后的图像数据。
    Mat img1;//压缩图
    Mat img2;//分割图
    int epliosn;//epliosn值，用于决定不同块的指标
    long time1;//编码时间
    long time2;//解码时间
    int nums;//块数
    double psnr;//psnr(峰值信噪比)值
    double bpp;//bpp(每像素比特数)值
    double cr;//cr(压缩率)值
    int way;//分割策略（水平优先和对角线优先）
    vector<Color> colorList;//存储每个已经编码的区域的左上以及右下的坐标(p)
    vector<char> coordinateList;//表示压缩图片的字符数组(q)
private:
   friend bool isSameBlock(Mat f, Mat mark, Point lt, Point rb, int xgm);//使用改良isSameBlock阴影法判断是否同类块
   friend void mark(Mat &mark, Point lt, Point rb);//用于给处理过的区域做标记
   friend void EnCode(Mat &R,int height, int width, vector<char> &Q);//用于将编码后的图像转换成用压缩的字符串表示
   friend void Decode(Mat &R, int height, int width, const vector<char> &Q);//用于将压缩的字符数组解压成图像
   friend Point REHelper_Diagonal_Priority(Mat f, Mat mark, int M, int N, Point start, int xgm);//用对角线优先策略寻找最大的矩型子模式
   friend Point REHelper_Horizonal_Priority(Mat f, Mat mark, int M, int N, Point start, int xgm);//用水平优先策略寻找最大的矩型子模式
   friend void RNAMCEncoding_Diagonal_Priority(Mat f,Mat &R,Mat &markMatrix,int M,int N,vector<Color> &p,vector<char> &q,int xgm);
   friend void RNAMCEncoding_Horizonal_Priority(Mat f,Mat &R,Mat &markMatrix,int M,int N,vector<Color> &p,vector<char> &q,int xgm);
   friend void RDHelper(Mat& R, Color p1);//恢复子模式的值
   friend void RNAMCDecoding(Mat& R, int M, int N, vector<Color> p, vector<char> q);//灰度图解码
   friend double PSNR(Mat f, Mat R, int M, int N);//计算信噪比
   friend double BPP(vector<Color> p, int M, int N, vector<char> q);
   friend void segmentDisplay(Mat &display, vector<Color> p);//化分割图
   friend void CR();//计算压缩比
   //运用友元函数将执行算法所需的函数包含在类中
};

bool isSameBlock(Mat f, Mat mark, Point lt, Point rb, int xgm);//使用改良isSameBlock阴影法判断是否同类块
void mark(Mat &mark, Point lt, Point rb);//用于给处理过的区域做标记
void EnCode(Mat &R,int height, int width, vector<char> &Q);//用于将编码后的图像转换成用压缩的字符串表示
void Decode(Mat &R, int height, int width, const vector<char> &Q);//用于将压缩的字符数组解压成图像
Point REHelper_Diagonal_Priority(Mat f, Mat mark, int M, int N, Point start, int xgm);//用对角线优先策略寻找最大的矩型子模式
Point REHelper_Horizonal_Priority(Mat f, Mat mark, int M, int N, Point start, int xgm);//用水平优先策略寻找最大的矩型子模式
void RNAMCEncoding_Diagonal_Priority(Mat f,Mat &R,Mat &markMatrix,int M,int N,vector<Color> &p,vector<char> &q,int xgm);
void RNAMCEncoding_Horizonal_Priority(Mat f,Mat &R,Mat &markMatrix,int M,int N,vector<Color> &p,vector<char> &q,int xgm);
void RDHelper(Mat& R, Color p1);//恢复子模式的值
void RNAMCDecoding(Mat& R, int M, int N, vector<Color> p, vector<char> q);//灰度图解码
double PSNR(Mat f, Mat R, int M, int N);//计算信噪比
double BPP(vector<Color> p, int M, int N, vector<char> q);//计算bpp值
void segmentDisplay(Mat &display, vector<Color> p);//化分割图


#endif // ALGO_H
