//////////////////////////////////////////////////////////////
//                                                          //
//   HW#2-4 : Enhancement Using Arithmetic Operation        //
//                                                          //
//   �ۼ��� : 2020039096 ������		��¥:2023�� 4�� 5��     //
//                                                          //
// ���� ���� : �־��� �� ����  ���� ���� ���� ���� ��     //
//             �������� ���̱� ���� ���� ����               //
//                                                          //
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(){
	//�� ������ ������ ����Ǿ� �ִ� ��ο��� grayscale�� �޾ƿ´�.
	Mat image1 = imread("C:/University/major/ImageProcessing/Practice/image/Fig0228(a)(angiography_mask_image).tif", IMREAD_GRAYSCALE);
	Mat image2 = imread("C:/University/major/ImageProcessing/Practice/image/Fig0228(b)(angiography_live_ image).tif", IMREAD_GRAYSCALE);

	//�� ���� �� �ϳ��� ���ٸ� ������ ���
	CV_Assert(!(image1.empty() || image2.empty()));

	//double alpha = 0.6, beta = 0.7;

	Mat sub_img = abs(image2 - image1);

	//���� ���� ����
	Mat invert_img = Scalar::all(255) - sub_img;

	Mat fImage;
	invert_img.convertTo(fImage, CV_32F);//���� �� ���� �� �浹�� �����ϱ� ���� float ������Ÿ������ ����

	/*���� ���� 5.0���� ����*/
	double power = 5.0;	//���� �� 5.0
	Mat powImage;
	pow(fImage, power, powImage);	// ����Ϳ� ��Ÿ���� ��⸦ ���� ������ ����
	normalize(powImage, powImage, 0, 1.0, NORM_MINMAX);	//0~1 ���̷� ����ȭ
	
	/*���� ���*/
	imshow("image1", image1), imshow("image2", image2);
	imshow("sub_img", sub_img);
	imshow("invert_img", invert_img);
	imshow("gamma_img", powImage);

	waitKey(0);
}