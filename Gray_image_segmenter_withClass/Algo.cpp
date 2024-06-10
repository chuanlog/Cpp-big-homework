#include "Algo.h"

Algo::Algo() {}

void Algo::run()
{
    Mat img=square;
    if (!img.empty()) {
        /*一，分割同类块及编码*/
        M = img.rows;
        N = img.cols;
        markMatrix = Mat::zeros(M, N, CV_8UC1);
        R = Mat::zeros(M, N, CV_8UC1);

        int xigema = epliosn;
        MyTimer mt;
        mt.Start();
        /*分块*/
        if(way==0)
        {
            RNAMCEncoding_Diagonal_Priority(img, R, markMatrix, M, N, colorList, coordinateList, xigema);
        }//用对角线优先策略
        else if(way==1)
        {
            RNAMCEncoding_Horizonal_Priority(img, R, markMatrix, M, N, colorList, coordinateList, xigema);
        }//用水平优先策略

        /*矩阵编码*/
        EnCode(R, M, N, coordinateList);
        mt.End();

        time1 = mt.costTime;
        mt.Reset();

        /*二，还原图像矩阵及图像*/
        img1 = Mat::zeros(M, N, CV_8UC1);

        mt.Start();
        Decode(img1, M, N, coordinateList);
        RNAMCDecoding(img1, M, N, colorList, coordinateList);
        mt.End();
        time2 = mt.costTime;
        mt.Reset();

        nums = colorList.size();
        psnr = PSNR(img, img1, M, N);
        bpp = BPP(colorList, M, N, coordinateList);
        cr = 8.0 / bpp;


        /*分割图*/
        Mat display(M, N, CV_8UC1, Scalar::all(255));
        segmentDisplay(display, colorList);
        img2 = display;
        img.release();
        display.release();
    }
}




