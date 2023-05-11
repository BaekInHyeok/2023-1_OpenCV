//////////////////////////////////////////////////////////////
//                                                          //
//                  HW#2-1 : Pawer Law                      //
//                                                          //
//   �ۼ��� : 2020039096 ������		��¥:2023�� 4�� 4��     //
//                                                          //
//       ���� ���� :  ���� ������ �Է� ���� ��ȯ            //
//                                                          //
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>

using namespace cv;

void main() {
	//ó���� ������ ��ġ�� ��ο��� �о�´�.
	Mat srcimage = imread("C:/University/major/ImageProcessing/Practice/image/Fig0309(a)(washed_out_aerial_image).tif");
	Mat fImage;
	srcimage.convertTo(fImage, CV_32F);//���� �� ���� �� �浹�� �����ϱ� ���� float ������Ÿ������ ����

	/*���� ���� 3.0���� ����*/
	double power1 = 3.0;//���� �� 3.0
	Mat powImage1;
	pow(fImage, power1, powImage1);	// ����Ϳ� ��Ÿ���� ��⸦ ���� ������ ����
	normalize(powImage1, powImage1, 0, 1.0, NORM_MINMAX);	//0~1 ���̷� ����ȭ

	/*���� ���� 4.0���� ����*/
	double power2 = 4.0;//���� �� 4.0
	Mat powImage2;
	pow(fImage, power2, powImage2);	// ����Ϳ� ��Ÿ���� ��⸦ ���� ������ ����
	normalize(powImage2, powImage2, 0, 1.0, NORM_MINMAX);	//0~1 ���̷� ����ȭ

	/*���� ���� 5.0���� ����*/
	double power3 = 5.0;//���� �� 5.0
	Mat powImage3;
	pow(fImage, power3, powImage3);	// ����Ϳ� ��Ÿ���� ��⸦ ���� ������ ����
	normalize(powImage3, powImage3, 0, 1.0, NORM_MINMAX);	//0~1 ���̷� ����ȭ


	/*���� ���*/
	imshow("original", srcimage);
	imshow("gamma3.0", powImage1);
	imshow("gamma4.0", powImage2);
	imshow("gamma5.0", powImage3);

	waitKey(0);
}
