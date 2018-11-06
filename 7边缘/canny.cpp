/*************************************************************************
    > File Name: canny.cpp
    > Author: jiang
    > Mail: 760021776@qq.com 
    > Created Time: 2018年11月05日 星期一 10时25分22秒
 ************************************************************************/

#include<iostream>
#include <opencv2/opencv.hpp>
#include "findlines.hpp"
using namespace std;

#define CANNY 1
#define HOUGHLINE 1
#define FINDCONTOURS 1

cv::Mat image,canny_img;
int thresh_low,thresh_high;

cv::Mat hough_line(cv::Mat contours);
cv::Mat findcontours(cv::Mat binary);


/*回调函数*/
void canny_track(int,void*)
{
	cv::Canny(image,canny_img,thresh_low,thresh_high);	
	cv::imshow("edge detection",canny_img);
#if HOUGHLINE
	
        cv::imshow("hough",hough_line(canny_img));  
#endif
#if FINDCONTOURS
	cv::imshow("findcontours",findcontours(canny_img));
#endif
}

/*find contours*/
cv::Mat findcontours(cv::Mat binary)
{
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(binary,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE);
	cv::Mat result(image.size(),CV_8U,cv::Scalar(255));
	cv::drawContours(result,contours,-1,0,2);
	return result;
}

/*hough变换*/
cv::Mat hough_line(cv::Mat contours)
{
	std::vector<cv::Vec2f> lines;
	cv::HoughLines(contours,lines,1,PI/90,200);

	// Draw the lines
	cv::Mat result(contours.rows,contours.cols,CV_8U,cv::Scalar(255,0,0));
	image.copyTo(result);
	std::vector<cv::Vec2f>::const_iterator it= lines.begin();
	while (it!=lines.end()) {

		float rho= (*it)[0];   // first element is distance rho
		float theta= (*it)[1]; // second element is angle theta
		
		if (theta < PI/4. || theta > 3.*PI/4.) { // ~vertical line
		
			// point of intersection of the line with first row
			cv::Point pt1(rho/cos(theta),0);        
			// point of intersection of the line with last row
			cv::Point pt2((rho-image.rows*sin(theta))/cos(theta),image.rows);
			// draw a white line
			cv::line(result, pt1, pt2, cv::Scalar(255), 1); 

		} else { // ~horizontal line

			// point of intersection of the line with first column
			cv::Point pt1(0,rho/sin(theta));        
			// point of intersection of the line with last column
			cv::Point pt2(image.cols,(rho-image.cols*cos(theta))/sin(theta));
			// draw a white line
			cv::line(result, pt1, pt2, cv::Scalar(255), 1); 
		}

//		std::cout << "line: (" << rho << "," << theta << ")\n"; 

		++it;
	}
	return result;
    // Display the detected line image
//	cv::imshow("hough_line",result);
}



int main()
{
	image = cv::imread("/home/jiang/图片/road2.jpg");
	cv::cvtColor(image,image,CV_BGR2GRAY);
	if(image.empty())
	{
		cout<<"open err1"<<endl;
		return 0;
	}
        cv::imshow("image_gray",image);
	
//        cv::Canny(image,canny_img,255,600);    
//        cv::imshow("edge",canny_img);
//       cv::imshow("hough",hough_line(canny_img));  

 	cv::namedWindow("hough",cv::WINDOW_NORMAL);
	cv::namedWindow("findcontours",cv::WINDOW_NORMAL);

#if CANNY
	cv::namedWindow("edge detection",cv::WINDOW_NORMAL);
	thresh_low = 255;
	thresh_high = 500;
	//创建一个滑动条，名字为Low:255，主窗口为edge detection，最大值为255，value为thresh_low，回调函数为canny_track
	cv::createTrackbar("Low: 500", "edge detection", &thresh_low, 500, canny_track);
	cv::createTrackbar("High: 800", "edge detection", &thresh_high, 800, canny_track);
	cv::imshow("edge detection",image);
#endif

#if HOUGHLINE
//	hough_line(canny_img);	
#endif
	cv::waitKey(0);
	return 0;
}

