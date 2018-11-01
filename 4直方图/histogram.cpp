/*************************************************************************
    > File Name: histogram.cpp
    > Author: jiang
    > Mail: 760021776@qq.com 
    > Created Time: 2018年10月31日 星期三 17时17分47秒
 ************************************************************************/

#include<iostream>
#include <opencv2/opencv.hpp>
using namespace std;

/*
	 柱状图显示
*/
    // Create an image representing a histogram
static cv::Mat getImageOfHistogram(cv::Mat image) 
{
	const int D_1 = 1;
        cv::Mat hist;
#if D_1	
	int dims = 1;
        const int channels[1] = { 0 };  
        const int hSize[1] = { 256 };  
        float hranges[2] = { 0, 255 };  
        const float* ranges[1] = { hranges };
#endif
#if !D_1
 	int dims = 3;
        const int channels[3] = { 0,1,2 };  
        const int hSize[3] = { 256,256,256 };  
        float hranges[2] = { 0, 255 };  
        const float* ranges[3] = { hranges,hranges,hranges };
#endif       

	// Compute 1D histogram with calcHist
        cv::calcHist(&image, 
                1,                      // histogram of 1 image only
                channels,       // the channel used
                cv::Mat(),      // no mask is used
                hist,           // the resulting histogram
                dims,                      // it is a 1D histogram
                hSize,       // number of bins
                ranges          // pixel value range
        );
           


        // Get min and max bin values
        double maxVal = 0;
        double minVal = 0;
        cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
	
        // get histogram size
        int histSize = hist.rows;

	int all_wid = hist.cols;
	int zoom = 1;

        // Square image on which to display histogram
        cv::Mat histImg(histSize, histSize, CV_8U, cv::Scalar(255));

        // set highest point at 90% of nbins (i.e. image height)
        int hpt =static_cast<int>(0.9*histSize);

        // Draw vertical line for each bin
        for (int h = 0; h < histSize; h++) {
	    
	    

            float binVal = hist.at<float>(h);
            if (binVal>0) {
                int intensity = static_cast<int>(binVal*hpt / maxVal);
                cv::line(histImg, cv::Point(h*zoom, histSize*zoom),
                    	 cv::Point(h*zoom, (histSize - intensity)*zoom), cv::Scalar(0), zoom);
            }
        }

        return histImg;
}

cv::Mat getHistogram(cv::Mat image) 
{

	cv::Mat hist;

	const int channels[1] = { 0 }; 
	const int histSize[1] = { 256 }; 
	float hranges[2] = { 0, 255 }; 
	const float* ranges[1] = { hranges };

	// Compute 1D histogram with calcHist
	cv::calcHist(&image, 
		1,			// histogram of 1 image only
		channels,	// the channel used
		cv::Mat(),	// no mask is used
		hist,		// the resulting histogram
		1,			// it is a 1D histogram
		histSize,	// number of bins
		ranges		// pixel value range
	);
	return hist;
}

int main()
{
	cv::Mat image = cv::imread("/home/jiang/图片/grassland.jpg",0);
	if(image.empty()){
             cout << "load1 err"<<endl;
             return 0;
        }
	cv::Mat h = getImageOfHistogram(image); 	
	cv::imshow("hist",h);
	cv::imshow("image",image);
	
	cv::Mat thre;
	threshold(image,thre,190,255,cv::THRESH_BINARY);
	cv::imshow("result",thre);
	
	cv::waitKey(0);
	return 0;
}	
