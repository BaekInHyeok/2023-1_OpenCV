//////////////////////////////////////////////////////////////
//                                                          //
//				    HW#4-2 : �밢�� ����		            //
//                                                          //
//   �ۼ��� : 2020039096 ������		��¥ : 2023�� 5�� 3��   //
//                                                          //
//         ���� ���� : Sobel �����ڸ� �����Ͽ� ������       //
//		  ����ũ�� ����� 45��, -45�� �밢�� edge ����		//
//															//
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	//�����ο��� �̹����� �׷��̽����Ϸ� �о����
	Mat srcImage = imread("C:/University/major/ImageProcessing/Practice/image/HW4-2.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	//������ ũ�Ⱑ Ŀ ũ�⸦ 0.5��� ����ϴ� ������ ��������
	Size newSize(srcImage.cols * 0.5, srcImage.rows * 0.5);
	Mat resized;
	resize(srcImage, resized, newSize);
	imshow("Resized Image", resized);
	
	//����þ� ���͸� �������� edge ���� ����� ���̸� �˾ƺ����� ��
	Mat blurred;
	GaussianBlur(resized, blurred, Size(3, 3), 0);
	imshow("Blurred Image", blurred);

	/*45��, -45�� ���� ������ ���� ������ Sobel Ŀ�� ����ũ*/

	/*Option 1*/
	/*
	//45��
	Mat kernel45 = (Mat_<float>(3, 3) << 
		0, 1, 2,
		-1, 0, 1,
		-2, -1, 0);

	//-45��
	Mat kernel_45 = (Mat_<float>(3, 3) << 
		-2, -1, 0,
		-1, 0, 1,
		0, 1, 2);
	*/

	/*Option 2*/

	//45��
	Mat kernel45 = (Mat_<float>(3, 3) <<
		-1, -1, 2,
		-1, 2, -1,
		2, -1, -1);

	//-45��
	Mat kernel_45 = (Mat_<float>(3, 3) <<
		2, -1, -1,
		-1, 2, -1,
		-1, -1, 2);
		
	//�Ӱ谪 ����
	int thPoint = 50;


	/*Resized Image�� ���� Sobel ���� -----------------------------------------------------*/

	//���� 45��, -45�� sobel Ŀ�� ����ũ ����
	Mat grad45, grad_45;
	filter2D(resized, grad45, CV_32F, kernel45);
	filter2D(resized, grad_45, CV_32F, kernel_45);

	// 45��, -45�� ������ �����ϴ� ����ȭ
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



	/*Blurred Image�� ���� Sobel ���� -------------------------------------------------*/

	//����þ� ���� ���� ���� 45��, -45�� sobel Ŀ�� ����ũ ����
	Mat grad45_b, grad_45_b;
	filter2D(blurred, grad45_b, CV_32F, kernel45);
	filter2D(blurred, grad_45_b, CV_32F, kernel_45);

	// 45��, -45�� ������ �����ϴ� ����ȭ
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