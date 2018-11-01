/*************************************************************************
    > File Name: rand_noise.cpp
    > Author: jiang
    > Mail: 760021776@qq.com 
    > Created Time: 2018年10月30日 星期二 15时25分41秒
 ************************************************************************/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
   
using namespace std;
using namespace cv;

#define NOISE  0
#define REDUCE 0

/*
    image : in img
    n  :   numbers of noise 
*/
void salt_pepper_noise(Mat image,int n)
{
	//C++11 random
	default_random_engine generator;
	uniform_int_distribution<int> randomRaw(0,image.rows-1);
 	uniform_int_distribution<int> randomCol(0,image.cols-1);
	
	int i,j;
	
	for(int k = 0;k < n;k ++){
	  //locatin of random img
		i = randomCol(generator);
		j = randomRaw(generator);
		if(image.type()== CV_8UC1){          //Gray
			
			image.at<uchar>(j,i) = 255;
		}
		else if(image.type() == CV_8UC3)     //BGR
		{
			image.at<Vec3b>(j,i)[0] = 255;	
			image.at<Vec3b>(j,i)[1] = 255;
			image.at<Vec3b>(j,i)[2] = 255;
		}	
	}
}

/*
 减色运算 
*/
void colorReduce(Mat &image,Mat &result,int div)
{
	result.create(image.rows,image.cols,image.type());

	int nl = image.rows;
	int nc = image.cols;
	int nchannels = image.channels();
	
	for(int j = 0;j < nl;j ++){
		uchar *data_in = image.ptr<uchar>(j);  //取得行j的地址
	 	uchar *data_out = result.ptr<uchar>(j); 
	
		for(int i = 0;i < nc*nchannels;i ++){
			data_out[i] = data_in[i]/div*div + div/2;
		}
	}
}


/*
 	图像锐化
*/
void sharpen(const cv::Mat &image, cv::Mat &result) {

	result.create(image.size(), image.type()); // allocate if necessary
	int nchannels= image.channels();

	for (int j= 1; j<image.rows-1; j++) { // for all rows (except first and last)

		const uchar* previous= image.ptr<const uchar>(j-1); // previous row
		const uchar* current= image.ptr<const uchar>(j);	// current row
		const uchar* next= image.ptr<const uchar>(j+1);		// next row

		uchar* output= result.ptr<uchar>(j);	// output row

		for (int i=nchannels; i<(image.cols-1)*nchannels; i++) {

			// apply sharpening operator
			*output++= cv::saturate_cast<uchar>(5*current[i]-current[i-nchannels]-current[i+nchannels]-previous[i]-next[i]); 
		}
	}

	// Set the unprocess pixels to 0
	result.row(0).setTo(cv::Scalar(0));
	result.row(result.rows-1).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
	result.col(result.cols-1).setTo(cv::Scalar(0));
}
// using kernel
void sharpen2D(const cv::Mat &image, cv::Mat &result) {

	// Construct kernel (all entries initialized to 0)
	cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));
	// assigns kernel values
	kernel.at<float>(1,1)= 5.0;
	kernel.at<float>(0,1)= -1.0;
	kernel.at<float>(2,1)= -1.0;
	kernel.at<float>(1,0)= -1.0;
	kernel.at<float>(1,2)= -1.0;

	//filter the image
	cv::filter2D(image,result,image.depth(),kernel);
}


/*
   行 正弦波浪化
*/
void wave(const cv::Mat &image, cv::Mat &result) {

	// the map functions
	cv::Mat srcX(image.rows,image.cols,CV_32F); // x-map
	cv::Mat srcY(image.rows,image.cols,CV_32F); // y-map

	// creating the mapping
	for (int i=0; i<image.rows; i++) {
		for (int j=0; j<image.cols; j++) {

			srcX.at<float>(i,j)= j;
			srcY.at<float>(i,j)= i+3*sin(j/6.0);

			// horizontal flipping
			// srcX.at<float>(i,j)= image.cols-j-1;
			// srcY.at<float>(i,j)= i;
		}
	}

	// applying the mapping
	cv::remap(image,  // source image
		      result, // destination image
			  srcX,   // x map
			  srcY,   // y map
			  cv::INTER_LINEAR); // interpolation method
}


//main
int main()
{
	Mat background = imread("/home/jiang/图片/background1.jpeg");
	Mat image = imread("/home/jiang/图片/nuture1.jpg");
	if (!image.data){
		cout << "open err1 "<<endl;
		return 0;
	}
	if (!background.data){
              cout << "open err2 "<<endl;
	     return 0;
	}
	Mat image0,result,re;
#if REDUCE	
	colorReduce(image,image0,64);
        imshow("__",image0);
#endif
#if NOISE
	salt_pepper_noise(image,2000);
#endif
	resize(background,background,Size(image.cols, image.rows),0,0,INTER_LINEAR);
	result = 0.7*image + 0.9*background;
        //addWeighted(image,0.7,background,0.9,50,re);
	wave(result,re);
	imshow("--",re);
	imshow("result",result);
	waitKey(0);
	return 0;
}
