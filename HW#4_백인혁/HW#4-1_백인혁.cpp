//////////////////////////////////////////////////////////////
//                                                          //
//				    HW#4-1 : Edge Detector		            //
//                                                          //
//   �ۼ��� : 2020039096 ������		��¥ : 2023�� 5�� 2��   //
//                                                          //
//         ���� ���� : Sobel ������, Laplacian ������,      //
//    Marr-Hildreth ���� ���� �˰����� �̿��� edge ����   //
//															//
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void ZeroCrossing(Mat& src, Mat& dst, int threshold);  // 0 ������ üũ

int main() {
	//�����ο��� �̹����� �׷��̽����Ϸ� �о����
	Mat srcImage = imread("C:/University/major/ImageProcessing/Practice/image/HW4-1.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	imshow("Original", srcImage);


	/*1. Sobel ������ ���-------------------------------------------------------------------------------*/

	int ksize = 3;
	int ddepth = CV_32F;	// ���̿� ���� �ڷ��� ����
	Mat dstGx, dstGy;

	//x ������ �̺��� ����
	Sobel(srcImage, dstGx, ddepth, 1, 0, ksize);    // dx

	//y ������ �̺��� ����
	Sobel(srcImage, dstGy, ddepth, 0, 1, ksize);	// dy

	int dtype = CV_8U;

	//x ���� �̺� ���뿡 ���� ����ȭ ����
	Mat dstImageGx;
	normalize(abs(dstGx), dstImageGx, 0, 255, NORM_MINMAX, dtype);    // |dstGx|
	imshow("dstImageGx", dstImageGx);

	//y ���� �̺� ���뿡 ���� ����ȭ ����
	Mat dstImageGy;
	normalize(abs(dstGy), dstImageGy, 0, 255, NORM_MINMAX, dtype);	// |dstGy|	
	imshow("dstImageGy", dstImageGy);

	//edge magnitude
	Mat dstMag;
	magnitude(dstGx, dstGy, dstMag);  // �ܼ�ȭ�ϸ�.. |dstGx| + |dstGy|

	//edge magnitude �Ϸ��� ������ ����ȭ ����
	Mat dstImageGxy;
	normalize(dstMag, dstImageGxy, 0, 255, NORM_MINMAX, dtype);
	imshow("SobelResult", dstImageGxy);


	/*2.Laplacian ������ ���-------------------------------------------------------------------------------*/

	ksize = 15;
	Mat blurImage;
	GaussianBlur(srcImage, blurImage, Size(ksize, ksize), 0.0);  // srcImage�� 15 x 15�� ����þ� ���ͷ� ������

	Mat lapImage;
	Laplacian(blurImage, lapImage, CV_32F, ksize);  // ����þ� ������ �� ���� ���� ���ö�þ� ���͸� ����

	Mat lapResult;
	ZeroCrossing(lapImage, lapResult, 10);  // ���ö�þ� ����� ���� �������� üũ

	imshow("LaplacianResult", lapResult);

	/*3.Marr-Hildreth ���� ���� �˰���(LOG ���)--------------------------------------------------------------*/
	// ������ Ŀ���� ũ�� n = 2 x 3 x sigma + 1 �Ǵ�  sigma = 0.3(n/2 - 1)+0.8�� ���

	const int ksizeLOG = 9;
	float logArr[ksizeLOG * ksizeLOG];
	int   s, t, k = 0;
	float g;
	float sigma = 1.4f;
	//float sigma= 0.3f*(ksizeLOG/2-1.0f) + 0.8f;

	for (s = -ksizeLOG / 2; s <= ksizeLOG / 2; s++)   // ksizeLOG x ksizeLOG ũ���� LoG ���� Ŀ�� ����
	{
		for (t = -ksizeLOG / 2; t <= ksizeLOG / 2; t++)
		{
			g = exp(-((float)s * s + (float)t * t) / (2 * sigma * sigma));
			g *= (1 - ((float)s * s + (float)t * t) / (2 * sigma * sigma));
			g /= (3.141592f * sigma * sigma * sigma * sigma);
			logArr[k++] = -g;
		}
	}

	Mat logKernel(ksizeLOG, ksizeLOG, CV_32F, logArr);
	cout << "logKernel=" << logKernel << endl;

	Mat logImage;
	filter2D(srcImage, logImage, CV_32F, logKernel);  // LoG ���͸�

	Mat logResult;
	ZeroCrossing(logImage, logResult, 0);  // 0 ������ ����
	imshow("LogResult", logResult);

	waitKey();
	return 0;
}

// ���ö�þ� ���͸��� �Է� ���� src���� ���ι���� ���� ������ �̿��� �����Ͽ� ��ȣ�� ����Ǵ� 0-���� ��ġ�� �����ϰ�
// ����Ǵ� ���̸� ���밪���� ������ ����, threshold �Լ��� �Ӱ谪 �̻��� ū ������ ��ȣ�� ����Ǵ� ��ġ�� ������ dst ���� �ݿ�

void ZeroCrossing(Mat& src, Mat& dst, int th)
{
	int x, y;
	double a, b;

	Mat zeroCrossH(src.size(), CV_32F, Scalar::all(0));  // ���� ������ 0-���� ����
	// src�� ������ ũ����, CV_32F�� �ڷ����� 0���� �ʱ�ȭ�� ��� ����

	Mat_<float> _src(src);	// src�� �����Ͽ� _src ����

	for (x = 1; x < src.rows - 1; x++)
	{
		for (y = 1; y < src.cols - 1; y++)
		{

			// (+.-), (-,+), (+,0,-), (-,0,+) �� ��츦 �����Ͽ� �����ϴ� ������ zeroCrossH�� ����

			a = _src(x, y);     		// ���� ������ ������ �� �ȼ� ����
			b = _src(x, y + 1);

			if (a == 0)   			// �ش� �ȼ��� ���� 0 �̸� �� ������ �ȼ��� �ٽ� ����.
				// (+,0,-) �Ǵ� (-,0,+)�� ��츦 �����ϱ� ����
				a = _src(x, y - 1);

			if (a * b < 0)			// ���� ������ ������ �� �ȼ��� ��ȣ�� �ٸ��ٸ�
				// �� �ȼ��� ���밪�� ���� ����
				zeroCrossH.at<float>(x, y) = fabs(a) + fabs(b);

			else				// ���� ������ ������ �� �ȼ��� ��ȣ�� ������ 0 ����
				zeroCrossH.at<float>(x, y) = 0;

		}
	}

	Mat zeroCrossV(src.size(), CV_32F, Scalar::all(0));  // ���� ������ 0-���� ����
	for (x = 1; x < src.rows - 1; x++)
	{
		for (y = 1; y < src.cols - 1; y++)
		{
			a = _src(x, y);
			b = _src(x + 1, y);

			if (a == 0)
				a = _src(x - 1, y);

			if (a * b < 0)
				zeroCrossV.at<float>(x, y) = fabs(a) + fabs(b);
			else
				zeroCrossV.at<float>(x, y) = 0;
		}
	}

	Mat zeroCross(src.size(), CV_32F, Scalar::all(0));

	add(zeroCrossH, zeroCrossV, zeroCross);  // zeroCross = zeroCrossH + zeroCrossV

	threshold(zeroCross, dst, th, 255, THRESH_BINARY);
}

