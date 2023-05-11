//////////////////////////////////////////////////////////////
//                                                          //
//             HW#2-2 : Piecewise-Linear Transform          //
//                                                          //
//   작성자 : 2020039096 백인혁		날짜:2023년 4월 4일     //
//                                                          //
//   문제 정의 :  명암도 변환 함수 구현 및 테스트           //
//                                                          //
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

// Gray-level Slicing
uchar computeOutput(uchar x, int A, int s1, int B, int s2, int option = 0);

int main() {
	//이미지 읽어오기
	Mat src = imread("C:/University/major/ImageProcessing/Practice/image/Fig0310(b)(washed_out_pollen_image).tif", 0);

	Mat newImage1 = src.clone();
	Mat newImage2 = src.clone();
	int s;
	int A = 64, s1 = 64, B = 255, s2 = 255;

	//src 이미지의 각 화소마다 이미지 처리를 수행한다.
	for (int x = 0; x < src.rows; x++) {
		for (int y = 0; y < src.cols; y++) {
			/*saturate_cast: 화소값이 허용범위(0 ~ 255)를 벗어나는 상황을 방지하는 함수
			화소값 < 0 : 0으로 변환, 화소값 > 255 : 255로 변환*/

			s = computeOutput(src.at<uchar>(x, y), A, s1, B, s2, 0);
			newImage1.at<uchar>(x, y) = saturate_cast<uchar>(s);

			s = computeOutput(src.at<uchar>(x, y), A, s1, B, s2, 1);
			newImage2.at<uchar>(x, y) = saturate_cast<uchar>(s);
		}
	}

	/*결과 출력*/
	imshow("03.10(b)", src);
	imshow("03.10(c)", newImage1);
	imshow("03.10(d)", newImage2);

	waitKey(0);
	return 0;
}


uchar computeOutput(uchar x, int A, int s1, int B, int s2, int option) {
	uchar result = 0;
	switch (option) {
	
	/*구간에 따른 명함도 변환 함수 구현*/
	case 0:
		// r1~r2 영역의 기울기 3, 나머지 영역의 기울기 0.5
		// r2이상의 영역은 r1이하의 영역의 직선에서 2.5만큼 y축으로 평행이동 시킨 직선

		//r1~r2 영역
		if (A < x && x <= B) 
			result = 3 * x - 5;

		//r1 이하 구역
		else if (A < x) 
			result = 0.5 * x;

		//r2 이상 구역
		else 
			result = 0.5 * x + 2.5;
		break;

	//Thresholding
	case 1:
		//임계값을 110으로 정하고, 그 미만일 경우 0으로, 그 이상일 경우 255로 설정
		if (x < 110)
			result = 0;
		else
			result = 255;
		break;
	}

	return result;
}
