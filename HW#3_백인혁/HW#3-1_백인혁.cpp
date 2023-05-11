//////////////////////////////////////////////////////////////
//                                                          //
//                HW#3-1 : Convolution                      //
//                                                          //
//   �ۼ��� : 2020039096 ������		��¥:2023�� 4�� 26��    //
//                                                          //
//           ���� ���� : ���� ���� �������               //
//    (�ڽ�, ����þ�, ������, ������, ��������, ���)    //
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

	//�����ο��� �̹����� �׷��̽����Ϸ� �о����
	Mat srcImage= imread("C:/University/major/ImageProcessing/Practice/image/lena.jpg",IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	imshow("Original", srcImage);

	/*�� ����ũ���� ����� ��������� ������ ������� ���*/
	
	//�ڽ� ����ũ
	Mat Box = (Mat_<float>(3, 3) << 
		1. / 9., 1. / 9., 1. / 9.,
		1. / 9., 1. / 9., 1. / 9.,
		1. / 9., 1. / 9., 1. / 9.);

	filter2D(srcImage, boxImage, -1, Box);
	imshow("BoxImage",boxImage);

	//����þ� ����ũ
	Mat Gaussian = (Mat_<float>(5,5) <<
		0.0000, 0.0000, 0.0002, 0.0000, 0.0000,
		0.0000, 0.0113, 0.0837, 0.0113, 0.0000,
		0.0002, 0.0837, 0.6187, 0.0837, 0.0002,
		0.0000, 0.0113, 0.0837, 0.0113, 0.0000,
		0.0000, 0.0000, 0.0002, 0.0000, 0.0000);

	filter2D(srcImage, gaussianImage, -1, Gaussian);
	imshow("GaussianImage", gaussianImage);

	//������ ����ũ
	Mat Sharpening = (Mat_<float>(3, 3) <<
		0., -1., 0.,
		-1., 5., -1.,
		0., -1., 0.);

	filter2D(srcImage, sharpImage, -1, Sharpening);
	imshow("SharpeningImage", sharpImage);

	//���� ���� ����ũ
	Mat HorizonEdge = (Mat_<float>(3, 3) <<
		1., 1., 1.,
		0., 0., 0.,
		-1., -1., -1.);

	filter2D(srcImage, hEdgeImage, -1, HorizonEdge);
	imshow("HorizonEdgeImage", hEdgeImage);

	//���� ���� ����ũ
	Mat VerticalEdge = (Mat_<float>(3, 3) <<
		1., 0., -1.,
		1., 0., -1.,
		1., 0., -1.);

	filter2D(srcImage, vEdgeImage, -1, VerticalEdge);
	imshow("VerticalEdgeImage", vEdgeImage);

	//��� ����ũ
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