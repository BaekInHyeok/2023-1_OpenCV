//////////////////////////////////////////////////////////////
//                                                          //
//				    HW#4-1 : Edge Detector		            //
//                                                          //
//   작성자 : 2020039096 백인혁		날짜 : 2023년 5월 2일   //
//                                                          //
//         문제 정의 : Sobel 연산자, Laplacian 연산자,      //
//    Marr-Hildreth 에지 검출 알고리즘을 이용한 edge 검출   //
//															//
//////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void ZeroCrossing(Mat& src, Mat& dst, int threshold);  // 0 교차점 체크

int main() {
	//저장경로에서 이미지를 그레이스케일로 읽어오기
	Mat srcImage = imread("C:/University/major/ImageProcessing/Practice/image/HW4-1.jpg", IMREAD_GRAYSCALE);
	if (srcImage.empty())
		return -1;

	imshow("Original", srcImage);


	/*1. Sobel 연산자 사용-------------------------------------------------------------------------------*/

	int ksize = 3;
	int ddepth = CV_32F;	// 깊이에 대한 자료형 변경
	Mat dstGx, dstGy;

	//x 방향의 미분을 적용
	Sobel(srcImage, dstGx, ddepth, 1, 0, ksize);    // dx

	//y 방향의 미분을 적용
	Sobel(srcImage, dstGy, ddepth, 0, 1, ksize);	// dy

	int dtype = CV_8U;

	//x 방향 미분 적용에 대한 정규화 수행
	Mat dstImageGx;
	normalize(abs(dstGx), dstImageGx, 0, 255, NORM_MINMAX, dtype);    // |dstGx|
	imshow("dstImageGx", dstImageGx);

	//y 방향 미분 적용에 대한 정규화 수행
	Mat dstImageGy;
	normalize(abs(dstGy), dstImageGy, 0, 255, NORM_MINMAX, dtype);	// |dstGy|	
	imshow("dstImageGy", dstImageGy);

	//edge magnitude
	Mat dstMag;
	magnitude(dstGx, dstGy, dstMag);  // 단순화하면.. |dstGx| + |dstGy|

	//edge magnitude 완료한 값으로 정규화 수행
	Mat dstImageGxy;
	normalize(dstMag, dstImageGxy, 0, 255, NORM_MINMAX, dtype);
	imshow("SobelResult", dstImageGxy);


	/*2.Laplacian 연산자 사용-------------------------------------------------------------------------------*/

	ksize = 15;
	Mat blurImage;
	GaussianBlur(srcImage, blurImage, Size(ksize, ksize), 0.0);  // srcImage를 15 x 15의 가우시안 필터로 스무딩

	Mat lapImage;
	Laplacian(blurImage, lapImage, CV_32F, ksize);  // 가우시안 스무딩 된 영상에 대해 라플라시안 필터링 수행

	Mat lapResult;
	ZeroCrossing(lapImage, lapResult, 10);  // 라플라시안 결과에 대해 영교차점 체크

	imshow("LaplacianResult", lapResult);

	/*3.Marr-Hildreth 에지 검출 알고리즘(LOG 사용)--------------------------------------------------------------*/
	// 윈도우 커널의 크기 n = 2 x 3 x sigma + 1 또는  sigma = 0.3(n/2 - 1)+0.8로 계산

	const int ksizeLOG = 9;
	float logArr[ksizeLOG * ksizeLOG];
	int   s, t, k = 0;
	float g;
	float sigma = 1.4f;
	//float sigma= 0.3f*(ksizeLOG/2-1.0f) + 0.8f;

	for (s = -ksizeLOG / 2; s <= ksizeLOG / 2; s++)   // ksizeLOG x ksizeLOG 크기의 LoG 필터 커널 생성
	{
		for (t = -ksizeLOG / 2; t <= ksizeLOG / 2; t++)
		{
			g = exp(-((float)s * s + (float)t * t) / (2 * sigma * sigma));
			g *= (1 - ((float)s * s + (float)t * t) / (2 * sigma * sigma));
			g /= (3.141592f * sigma * sigma * sigma * sigma);
			logArr[k++] = -g;
		}
	}

	Mat logKernel(ksizeLOG, ksizeLOG, CV_32F, logArr);
	cout << "logKernel=" << logKernel << endl;

	Mat logImage;
	filter2D(srcImage, logImage, CV_32F, logKernel);  // LoG 필터링

	Mat logResult;
	ZeroCrossing(logImage, logResult, 0);  // 0 교차점 검출
	imshow("LogResult", logResult);

	waitKey();
	return 0;
}

// 라플라시안 필터링된 입력 영상 src에서 가로방향과 세로 방향의 이웃을 조사하여 부호가 변경되는 0-교차 위치를 검출하고
// 변경되는 차이를 절대값으로 저장한 다음, threshold 함수로 임계값 이상의 큰 값으로 부호가 변경되는 위치를 에지로 dst 영상에 반영

void ZeroCrossing(Mat& src, Mat& dst, int th)
{
	int x, y;
	double a, b;

	Mat zeroCrossH(src.size(), CV_32F, Scalar::all(0));  // 가로 방향의 0-교차 검출
	// src와 동일한 크기의, CV_32F의 자료형에 0으로 초기화된 행렬 생성

	Mat_<float> _src(src);	// src를 복사하여 _src 생성

	for (x = 1; x < src.rows - 1; x++)
	{
		for (y = 1; y < src.cols - 1; y++)
		{

			// (+.-), (-,+), (+,0,-), (-,0,+) 인 경우를 검출하여 교차하는 정도를 zeroCrossH에 저장

			a = _src(x, y);     		// 가로 방향의 인접한 두 픽셀 선택
			b = _src(x, y + 1);

			if (a == 0)   			// 해당 픽셀의 값이 0 이면 그 왼쪽의 픽셀을 다시 선택.
				// (+,0,-) 또는 (-,0,+)인 경우를 검출하기 위함
				a = _src(x, y - 1);

			if (a * b < 0)			// 가로 방향의 인접한 두 픽셀의 부호가 다르다면
				// 두 픽셀의 절대값의 합을 저장
				zeroCrossH.at<float>(x, y) = fabs(a) + fabs(b);

			else				// 가로 방향의 인접한 두 픽셀의 부호가 같으면 0 저장
				zeroCrossH.at<float>(x, y) = 0;

		}
	}

	Mat zeroCrossV(src.size(), CV_32F, Scalar::all(0));  // 세로 방향의 0-교차 검출
	for (x = 1; x < src.rows - 1; x++)
	{
		for (y = 1; y < src.cols - 1; y++)
		{
			a = _src(x, y);
			b = _src(x + 1, y);

			if (a == 0)
				a = _src(x - 1, y);

			if (a * b < 0)
				zeroCrossV.at<float>(x, y) = fabs(a) + fabs(b);
			else
				zeroCrossV.at<float>(x, y) = 0;
		}
	}

	Mat zeroCross(src.size(), CV_32F, Scalar::all(0));

	add(zeroCrossH, zeroCrossV, zeroCross);  // zeroCross = zeroCrossH + zeroCrossV

	threshold(zeroCross, dst, th, 255, THRESH_BINARY);
}

