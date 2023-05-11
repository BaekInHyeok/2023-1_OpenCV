//////////////////////////////////////////////////////////////
//                                                          //
//             HW#2-2 : Piecewise-Linear Transform          //
//                                                          //
//   �ۼ��� : 2020039096 ������		��¥:2023�� 4�� 4��     //
//                                                          //
//   ���� ���� :  ��ϵ� ��ȯ �Լ� ���� �� �׽�Ʈ           //
//                                                          //
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

// Gray-level Slicing
uchar computeOutput(uchar x, int A, int s1, int B, int s2, int option = 0);

int main() {
	//�̹��� �о����
	Mat src = imread("C:/University/major/ImageProcessing/Practice/image/Fig0310(b)(washed_out_pollen_image).tif", 0);

	Mat newImage1 = src.clone();
	Mat newImage2 = src.clone();
	int s;
	int A = 64, s1 = 64, B = 255, s2 = 255;

	//src �̹����� �� ȭ�Ҹ��� �̹��� ó���� �����Ѵ�.
	for (int x = 0; x < src.rows; x++) {
		for (int y = 0; y < src.cols; y++) {
			/*saturate_cast: ȭ�Ұ��� ������(0 ~ 255)�� ����� ��Ȳ�� �����ϴ� �Լ�
			ȭ�Ұ� < 0 : 0���� ��ȯ, ȭ�Ұ� > 255 : 255�� ��ȯ*/

			s = computeOutput(src.at<uchar>(x, y), A, s1, B, s2, 0);
			newImage1.at<uchar>(x, y) = saturate_cast<uchar>(s);

			s = computeOutput(src.at<uchar>(x, y), A, s1, B, s2, 1);
			newImage2.at<uchar>(x, y) = saturate_cast<uchar>(s);
		}
	}

	/*��� ���*/
	imshow("03.10(b)", src);
	imshow("03.10(c)", newImage1);
	imshow("03.10(d)", newImage2);

	waitKey(0);
	return 0;
}


uchar computeOutput(uchar x, int A, int s1, int B, int s2, int option) {
	uchar result = 0;
	switch (option) {
	
	/*������ ���� ���Ե� ��ȯ �Լ� ����*/
	case 0:
		// r1~r2 ������ ���� 3, ������ ������ ���� 0.5
		// r2�̻��� ������ r1������ ������ �������� 2.5��ŭ y������ �����̵� ��Ų ����

		//r1~r2 ����
		if (A < x && x <= B) 
			result = 3 * x - 5;

		//r1 ���� ����
		else if (A < x) 
			result = 0.5 * x;

		//r2 �̻� ����
		else 
			result = 0.5 * x + 2.5;
		break;

	//Thresholding
	case 1:
		//�Ӱ谪�� 110���� ���ϰ�, �� �̸��� ��� 0����, �� �̻��� ��� 255�� ����
		if (x < 110)
			result = 0;
		else
			result = 255;
		break;
	}

	return result;
}
