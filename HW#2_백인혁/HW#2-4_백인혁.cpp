//////////////////////////////////////////////////////////////
//                                                          //
//   HW#2-4 : Enhancement Using Arithmetic Operation        //
//                                                          //
//   작성자 : 2020039096 백인혁		날짜:2023년 4월 5일     //
//                                                          //
// 문제 정의 : 주어진 두 영상에  대한 뺄셈 연산 수행 후     //
//             가독성을 높이기 위한 보정 수행               //
//                                                          //
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(){
	//두 영상을 영상이 저장되어 있는 경로에서 grayscale로 받아온다.
	Mat image1 = imread("C:/University/major/ImageProcessing/Practice/image/Fig0228(a)(angiography_mask_image).tif", IMREAD_GRAYSCALE);
	Mat image2 = imread("C:/University/major/ImageProcessing/Practice/image/Fig0228(b)(angiography_live_ image).tif", IMREAD_GRAYSCALE);

	//두 영상 중 하나라도 없다면 에러를 출력
	CV_Assert(!(image1.empty() || image2.empty()));

	//double alpha = 0.6, beta = 0.7;

	Mat sub_img = abs(image2 - image1);

	//영상 반전 수행
	Mat invert_img = Scalar::all(255) - sub_img;

	Mat fImage;
	invert_img.convertTo(fImage, CV_32F);//감마 값 변경 시 충돌을 방지하기 위해 float 데이터타입으로 변경

	/*감마 값을 5.0으로 설정*/
	double power = 5.0;	//감마 값 5.0
	Mat powImage;
	pow(fImage, power, powImage);	// 모니터에 나타나는 밝기를 감마 값으로 조절
	normalize(powImage, powImage, 0, 1.0, NORM_MINMAX);	//0~1 사이로 정규화
	
	/*영상 출력*/
	imshow("image1", image1), imshow("image2", image2);
	imshow("sub_img", sub_img);
	imshow("invert_img", invert_img);
	imshow("gamma_img", powImage);

	waitKey(0);
}