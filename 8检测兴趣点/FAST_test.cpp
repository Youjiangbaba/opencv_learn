/*************************************************************************
    > File Name: FAST_test.cpp
    > Author: jiang
    > Mail: 760021776@qq.com 
    > Created Time: 2018年11月06日 星期二 11时12分06秒
 ************************************************************************/

#include<iostream>
#include <opencv2/opencv.hpp>

#include "track.hpp"

using namespace std;
int range;
cv::Mat image;
func_track track;

void track_back(int,void*)
{
	track.FAST_BACK(image);
	track.SURF_BACK(image);
/*	cv::Mat result(image.rows,image.cols,CV_8UC3);
	image.copyTo(result);

	vector<cv::KeyPoint> keypoints;
        cv::FastFeatureDetector ptrFAST(range);
        ptrFAST.detect(image,keypoints);

        cv::drawKeypoints(result,keypoints,result,cv::Scalar::all(-1),cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);
	keypoints.clear();
	cv::imshow("image",result);	
*/
}


int main()
{
	image = cv::imread("/home/jiang/图片/church1.jpeg");
	if(!image.data)
	{
		cout << "open err1" <<endl;
		return 0;
	}
	//cv::resize(image,image,cv::Size(),0.5,0.5,cv::INTER_LINEAR);
	cv::imshow("o",image);


//	cv::initModule_nonfree();             //if use SIFT or SURF

/*	cv::Ptr<cv::FastFeatureDetector> ptrFAST = cv::FastFeatureDetector::create("FAST");
	if(ptrFAST.empty())
	{
		cout << "failed to create ptrFAST"<< endl;
	//	return 0;
	}
	ptrFAST -> detect(image,keypoints);
*/	
//	cv::drawKeypoints(image,keypoints,image,cv::Scalar::all(-1),cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);
/*	cv::namedWindow("FAST",CV_WINDOW_NORMAL);
	track.FASTrange = 10;
	//创建一个滑动条，名字为Low:255，主窗口为edge detection，最大值为255，value为thresh_low，回调函数为canny_track
	cv::createTrackbar("range: 255", "image", &range, 255, track_back);
	cv::imshow("image",image);
*/
	track.track_fast();
	track.track_surf();
	cv::waitKey(0);
	return 0;
}

