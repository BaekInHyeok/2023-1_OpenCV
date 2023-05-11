//////////////////////////////////////////////////////////////
//                                                          //
//                  HW#2-1 : Pawer Law                      //
//                                                          //
//   작성자 : 2020039096 백인혁		날짜:2023년 4월 4일     //
//                                                          //
//       문제 정의 :  감마 조절로 입력 영상 변환            //
//                                                          //
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>

using namespace cv;

void main() {
	//처리할 영상을 위치한 경로에서 읽어온다.
	Mat srcimage = imread("C:/University/major/ImageProcessing/Practice/image/Fig0309(a)(washed_out_aerial_image).tif");
	Mat fImage;
	srcimage.convertTo(fImage, CV_32F);//감마 값 변경 시 충돌을 방지하기 위해 float 데이터타입으로 변경

	/*감마 값을 3.0으로 설정*/
	double power1 = 3.0;//감마 값 3.0
	Mat powImage1;
	pow(fImage, power1, powImage1);	// 모니터에 나타나는 밝기를 감마 값으로 조절
	normalize(powImage1, powImage1, 0, 1.0, NORM_MINMAX);	//0~1 사이로 정규화

	/*감마 값을 4.0으로 설정*/
	double power2 = 4.0;//감마 값 4.0
	Mat powImage2;
	pow(fImage, power2, powImage2);	// 모니터에 나타나는 밝기를 감마 값으로 조절
	normalize(powImage2, powImage2, 0, 1.0, NORM_MINMAX);	//0~1 사이로 정규화

	/*감마 값을 5.0으로 설정*/
	double power3 = 5.0;//감마 값 5.0
	Mat powImage3;
	pow(fImage, power3, powImage3);	// 모니터에 나타나는 밝기를 감마 값으로 조절
	normalize(powImage3, powImage3, 0, 1.0, NORM_MINMAX);	//0~1 사이로 정규화


	/*영상 출력*/
	imshow("original", srcimage);
	imshow("gamma3.0", powImage1);
	imshow("gamma4.0", powImage2);
	imshow("gamma5.0", powImage3);

	waitKey(0);
}
