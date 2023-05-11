//////////////////////////////////////////////////////////////
//                                                          //
//                HW#3-1 : Convolution                      //
//                                                          //
//   작성자 : 2020039096 백인혁		날짜:2023년 4월 26일    //
//                                                          //
//           문제 정의 : 영상에 대한 컨볼루션               //
//    (박스, 가우시안, 샤프닝, 수평에지, 수직에지, 모션)    //
//														    //
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat boxImage;
	Mat gaussianImage;
	Mat sharpImage;
	Mat hEdgeImage;
	Mat vEdgeImage;
	Mat motionImage;

	//저장경로에서 이미지를 그레이스케일로 읽어오기
	Mat srcImage= imread("C:/University/major/ImageProcessing/Practice/image/lena.jpg",IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	imshow("Original", srcImage);

	/*각 마스크들을 만들어 컨볼루션을 시행해 결과물을 출력*/
	
	//박스 마스크
	Mat Box = (Mat_<float>(3, 3) << 
		1. / 9., 1. / 9., 1. / 9.,
		1. / 9., 1. / 9., 1. / 9.,
		1. / 9., 1. / 9., 1. / 9.);

	filter2D(srcImage, boxImage, -1, Box);
	imshow("BoxImage",boxImage);

	//가우시안 마스크
	Mat Gaussian = (Mat_<float>(5,5) <<
		0.0000, 0.0000, 0.0002, 0.0000, 0.0000,
		0.0000, 0.0113, 0.0837, 0.0113, 0.0000,
		0.0002, 0.0837, 0.6187, 0.0837, 0.0002,
		0.0000, 0.0113, 0.0837, 0.0113, 0.0000,
		0.0000, 0.0000, 0.0002, 0.0000, 0.0000);

	filter2D(srcImage, gaussianImage, -1, Gaussian);
	imshow("GaussianImage", gaussianImage);

	//샤프닝 마스크
	Mat Sharpening = (Mat_<float>(3, 3) <<
		0., -1., 0.,
		-1., 5., -1.,
		0., -1., 0.);

	filter2D(srcImage, sharpImage, -1, Sharpening);
	imshow("SharpeningImage", sharpImage);

	//수평 에지 마스크
	Mat HorizonEdge = (Mat_<float>(3, 3) <<
		1., 1., 1.,
		0., 0., 0.,
		-1., -1., -1.);

	filter2D(srcImage, hEdgeImage, -1, HorizonEdge);
	imshow("HorizonEdgeImage", hEdgeImage);

	//수직 에지 마스크
	Mat VerticalEdge = (Mat_<float>(3, 3) <<
		1., 0., -1.,
		1., 0., -1.,
		1., 0., -1.);

	filter2D(srcImage, vEdgeImage, -1, VerticalEdge);
	imshow("VerticalEdgeImage", vEdgeImage);

	//모션 마스크
	Mat Motion = (Mat_<float>(5, 5) <<
		0.0304, 0.0501, 0.0000, 0.0000, 0.0000,
		0.0501, 0.1771, 0.0519, 0.0000, 0.0000,
		0.0000, 0.0519, 0.1771, 0.0519, 0.0002,
		0.0000, 0.0000, 0.0519, 0.1771, 0.0501,
		0.0000, 0.0000, 0.0000, 0.0501, 0.0304);

	filter2D(srcImage, motionImage, -1, Motion);
	imshow("Motion", motionImage);

	waitKey();
	return 0;
}