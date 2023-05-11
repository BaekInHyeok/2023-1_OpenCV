//////////////////////////////////////////////////////////////
//                                                          //
//				    HW#4-2 : 대각선 검출		            //
//                                                          //
//   작성자 : 2020039096 백인혁		날짜 : 2023년 5월 3일   //
//                                                          //
//         문제 정의 : Sobel 연산자를 변형하여 적절한       //
//		  마스크를 만들어 45도, -45도 대각선 edge 검출		//
//															//
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	//저장경로에서 이미지를 그레이스케일로 읽어오기
	Mat srcImage = imread("C:/University/major/ImageProcessing/Practice/image/HW4-2.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	//사진의 크기가 커 크기를 0.5배로 축소하는 연산을 수행했음
	Size newSize(srcImage.cols * 0.5, srcImage.rows * 0.5);
	Mat resized;
	resize(srcImage, resized, newSize);
	imshow("Resized Image", resized);
	
	//가우시안 필터를 적용했을 edge 검출 결과의 차이를 알아보고자 함
	Mat blurred;
	GaussianBlur(resized, blurred, Size(3, 3), 0);
	imshow("Blurred Image", blurred);

	/*45도, -45도 에지 검출을 위해 변형한 Sobel 커널 마스크*/

	/*Option 1*/
	/*
	//45도
	Mat kernel45 = (Mat_<float>(3, 3) << 
		0, 1, 2,
		-1, 0, 1,
		-2, -1, 0);

	//-45도
	Mat kernel_45 = (Mat_<float>(3, 3) << 
		-2, -1, 0,
		-1, 0, 1,
		0, 1, 2);
	*/

	/*Option 2*/

	//45도
	Mat kernel45 = (Mat_<float>(3, 3) <<
		-1, -1, 2,
		-1, 2, -1,
		2, -1, -1);

	//-45도
	Mat kernel_45 = (Mat_<float>(3, 3) <<
		2, -1, -1,
		-1, 2, -1,
		-1, -1, 2);
		
	//임계값 설정
	int thPoint = 50;


	/*Resized Image에 대한 Sobel 연산 -----------------------------------------------------*/

	//영상에 45도, -45도 sobel 커널 마스크 적용
	Mat grad45, grad_45;
	filter2D(resized, grad45, CV_32F, kernel45);
	filter2D(resized, grad_45, CV_32F, kernel_45);

	// 45도, -45도 에지를 검출하는 이진화
	Mat edges = Mat::zeros(grad45.size(), CV_8U);
	for (int i = 0; i < grad45.rows; i++)
	{
		for (int j = 0; j < grad45.cols; j++)
		{
			float g45 = grad45.at<float>(i, j);
			float g_45 = grad_45.at<float>(i, j);

			if (g45 > thPoint || g_45 > thPoint)
			{
				edges.at<uchar>(i, j) = 255;
			}
		}
	}
	imshow("Edges", edges);



	/*Blurred Image에 대한 Sobel 연산 -------------------------------------------------*/

	//가우시안 필터 적용 영상에 45도, -45도 sobel 커널 마스크 적용
	Mat grad45_b, grad_45_b;
	filter2D(blurred, grad45_b, CV_32F, kernel45);
	filter2D(blurred, grad_45_b, CV_32F, kernel_45);

	// 45도, -45도 에지를 검출하는 이진화
	Mat edges_b = Mat::zeros(grad45_b.size(), CV_8U);
	for (int i = 0; i < grad45_b.rows; i++)
	{
		for (int j = 0; j < grad45_b.cols; j++)
		{
			float g45_b = grad45_b.at<float>(i, j);
			float g_45_b = grad_45_b.at<float>(i, j);

			if (g45_b > thPoint || g_45_b > thPoint)
			{
				edges_b.at<uchar>(i, j) = 255;
			}
		}
	}
	imshow("Blurred_Edges", edges_b);

	waitKey();
	return 0;
}