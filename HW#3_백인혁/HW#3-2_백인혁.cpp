//////////////////////////////////////////////////////////////
//                                                          //
//           HW#3-2 : Gaussian Smoothing Fliter             //
//                                                          //
//   작성자 : 2020039096 백인혁		날짜:2023년 4월 27일    //
//                                                          //
//           문제 정의 : 가우시안 스무딩 필터링             //
//      getGaussianKernel(), GaussianBlur() 함수 사용       //
//                                                          //
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {

	//경로에서 이미지를 그레이스케일로 읽어오기
	Mat srcImage = imread("C:/University/major/ImageProcessing/Practice/image/lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	imshow("Original", srcImage);

	int ksize = 0;//필터 윈도우 크기를 저장하는 변수
	//getGaussianKernel()

	//필터 윈도우 크기가 5인 경우 - 가우시안 커널 사용
	ksize = 5;

	Mat kx = getGaussianKernel(ksize, 0.0);	// 5 x 1 가우시안 커널
	Mat ky = getGaussianKernel(ksize, 0.0);	// 1 x 5 가우시안 커널
	Mat kxy = kx * ky.t();	// 5 x 5 2D 가우시안 커널 생성

	Mat dstImage5x5;
	filter2D(srcImage, dstImage5x5, -1, kxy);
	imshow("5x5", dstImage5x5);

	//필터 윈도우 크기가 7인 경우 - 가우시안 커널 사용
	ksize = 7;

	kx = getGaussianKernel(ksize, 0.0);	// 7 x 1 가우시안 커널
	ky = getGaussianKernel(ksize, 0.0);	// 1 x 7 가우시안 커널
	kxy = kx * ky.t();	// 7 x 7 2D 가우시안 커널 생성

	Mat dstImage7x7;
	filter2D(srcImage, dstImage7x7, -1, kxy);
	imshow("7x7", dstImage7x7);

	//필터 윈도우 크기가 9인 경우 - 가우시안 블러 사용
	ksize = 9;

	Mat dstImage9x9;
	GaussianBlur(srcImage, dstImage9x9, Size(ksize, ksize), 0.0);  // 가우시안 스무딩   sigmaX, sigmaY=0.0
	imshow("9x9", dstImage9x9);

	//필터 윈도우 크기가 11인 경우 - 가우시안 블러 사용
	ksize = 11;

	Mat dstImage11x11;
	GaussianBlur(srcImage, dstImage11x11, Size(ksize, ksize), 0.0);  // 가우시안 스무딩   sigmaX, sigmaY=0.0
	imshow("11x11", dstImage11x11);

	waitKey();
}