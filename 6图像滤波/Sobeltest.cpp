/*************************************************************************
    > File Name: Sobeltest.cpp
    > Author: jiang
    > Mail: 760021776@qq.com 
    > Created Time: 2018年11月01日 星期四 15时56分07秒
 ************************************************************************/

#include<iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int main()
{
	// Read input image
	cv::Mat image= cv::imread("/home/jiang/图片/test2.jpg",0);
	if (!image.data)
		return 0; 


	// Compute Sobel X derivative
	cv::Mat sobelX;
	cv::Sobel(image,  // input
		sobelX,    // output
		CV_8U,     // image type
		1, 0,      // kernel specification
		3,         // size of the square kernel 
		0.5,96); // scale and offset

    // Display the image
	cv::namedWindow("Sobel X Image");
	cv::imshow("Sobel X Image",sobelX);

	// Compute Sobel Y derivative
	cv::Mat sobelY;
	cv::Sobel(image,  // input
		sobelY,    // output
		CV_8U,     // image type
		0, 1,      // kernel specification
		3,         // size of the square kernel 
		0.4, 128); // scale and offset

    // Display the image
	cv::namedWindow("Sobel Y Image");
	cv::imshow("Sobel Y Image",sobelY);

	// Compute norm of Sobel
	cv::Sobel(image,sobelX,CV_16S,1,0);
	cv::Sobel(image,sobelY,CV_16S,0,1);
	cv::Mat sobel;
	//compute the L1 norm
	sobel= abs(sobelX)+abs(sobelY);

	double sobmin, sobmax;
	cv::minMaxLoc(sobel,&sobmin,&sobmax);
	std::cout << "sobel value range: " << sobmin << "  " << sobmax << std::endl;

	// Compute Sobel X derivative (7x7)
	cv::Sobel(image,sobelX,CV_8U,1,0,7,0.001,128);

    // Display the image
	cv::namedWindow("Sobel X Image (7x7)");
	cv::imshow("Sobel X Image (7x7)",sobelX);

	// Conversion to 8-bit image
	// sobelImage = -alpha*sobel + 255
	cv::Mat sobelImage;
	sobel.convertTo(sobelImage,CV_8U,-255./sobmax,255);

    // Display the image
	cv::namedWindow("Sobel Image");
	cv::imshow("Sobel Image",sobelImage);

/*	// Apply threshold to Sobel norm (low threshold value)
	cv::Mat sobelThresholded;
	cv::threshold(sobelImage, sobelThresholded, 220, 255, cv::THRESH_BINARY);

    // Display the image
	cv::namedWindow("Binary Sobel Image (low)");
	cv::imshow("Binary Sobel Image (low)",sobelThresholded);

	// Apply threshold to Sobel norm (high threshold value)
	cv::threshold(sobelImage, sobelThresholded, 150, 255, cv::THRESH_BINARY);

    // Display the image
	cv::namedWindow("Binary Sobel Image (high)");
	cv::imshow("Binary Sobel Image (high)",sobelThresholded);
*/	
	cv::waitKey(0);
	return 0;
}

void Sobel_Test(cv::Mat image,bool dirc,int size)
{
	cv::Mat sobel;
	if(dirc){             // 1 - 1,0  水平
		cv::Sobel(image,sobel,CV_8U,1,0,size,0.001,128);
	}
	else
		cv::Sobel(image,sobel,CV_8U,0,1,size,0.001,128);
}

