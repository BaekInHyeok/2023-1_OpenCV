//////////////////////////////////////////////////////////////
//                                                          //
//                 HW#3-3 : Noise Filtering                 //
//                                                          //
//   작성자 : 2020039096 백인혁		날짜:2023년 4월 28일    //
//                                                          //
//      문제 정의 : 솔트 앤 페퍼, 가우시안 노이즈 생성      //
//                  최적의 필터 방법 탐색                   //
//                                                          //
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	//경로에서 이미지를 그레이스케일로 가져오기
	Mat srcImage = imread("C:/University/major/ImageProcessing/Practice/image/lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	imshow("Original", srcImage);

	/*솔트 앤 페퍼 잡음 생성---------------------------------------------------------------------------------------*/
	Mat sANDp = imread("C:/University/major/ImageProcessing/Practice/image/lena.jpg", IMREAD_GRAYSCALE);
	if (sANDp.empty())
		return -1;

	Mat noise = Mat::zeros(sANDp.size(), sANDp.type());
	randu(noise, 0, 255);
	Mat black = noise < 30;
	Mat white = noise > 225;
	sANDp.setTo(255, white);
	sANDp.setTo(0, black);

	imshow("Salt&Pepper", sANDp);

	/*가우시안 잡음 생성-----------------------------------------------------------------------------*/
	int sttdev = 30;//표준편차

	Mat Gaussiannoise(srcImage.size(), CV_32SC1);
	randn(Gaussiannoise, 0, sttdev);

	Mat dst;
	add(srcImage, Gaussiannoise, dst, Mat(), CV_8U);
	imshow("GaussianNoise", dst);


	/*평균 필터(Mean Filter)---------------------------------------------------------------------*/

	Mat avgImage1;
	Mat avgImage2;

	blur(sANDp, avgImage1, Size(5, 5), Point(-1, 1));
	blur(dst, avgImage2, Size(5, 5), Point(-1, 1));
	imshow("S&P Mean", avgImage1);
	imshow("Gaussian Mean", avgImage2);

	/*가우시안 필터(Gaussian Filter)--------------------------------------------------------------------*/
	int size = 7;

	Mat Gaussian1;
	Mat Gaussian2;

	GaussianBlur(sANDp, Gaussian1, Size(size, size), 0.0);  // 가우시안 스무딩   sigmaX, sigmaY=0.0
	GaussianBlur(dst, Gaussian2, Size(size, size), 0.0);  // 가우시안 스무딩   sigmaX, sigmaY=0.0

	imshow("S&P GS", Gaussian1);
	imshow("Gaussian GS", Gaussian2);


	/*중간값 필터(Median Filter)------------------------------------------------------------------------*/
	
	Mat Median1;
	Mat Median2;

	medianBlur(sANDp, Median1, size);
	medianBlur(dst, Median2, size);

	imshow("S&P Median", Median1);
	imshow("Gaussian Median", Median2);

	waitKey();
	
	return 0;
}