void fun(int epsilon, Mat mat, int& time1, int& time2, int& num, double& psnr, double& bpp, double& cr, Mat& img1, Mat& img2,int ways)
{
    Mat img = mat;
    if (!img.empty()) {
        /*一，分割同类块及编码*/
        int M = img.rows;
        int N = img.cols;

        Mat img_gray = img;
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



//使用改良isSameBlock阴影法判断是否同类块
bool isSameBlock(Mat f,Mat mark, Point lt, Point rb,int xgm)
{
    uchar g1 = f.at<uchar>(lt);
    uchar g2 = f.at<uchar>(Point(rb.x, lt.y));
    uchar g3 = f.at<uchar>(Point(lt.x, rb.y));
    uchar g4 = f.at<uchar>(rb);
    //标准矩形
    if (lt.x < rb.x&&lt.y < rb.y)
    {
        int flag = 1;
        for (int j = lt.y; j <= rb.y; j++)
        {
            for (int i = lt.x; i <= rb.x; i++)
            {
                double i1 = (j - lt.y) / (double)(rb.y - lt.y);
                double i2 = (i - lt.x) / (double)(rb.x - lt.x);
                double g5 = g1 + (g2 - g1)*i2;
                double g6 = g3 + (g4 - g3)*i2;
                double gest = g5 + (g6 - g5)*i1;
                //cout << g1 << " " << g2 << " " << g3 << " " << g4 << " " << g5 << " " << g6 << " " << gest << " "<<f.at<uchar>(Point(i,j))<<endl;
                if (abs(f.at<uchar>(Point(i, j)) - gest) > xgm||mark.at<uchar>(Point(i,j))==1)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 0)break;
        }
        return flag;
    }
    //宽为1的矩形
    else if (lt.x != rb.x&&lt.y == rb.y)
    {
        int flag = 1;
        for (int i = lt.x; i <= rb.x; i++)
        {
            double i2 = (i - lt.x) / (double)(rb.x - lt.x);
            double gest = g1 + (g4 - g1)*i2;
            if (abs(f.at<uchar>(Point(i, lt.y)) - gest) > xgm|| mark.at<uchar>(Point(i,lt.y)) == 1)
            {
                flag = 0;
                break;
            }
        }
        return flag;
    }
    //长为1的矩形
    else if (lt.x == rb.x&&lt.y != rb.y)
    {
        int flag = 1;
        for (int j = lt.y; j <= rb.y; j++)
        {
            double i1 = (j - lt.y) / (double)(rb.y - lt.y);
            double gest = g1 + (g4 - g1)*i1;
            if (abs(f.at<uchar>(Point(lt.x, j)) - gest) > xgm|| mark.at<uchar>(Point(lt.x,j)) == 1)
            {
                flag = 0;
                break;
            }
        }
        return flag;
    }
    //孤立点矩形
    else if (lt.x == rb.x&&lt.y == rb.y)
    {
        //double g1 = f.at<uchar>(lt);
        if (mark.at<uchar>(lt) == 1)return 0;
        return 1;
    }
}

//给灰度图f已经搜索过的矩形子模式做标记
void mark(Mat &mark, Point lt, Point rb) {
    for (int i = lt.y; i <= rb.y; i++)
        for (int j = lt.x; j <= rb.x; j++)
            mark.at<uchar>(i, j) = 1;
}

void EnCode(Mat &R, int height, int width, vector<char> &Q)
{
    int c = 0;
    int offsetValue = 0;
    int count = 0;

    for (int i = 0; i < height; i++)
    {
        c = 0;
        offsetValue = 0;
        count = 0;
        //Q.push_back(' ');
        for (int j = 0; j < width; j++)
        {
            int value = R.at<uchar>(i,j);
            if (0 == value)
            {
                if (j == width - 1)
                {
                    Q.push_back('0');
                }
            }
            else
            {
                if (1 == value)
                {
                    Q.push_back('1');
                    Q.push_back('1');

                }
                else if (2 == value)
                {
                    Q.push_back('1');
                    Q.push_back('0');
                    Q.push_back('1');
                }
                else if (3 == value)
                {
                    Q.push_back('1');
                    Q.push_back('0');
                    Q.push_back('0');

                }

                //位置从1开始 不是从0开始 所以多减去1
                int b = ceil(log((double)(width - c - count)) / log(2.0f));
                if (0 == count)
                {
                    offsetValue = j;
                }
                else
                {
                    offsetValue = j - c - 1;
                }

                b = (b == 0) ? 1 : b;
                count = 1;
                c = j;

                for (int v = b - 1; v >= 0; v--)
                {
                    if ((offsetValue & (1 << v)) == 0)
                    {
                        Q.push_back('0');
                    }
                    else
                    {
                        Q.push_back('1');
                    }
                }
            }
        }
    }
}

void Decode(Mat &R, int height, int width, const vector<char> &Q)
{
    int n = 0;
    int count = 0;
    int c = 0;
    int row = 0;
    int num = 0;
    for (int pos = 0; pos < Q.size(); pos++)
    {
        if ('1' == Q[pos])
        {
            pos++;
            if ('1' == Q[pos])
            {
                n = 1;

            }
            else
            {
                pos++;
                if ('1' == Q[pos])
                {
                    n = 2;
                }
                else
                {
                    n = 3;
                }
            }
        }
        else
        {
            row++;
            count = 0;
            c = 0;
            num = 0;
            continue;
        }

        int b = ceil(log((double)(width - c - count)) / log(2.0f));
        b = b == 0 ? 1 : b;
        count = 1;

        int value = 0;
        for (int i = b - 1; i >= 0; i--)
        {
            pos++;
            if ('1' == Q[pos])
            {
                value += 1 << i;
            }
        }

        if (0 == num)
        {
            c = c + value;
        }
        else
        {
            c = c + value + 1;
        }

        num++;


        R.at<uchar>(row,c) = n;
        if (c == (width - 1))
        {
            row++;
            count = 0;
            c = 0;
            num = 0;
        }
    }
}

//用Diagonal priority寻找最大的矩形子模式
Point REHelper_Diagonal_priority(Mat f, Mat mark, int M, int N, Point start,int xgm) {
    Point end = start;
    Point end1, end2;
    while (end.x < M&&end.y < N && (mark.at<uchar>(end) == 0) && (mark.at<uchar>(start) == 0) ){
        if (!isSameBlock(f, mark,start, end,xgm)) break;
        end.x++;
        end.y++;
    }
    end.x--;
    end.y--;

    end1 = end;
    while (end1.x < M && (mark.at<uchar>(end1) == 0)) {
        if (!isSameBlock(f,mark, start, end1,xgm)) break;
        end1.x++;
    }
    end1.x--;

    end2 = end;
    while (end2.y < N && (mark.at<uchar>(end2) == 0)) {
        if (!isSameBlock(f, mark,start, end2,xgm)) break;
        end2.y++;
    }
    end2.y--;


    if ((end2.x - start.x + 1)*(end2.y - start.y + 1) > (end1.x - start.x + 1)*(end1.y - start.y + 1))return end2;
    else return end1;
}

//用Horizonal priority策略寻找最大的矩型子模式
Point REHelper_Horizonal_priority(Mat f, Mat mark, int M, int N, Point start,int xgm) {
    Point end2,end1 = end2 = start;

    while (end1.x < M && (mark.at<uchar>(end1) != 1)) {
        if (!isSameBlock(f, mark,start, end1, xgm)) break;
        end1.x++;
    }
    end1.x--;
    while (end1.y < N && (mark.at<uchar>(end1) != 1)) {
        if (!isSameBlock(f,mark, start, end1, xgm)) break;
        end1.y++;
    }
    end1.y--;

    while (end2.y < N && (mark.at<uchar>(end2) != 1)) {
        if (!isSameBlock(f, mark,start, end2, xgm)) break;
        end2.y++;
    }
    end2.y--;
    while (end2.x < M && (mark.at<uchar>(end2) != 1)) {
        if (!isSameBlock(f, mark,start, end2, xgm)) break;
        end2.x++;
    }
    end2.x--;


    if ((end2.x - start.x + 1)*(end2.y - start.y + 1) > (end1.x - start.x + 1)*(end1.y - start.y + 1))return end2;
    else return end1;
}


//Diagonal_Priority策略给灰度图f编码
void RNAMCEncoding_Diagonal_Priority(Mat f, Mat& R, Mat& markMatrix, int M, int N, vector<Color>& p, vector<char>& q, int xgm) {
    Point start, end;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (markMatrix.at<uchar>(i, j) == 0)
            {
                start = Point(j, i);
                end = REHelper_Diagonal_priority(f, markMatrix, M, N, start, xgm);
                Color p1;
                p1.setLt(start);
                p1.setRb(end);
                uchar g1 = f.at<uchar>(start);
                uchar g2 = f.at<uchar>(Point(end.x, start.y));
                uchar g3 = f.at<uchar>(Point(start.x, end.y));
                uchar g4 = f.at<uchar>(end);
                if (start.x < end.x && start.y < end.y)
                {
                    p1.setGrey(Scalar(g1, g2, g3, g4));
                    R.at<uchar>(start) = 1;
                    R.at<uchar>(end) = 2;
                }
                //宽为1的矩形
                if (start.x != end.x && start.y == end.y)
                {
                    p1.setGrey(Scalar(g1, 0, 0, g4));
                    R.at<uchar>(start) = 1;
                    R.at<uchar>(end) = 2;
                }
                //长为1的矩形
                if (start.x == end.x && start.y != end.y)
                {
                    p1.setGrey(Scalar(g1, 0, 0, g4));
                    R.at<uchar>(start) = 1;
                    R.at<uchar>(end) = 2;
                }
                //孤立点矩形
                if (start.x == end.x && start.y == end.y)
                {
                    p1.setGrey(Scalar(g1, 0, 0, 0));
                    R.at<uchar>(start) = 3;
                }
                p.push_back(p1);
                mark(markMatrix, start, end);
                /*for (int i = 0; i < M; i++) {
                    for (int j = 0; j < N; j++) {
                        cout << (int)markmatrix.at<uchar>(i, j);
                    }
                    cout << endl;
                }
                cout << endl;*/
            }
        }
    }
}

