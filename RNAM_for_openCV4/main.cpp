#include "Header.h"
//  lena512.bmp gray.jpg rnamc.jpg 10
/*����cyc*/

int main(int argc, char** argv)//�ֱ�����1.ԭ�Ҷ�ͼ 2.ת�Ҷ�ͼ�ļ��� 3.�������ļ��� 4.EPSILON
{
	if (argc == 5) {
		Mat img=imread(argv[1]);
		if (!img.empty()) {
			namedWindow("ԭͼ�Ҷ�ͼ��", 1);
			imshow("ԭͼ�Ҷ�ͼ��", img);
			/*һ���ָ�ͬ��鼰����*/
			int M = img.rows;
			int N = img.cols;
			
			Mat img_gray = img;
			cvtColor(img, img_gray, CV_BGR2GRAY);
			Mat markMatrix = Mat::zeros(M, N, CV_8UC1);
			Mat R = Mat::zeros(M, N, CV_8UC1);
			
			vector<Color> colorList;
			vector<char> coordinateList;
			int xigema = atoi(argv[4]);
			MyTimer mt;
			mt.Start();
			
			/*�ֿ�*/
			RNAMCEncoding(img_gray,R,markMatrix,M,N,colorList,coordinateList,xigema);
	
			/*�������*/
			EnCode(R, M, N, coordinateList);
			mt.End();

			cout << "����ѹ������:" << mt.costTime << "ms" << endl;
			mt.Reset();

			/*������ԭͼ�����ͼ��*/
			Mat T = Mat::zeros(M, N, CV_8UC1);

			mt.Start();
			Decode(T, M, N, coordinateList);
			RNAMCDecoding(T, M, N, colorList, coordinateList);
			mt.End();
			cout << "��ԭͼ���ʱ:" << mt.costTime << "ms" << endl;
			mt.Reset();

			cout << "����:" << colorList.size() << endl;
			cout << "PSNRֵ:" << PSNR(img_gray,T,M,N) << endl;
			double BPPValue = BPP(colorList,M,N,coordinateList);
			cout << "BPPֵ:" << BPPValue << endl;
			cout << "CRֵ:" << 8.0 / BPPValue << endl;

			namedWindow("ѹ��ͼ�Ҷ�ͼ��", 1);
			imshow("ѹ��ͼ�Ҷ�ͼ��", T);

			/*�ָ�ͼ*/
			Mat display(M, N, CV_8UC1, Scalar::all(255));
			segmentDisplay(display, colorList);
			namedWindow("�ָ�ͼ", 1);
			imshow("�ָ�ͼ", display);
			imwrite("hjw.bmp", display);
			waitKey(0);
			destroyAllWindows();
			img.release();
			img_gray.release();
			display.release();
			T.release();
		}
	}

	return 0;
}