#include<opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include<iostream>
#include<vector>
#include<cmath>
#include <windows.h>
using namespace cv;
using namespace std;

//��ɫ��
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
//��ʱ
class MyTimer {
private:
	int _freq;
	LARGE_INTEGER _begin;
	LARGE_INTEGER _end;
public:
	long costTime;            // ���ѵ�ʱ��(��ȷ��΢��)
public:
	MyTimer() {
		LARGE_INTEGER tmp;
		QueryPerformanceFrequency(&tmp);
		_freq = tmp.QuadPart;
		costTime = 0;
	}
	void Start() {            // ��ʼ��ʱ
		QueryPerformanceCounter(&_begin);
	}
	void End() {                // ������ʱ
		QueryPerformanceCounter(&_end);
		costTime = (long)((_end.QuadPart - _begin.QuadPart) * 1000 / _freq);
	}
	void Reset() {            // ��ʱ��0
		costTime = 0;
	}
};



bool isSameBlock(Mat f,Mat mark, Point lt, Point rb,int xgm);
void mark(Mat &mark, Point lt, Point rb);
void EnCode(Mat &R, int height, int width, vector<char> &Q);
void Decode(Mat &R, int height, int width, const vector<char> &Q);
Point REHelper(Mat f, Mat mark, int M, int N, Point start, int xgm);
void RNAMCEncoding(Mat f, Mat &R, Mat &markMatrix, int M, int N, vector<Color> &p, vector<char> &q, int xgm);
void RDHelper(Mat& R, Color p1);
void RNAMCDecoding(Mat& R, int M, int N, vector<Color> p, vector<char> q);
double PSNR(Mat f, Mat R, int M, int N);
double BPP(vector<Color> p, int M, int N, vector<char> q);
void segmentDisplay(Mat &display, vector<Color> p);