//用Horizonal_Priority策略给灰度图f编码
void RNAMCEncoding_Horizonal_Priority(Mat f,Mat &R,Mat &markMatrix,int M,int N,vector<Color> &p,vector<char> &q,int xgm) {
    Point start, end;
    for (int i = 0; i < M; i++)
    {

        for (int j = 0; j < N; j++)
        {
            if (markMatrix.at<uchar>(i, j) == 0)
            {
                start = Point(j, i);
                end = REHelper_Horizonal_priority(f, markMatrix, M, N, start, xgm);
                Color p1;
                p1.setLt(start);
                p1.setRb(end);
                uchar g1 = f.at<uchar>(start);
                uchar g2 = f.at<uchar>(Point(end.x, start.y));
                uchar g3 = f.at<uchar>(Point(start.x, end.y));
                uchar g4 = f.at<uchar>(end);
                if (start.x < end.x && start.y < end.y)
                {
                    p1.setGrey(Scalar(g1, g2, g3, g4));
                    R.at<uchar>(start) = 1;
                    R.at<uchar>(end) = 2;
                }
                //宽为1的矩形
                if (start.x != end.x && start.y == end.y)
                {
                    p1.setGrey(Scalar(g1, 0, 0, g4));
                    R.at<uchar>(start) = 1;
                    R.at<uchar>(end) = 2;
                }
                //长为1的矩形
                if (start.x == end.x && start.y != end.y)
                {
                    p1.setGrey(Scalar(g1, 0, 0, g4));
                    R.at<uchar>(start) = 1;
                    R.at<uchar>(end) = 2;
                }
                //孤立点矩形
                if (start.x == end.x && start.y == end.y)
                {
                    p1.setGrey(Scalar(g1, 0, 0, 0));
                    R.at<uchar>(start) = 3;
                }
                p.push_back(p1);
                mark(markMatrix, start, end);
            }
        }
    }
}


