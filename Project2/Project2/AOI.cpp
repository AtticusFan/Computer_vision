#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"


int const max_value = 255;
int const max_binary_value = 255;
Mat removeLight(Mat img, Mat pattern, int method) 
{
	Mat aux;
	if (method == 1)
	{
		Mat img32, pattern32;
		img.convertTo(img32, CV_32F);
		pattern.convertTo(pattern32, CV_32F);
		aux = 1 - (img32 / pattern32);
		aux = aux * 255;
		aux.convertTo(aux, CV_8U);
	}
	else
	{
		aux = pattern - img;
	}
	return aux;
}


int main(int argc, const char** argv)
{

	Mat Noise_obj = imread("noise.png");
	Mat Light = imread("light.jpg");
	namedWindow("1.Object with noise");
	imshow("1.Object with noise", Noise_obj);

	Mat rm_Noise;
	medianBlur(Noise_obj, rm_Noise, 5);
	namedWindow("2.Remove Noise");
	imshow("2.Remove Noise", rm_Noise);

	Mat Thresh_Res;
	threshold(rm_Noise, Thresh_Res, 1 < 0, 255, THRESH_BINARY_INV);
	namedWindow("3.Thresholding result");
	imshow("3.Thresholding result", Thresh_Res);

	Mat rm_Light_Sub;
	rm_Light_Sub = removeLight(rm_Noise, Light, 2);
	namedWindow("4.No light subtraction result");
	imshow("4.No light subtraction result", rm_Light_Sub);
	
	Mat rm_Light_Div;
	rm_Light_Div = removeLight(rm_Noise, Light, 1);
	namedWindow("5.No light division result");
	imshow("5.No light division result", rm_Light_Div);

	Mat Thres_Res_rmlight;
	threshold(rm_Light_Sub, Thres_Res_rmlight, 30, 255, THRESH_BINARY);
	namedWindow("6.Thresholding no light subtraction result");
	imshow("6.Thresholding no light subtraction result", Thres_Res_rmlight);
	
	Mat Thres_Res_rmlight_div;
	threshold(rm_Light_Div, Thres_Res_rmlight_div, 30, 255, THRESH_BINARY);
	namedWindow("7.Thresholding no light division result");
	imshow("7.Thresholding no light division result", Thres_Res_rmlight_div);
	
	waitKey();
	destroyAllWindows();
	return 0;
}