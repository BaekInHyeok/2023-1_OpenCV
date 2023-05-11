//////////////////////////////////////////////////////////////
//                                                          //
//                HW#2-5 : Logic Operation                  //
//                                                          //
//   작성자 : 2020039096 백인혁		날짜:2023년 4월 6일     //
//                                                          //
//     문제 정의 : 주어진 두 영상에 대한 논리 연산 수행     //
//                                                          //
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
	//두 개의 영상을 영상이 저장되어 있는 위치에서 받아온다.
	Mat Image1 = imread("C:/University/major/ImageProcessing/Practice/image/Fig0230(a)(dental_xray).tif");
	Mat Image2 = imread("C:/University/major/ImageProcessing/Practice/image/Fig0230(b)(dental_xray_mask).tif");

	//화소값 AND 연산을 수행한다.
	Mat ANDImage;
	bitwise_and(Image1, Image2, ANDImage);

	//영상 출력
	imshow("xray", Image1);
	imshow("mask", Image2);
	imshow("result", ANDImage);

	waitKey(0);
	return 0;
}