//恢复矩形子模式的值
void RDHelper(Mat& R, Color p1) {
    Point lt = p1.getLt();
    Point rb = p1.getRb();
    uchar g1 = p1.getGrey()[0];
    uchar g2 = p1.getGrey()[1];
    uchar g3 = p1.getGrey()[2];
    uchar g4 = p1.getGrey()[3];
    //标准矩形
    if (lt.x < rb.x&&lt.y < rb.y)
    {

        for (int j = lt.y; j <= rb.y; j++)
        {
            for (int i = lt.x; i <= rb.x; i++)
            {
                double i1 = (j - lt.y) / (double)(rb.y - lt.y);
                double i2 = (i - lt.x) / (double)(rb.x - lt.x);
                double g5 = g1 + (g2 - g1)*i2;
                double g6 = g3 + (g4 - g3)*i2;
                double gest = g5 + (g6 - g5)*i1;
                R.at<uchar>(Point(i, j)) = gest;
            }
        }
    }
    //宽为1的矩形
    if (lt.x != rb.x&&lt.y == rb.y)
    {
        for (int i = lt.x; i <= rb.x; i++)
        {
            double i2 = (i - lt.x) / (double)(rb.x - lt.x);
            double gest = g1 + (g4 - g1)*i2;
            R.at<uchar>(Point(i, lt.y)) = gest;
        }
    }
    //长为1的矩形
    if (lt.x == rb.x&&lt.y != rb.y)
    {
        for (int j = lt.y; j <= rb.y; j++)
        {
            double i1 = (j - lt.y) / (double)(rb.y - lt.y);
            double gest = g1 + (g4 - g1)*i1;
            R.at<uchar>(Point(lt.x, j)) = gest;
        }
    }
    //孤立点矩形
    if (lt.x == rb.x&&lt.y == rb.y)
    {
        R.at<uchar>(Point(lt.x, lt.y)) = g1;
    }
}

//灰度图f解码
void RNAMCDecoding(Mat& R,int M,int N,vector<Color> p,vector<char> q) {
    for (int i = 0; i < p.size(); i++)
        RDHelper(R, p[i]);
}

//PSNR
double PSNR(Mat f, Mat R,int M,int N) {
    double mid = 0;;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) {
            mid += pow(f.at<uchar>(i, j) - R.at<uchar>(i, j), 2);
        }
    return 10 * log10f(pow(255., 2)*M*N / mid);
}

//BPP
double BPP(vector<Color> p, int M, int N, vector<char> q) {
    int a1 = 0, a2 = 0, a3 = 0;
    for (int i = 0; i < p.size(); i++) {
        if (p[i].getGrey()[0] != -1 && p[i].getGrey()[3] != -1) a1++;
        else if (p[i].getGrey()[1] == -1 && p[i].getGrey()[2] == -1) a3++;
        else  a2++;
    }
    double BPPValue = (q.size() + 16 * a1 + 8 * a2 + 4.0*a3) / (M*N);
    return BPPValue;
}

void segmentDisplay(Mat &display, vector<Color> p) {
    for (int i = 0; i < p.size(); i++) {
        rectangle(display,p[i].getLt(),p[i].getRb(), Scalar(0),1);
    }
}
