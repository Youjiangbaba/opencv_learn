/*************************************************************************
    > File Name: Color_Process.cpp
    > Author: jiang
    > Mail: 760021776@qq.com 
    > Created Time: 2018年10月31日 星期三 14时13分29秒
 ************************************************************************/

#include<iostream>
#include <opencv2/opencv.hpp>
using namespace std;
void color_part(cv::Mat image)
{
	cv::floodFill(image,            // input/ouput image
			cv::Point(239, 311),         // seed point
			cv::Scalar(255, 255, 255),  // repainted color
			(cv::Rect*)0,  // bounding rectangle of the repainted pixel set
			cv::Scalar(150, 60, 80),     // low and high difference threshold
			cv::Scalar(150, 60, 80),     // most of the time will be identical
			cv::FLOODFILL_FIXED_RANGE); // pixels are compared to seed color
	
}

void test_grabcut(cv::Mat image)
{

	// define bounding rectangle 
	cv::Rect rectangle(220,118,260,350);
	// the models (internally used)
	cv::Mat bgModel,fgModel; 
	// segmentation result
	cv::Mat result; // segmentation (4 possible values)

	// GrabCut segmentation
	cv::grabCut(image,    // input image
		result,   // segmentation result
		rectangle,// rectangle containing foreground 
		bgModel, fgModel, // models
		1,        // number of iterations
		cv::GC_INIT_WITH_RECT); // use rectangle

	// Get the pixels marked as likely foreground
	cv::compare(result,cv::GC_PR_FGD,result,cv::CMP_EQ);
	// or:
    //	result= result&1;

	// create a white image
	cv::Mat foreground(image.size(), CV_8UC3,
	          	       cv::Scalar(255, 255, 255));

	image.copyTo(foreground,result); // bg pixels not copied

	// draw rectangle on original image
	cv::rectangle(image, rectangle, cv::Scalar(255,255,255),1);
	cv::namedWindow("Image with rectangle");
	cv::imshow("Image with rectangle",image);

	// display result
	cv::namedWindow("Foreground object");
	cv::imshow("Foreground object",foreground);
}

/*
	肤色检测
*/
void detectHScolor(const cv::Mat& image,		// input image 
	double minHue, double maxHue,	// Hue interval 
	double minSat, double maxSat,	// saturation interval
	cv::Mat& mask) {				// output mask

	// convert into HSV space
	cv::Mat hsv;
	cv::cvtColor(image, hsv, CV_BGR2HSV);

//	cv::imshow("hsv",image);

	// split the 3 channels into 3 images
	std::vector<cv::Mat> channels;
	cv::split(hsv, channels);
	// channels[0] is the Hue
	// channels[1] is the Saturation
	// channels[2] is the Value

	// Hue masking
	cv::Mat mask1; // below maxHue
	cv::threshold(channels[0], mask1, maxHue, 255, cv::THRESH_BINARY_INV);
	cv::Mat mask2; // over minHue
	cv::threshold(channels[0], mask2, minHue, 255, cv::THRESH_BINARY);

	cv::Mat hueMask; // hue mask
	if (minHue < maxHue)
		hueMask = mask1 & mask2;
	else // if interval crosses the zero-degree axis
		hueMask = mask1 | mask2;

	// Saturation masking
	// below maxSat
	cv::threshold(channels[1], mask1, maxSat, 255, cv::THRESH_BINARY_INV);
	// over minSat
	cv::threshold(channels[1], mask2, minSat, 255, cv::THRESH_BINARY);

	cv::Mat satMask; // saturation mask
	satMask = mask1 & mask2;

	// combined mask
	mask = hueMask&satMask;
}


int main()
{
	cv::Mat image = cv::imread("/home/jiang/图片/nuture1.jpg");
	cv::Mat face = cv::imread("/home/jiang/图片/test2.jpg");
       if(face.empty()){
             cout << "load1 err"<<endl;
             return 0;
        } 
	if(image.empty()){
		cout << "load2 err"<<endl;
		return 0;
	}
//       cv::imshow(" 0",face);
//        test_grabcut(face);
	
	cv::Mat mask;
	detectHScolor(face,200,10,10,180,mask);
	cv::Mat detected(face.size(), CV_8UC3, cv::Scalar(0, 0, 0));
	face.copyTo(detected, mask);
	cv::imshow("Detection result",detected);

//	color_part(image);
//	cv::imshow(" 2",image);
	cv::waitKey(0);
	return 0;
}
