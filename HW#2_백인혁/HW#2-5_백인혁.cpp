//////////////////////////////////////////////////////////////
//                                                          //
//                HW#2-5 : Logic Operation                  //
//                                                          //
//   �ۼ��� : 2020039096 ������		��¥:2023�� 4�� 6��     //
//                                                          //
//     ���� ���� : �־��� �� ���� ���� �� ���� ����     //
//                                                          //
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
	//�� ���� ������ ������ ����Ǿ� �ִ� ��ġ���� �޾ƿ´�.
	Mat Image1 = imread("C:/University/major/ImageProcessing/Practice/image/Fig0230(a)(dental_xray).tif");
	Mat Image2 = imread("C:/University/major/ImageProcessing/Practice/image/Fig0230(b)(dental_xray_mask).tif");

	//ȭ�Ұ� AND ������ �����Ѵ�.
	Mat ANDImage;
	bitwise_and(Image1, Image2, ANDImage);

	//���� ���
	imshow("xray", Image1);
	imshow("mask", Image2);
	imshow("result", ANDImage);

	waitKey(0);
	return 0;
}