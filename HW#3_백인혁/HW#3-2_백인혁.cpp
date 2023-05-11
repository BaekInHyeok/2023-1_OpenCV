//////////////////////////////////////////////////////////////
//                                                          //
//           HW#3-2 : Gaussian Smoothing Fliter             //
//                                                          //
//   �ۼ��� : 2020039096 ������		��¥:2023�� 4�� 27��    //
//                                                          //
//           ���� ���� : ����þ� ������ ���͸�             //
//      getGaussianKernel(), GaussianBlur() �Լ� ���       //
//                                                          //
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {

	//��ο��� �̹����� �׷��̽����Ϸ� �о����
	Mat srcImage = imread("C:/University/major/ImageProcessing/Practice/image/lena.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	imshow("Original", srcImage);

	int ksize = 0;//���� ������ ũ�⸦ �����ϴ� ����
	//getGaussianKernel()

	//���� ������ ũ�Ⱑ 5�� ��� - ����þ� Ŀ�� ���
	ksize = 5;

	Mat kx = getGaussianKernel(ksize, 0.0);	// 5 x 1 ����þ� Ŀ��
	Mat ky = getGaussianKernel(ksize, 0.0);	// 1 x 5 ����þ� Ŀ��
	Mat kxy = kx * ky.t();	// 5 x 5 2D ����þ� Ŀ�� ����

	Mat dstImage5x5;
	filter2D(srcImage, dstImage5x5, -1, kxy);
	imshow("5x5", dstImage5x5);

	//���� ������ ũ�Ⱑ 7�� ��� - ����þ� Ŀ�� ���
	ksize = 7;

	kx = getGaussianKernel(ksize, 0.0);	// 7 x 1 ����þ� Ŀ��
	ky = getGaussianKernel(ksize, 0.0);	// 1 x 7 ����þ� Ŀ��
	kxy = kx * ky.t();	// 7 x 7 2D ����þ� Ŀ�� ����

	Mat dstImage7x7;
	filter2D(srcImage, dstImage7x7, -1, kxy);
	imshow("7x7", dstImage7x7);

	//���� ������ ũ�Ⱑ 9�� ��� - ����þ� �� ���
	ksize = 9;

	Mat dstImage9x9;
	GaussianBlur(srcImage, dstImage9x9, Size(ksize, ksize), 0.0);  // ����þ� ������   sigmaX, sigmaY=0.0
	imshow("9x9", dstImage9x9);

	//���� ������ ũ�Ⱑ 11�� ��� - ����þ� �� ���
	ksize = 11;

	Mat dstImage11x11;
	GaussianBlur(srcImage, dstImage11x11, Size(ksize, ksize), 0.0);  // ����þ� ������   sigmaX, sigmaY=0.0
	imshow("11x11", dstImage11x11);

	waitKey();
}