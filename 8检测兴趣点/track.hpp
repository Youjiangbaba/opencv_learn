/*************************************************************************
    > File Name: track.hpp
    > Author: jiang
    > Mail: 760021776@qq.com 
    > Created Time: 2018年11月06日 星期二 14时35分07秒
 ************************************************************************/

#include<iostream>
#include <opencv2/opencv.hpp>

#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>

using namespace std;

void track_back(int,void*);
class func_track
{
private:
	cv::Mat FAST_img;
	cv::Mat SURF_img;
	cv::Mat ORB_img;
	vector<cv::KeyPoint> FASTkeypoints;
        vector<cv::KeyPoint> SURFkeypoints;
        vector<cv::KeyPoint> ORBkeypoints;
	int FASTrange;
	int SURFrange;
	int ORBrange;
	int last_fast,last_surf,last_orb;

//	void track_back(int,void*);


public:
	void FAST_BACK(cv::Mat image){
		if(last_fast != FASTrange)
		{
			cv::Mat result(image.rows,image.cols,CV_8UC3);
			image.copyTo(result);
			cv::FastFeatureDetector ptrFAST(FASTrange);
			ptrFAST.detect(image,FASTkeypoints);
			cv::drawKeypoints(result,FASTkeypoints,result,cv::Scalar::all(-1),cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);
			FASTkeypoints.clear();
			cv::imshow("FAST",result);
			last_fast = FASTrange;
		}
	}

	void SURF_BACK(cv::Mat image){
		if(last_surf != SURFrange){
			cv::Mat result(image.rows,image.cols,CV_8UC3);
			image.copyTo(result);
		        cv::SurfFeatureDetector ptrSURF(SURFrange);
		        ptrSURF.detect(image,SURFkeypoints);
		        cv::drawKeypoints(result,SURFkeypoints,result,cv::Scalar::all(-1),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		        SURFkeypoints.clear();
			last_surf = SURFrange;
	   		cv::imshow("SURF",result);
		}
	
        }
	void track_fast(){
		last_fast = 0;
		FASTrange = 10;
		cv::namedWindow("FAST",CV_WINDOW_NORMAL);
		//创建一个滑动条，名字为Low:255，主窗口为edge detection，最大值为255，value为thresh_low，回调函数为canny_track
		cv::createTrackbar("FASTrange: 255", "FAST", &FASTrange, 255, track_back);
	}
	void track_surf(){
		last_surf = 0;
		SURFrange = 10;
		cv::namedWindow("SURF",CV_WINDOW_NORMAL);
		//创建一个滑动条，名字为Low:255，主窗口为edge detection，最大值为255，value为thresh_low，回调函数为canny_track
		cv::createTrackbar("SURFrange: 255", "SURF", &SURFrange, 255, track_back);
	}
};
