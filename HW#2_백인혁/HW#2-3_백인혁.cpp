//////////////////////////////////////////////////////////////
//                                                          //
//                HW#2-3 : Bit Plane Slicing                //
//                                                          //
//   작성자 : 2020039096 백인혁		날짜:2023년 4월 5일     //
//                                                          //
//   문제 정의 : 8-bit 영상에 대한 Bit-plane 수행 구현      //
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
	//영상을 영상이 저장되어있는 경로에서 grayscale로 가져온다.
	Mat m1 = imread("C:/University/major/ImageProcessing/Practice/image/Fig0314(a)(100-dollars).tif", IMREAD_GRAYSCALE);
	imshow("Original", m1);//오리지날 영상 출력

	int cols, rows, x, y;

	cols = m1.cols;
	rows = m1.rows;

	printf("%d %d \n", m1.rows, m1.cols);

	Mat out[8];

	//영상을 8-bit 영상으로 변환
	//CV_8UC1 : 8 - bit unsigned integer : uchar(0..255)
	for (int i = 0; i <= 7; i++) {
		out[i] = Mat(rows, cols, CV_8UC1, Scalar(0));
	}

	//bit-plane 1단계 ~ 8단계 순서로 반복(C++ 배열에서는 0~7)
	for (int i = 0; i <= 7; i++) {

		/*각 비트에 대한 이진화 출력*/
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