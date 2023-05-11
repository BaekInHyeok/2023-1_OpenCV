//////////////////////////////////////////////////////////////
//                                                          //
//                HW#2-3 : Bit Plane Slicing                //
//                                                          //
//   �ۼ��� : 2020039096 ������		��¥:2023�� 4�� 5��     //
//                                                          //
//   ���� ���� : 8-bit ���� ���� Bit-plane ���� ����      //
//                                                          //
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

char print(int i) {
	char temp = (char)(i + '0');
	return temp;
}

int main()
{
	//������ ������ ����Ǿ��ִ� ��ο��� grayscale�� �����´�.
	Mat m1 = imread("C:/University/major/ImageProcessing/Practice/image/Fig0314(a)(100-dollars).tif", IMREAD_GRAYSCALE);
	imshow("Original", m1);//�������� ���� ���

	int cols, rows, x, y;

	cols = m1.cols;
	rows = m1.rows;

	printf("%d %d \n", m1.rows, m1.cols);

	Mat out[8];

	//������ 8-bit �������� ��ȯ
	//CV_8UC1 : 8 - bit unsigned integer : uchar(0..255)
	for (int i = 0; i <= 7; i++) {
		out[i] = Mat(rows, cols, CV_8UC1, Scalar(0));
	}

	//bit-plane 1�ܰ� ~ 8�ܰ� ������ �ݺ�(C++ �迭������ 0~7)
	for (int i = 0; i <= 7; i++) {

		/*�� ��Ʈ�� ���� ����ȭ ���*/
		for (int x = 0; x < rows; x++) {
			for (int y = 0; y < cols; y++) {
				out[i].at<uchar>(x, y) = (m1.at<uchar>(x, y) & uchar(pow(2, i))) ? uchar(255) : uchar(0);
			}
		}
		string s = "dstImage";
		s += print(i);
		imshow(s, out[i]);
	}

	waitKey(0);

	return 0;
}