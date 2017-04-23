#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>   
#include <algorithm>  
using namespace cv;
using namespace std;

#include "medianFilter.cpp"
#include "threshold.cpp"
#include "morph_operations.cpp"
#include "contrast_stretching.cpp"
#include "connected_components.cpp"
#include "seed_growing.cpp"
int getMaxLabel(vector<int> label_count)
{
	int max = 0 ;
	int index = -1;
	for(int i = 0 ; i<label_count.size();i++)
	{
		if(label_count.at(i)>max)
		{
			max= label_count.at(i);
			index = i; 
		}
	}

	return index; 
}

void get_segmented_image(Mat& label_image, Mat& object_segmented_image)
{
	vector<int> labels ; 
    vector<int> label_count ; 
    for(int i = 0 ;i<label_image.rows;i++)
    {
    	for(int j = 0; j<label_image.cols;j++)
    	{
    		int flag = 0 ;
    		for(int k =0 ; k<labels.size();k++)
    		{
    			if(labels.at(k) == (int)label_image.at<uchar>(i,j))
    				{
    					label_count.at(k)++;
    					flag = 1; 
    					break;
    				}
    		}
    		if(flag == 0)
    		{
    			labels.push_back((int)label_image.at<uchar>(i,j)) ;
    			label_count.push_back(1); 
    		}	

    	}
    }
    // for(int i = 0 ; i<label_count.size();i++)
    // 	cout<<" Label "<<i << " = "<<label_count.at(i)<<endl;

    int object_label  = 1; 
     for(int i = 0 ;i<label_image.rows;i++)
    {
    	for(int j = 0; j<label_image.cols;j++)
    	{
    		if((int)label_image.at<uchar>(i,j) == labels.at(object_label))
    			object_segmented_image.at<uchar>(i,j) = 255;
    	}

    }

}
int main()
{
    Mat image = imread("../mini-MiasDatabase/all-mias/mdb004.pgm", CV_LOAD_IMAGE_GRAYSCALE	);   // Read the file
    cv::resize(image,image,Size(280,200));//resize image
	// std::cout<<image.channels()<<endl;
	// std::cout<<image.type()<<endl;

	int medianFilterSize = 5; 
	Mat medianFilteredImage = Mat::zeros(image.rows - medianFilterSize+1,image.cols- medianFilterSize+1,image.type());
    medianFiter(medianFilterSize, image, medianFilteredImage);	//no padding done



    int globalThreshold = 18 ; 
    Mat thresholdedImage;
    thresholding(medianFilteredImage,thresholdedImage,globalThreshold);
    imshow("thresholdedImage",thresholdedImage);
    cout<<"Connencted Components Running ..."<<endl;
    Mat label_image= Mat::zeros(image.rows,image.cols,CV_8UC1) ; 
    connectedComponents(thresholdedImage,label_image);
    Mat object_segmented_image= Mat::zeros(image.rows,image.cols,CV_8UC1) ; 
    get_segmented_image(label_image,object_segmented_image);

    Mat cleaned_image = Mat::zeros(object_segmented_image.rows,object_segmented_image.cols,object_segmented_image.type()) ;
  	clean(object_segmented_image, cleaned_image, 3);

  	Mat erodedImage= Mat::zeros(image.rows,image.cols,image.type()) ; 
	erosion(cleaned_image, erodedImage, 5);
	Mat dilatedImage= Mat::zeros(image.rows,image.cols,image.type()) ; 
	dilation(erodedImage,dilatedImage,5);
	Mat holeFilledImage = Mat::zeros(image.rows,image.cols,image.type()) ;
	holefill(dilatedImage,holeFilledImage,3);
	cout<<"Line 105"<<endl;
	Mat output_image = Mat::zeros(holeFilledImage.rows,holeFilledImage.cols,holeFilledImage.type()) ;
	int delta = 2 ;
	cout<<"cols= "<<output_image.cols<<endl;
	cout<<"rows= "<<output_image.rows<<endl;
	imshow("medianFilteredImage",medianFilteredImage);
	seeded_region_growing(medianFilteredImage,output_image,delta);
	Mat dilatedImage1= Mat::zeros(image.rows,image.cols,image.type()) ; 

	dilation(output_image,dilatedImage1,5);
	output_image = dilatedImage1;
	Mat temp_img = holeFilledImage - output_image ; 

	imshow("holeFilledImage",holeFilledImage);
	imshow("output_image",output_image);

	Mat segmented_image=  Mat::zeros(medianFilteredImage.rows,medianFilteredImage.cols,CV_8UC1) ; 
    multiply(temp_img, medianFilteredImage, segmented_image );

    Mat contrast_enhanced_image= Mat::zeros(medianFilteredImage.rows,medianFilteredImage.cols,medianFilteredImage.type()) ; 
    contrastStretching(segmented_image,contrast_enhanced_image);

    imshow("contrast_enhanced_image",contrast_enhanced_image);
	waitKey(0);
	imwrite( "outputs/mdb004.jpg", contrast_enhanced_image );
	cout<<"Line 109"<<endl;
  	// 

  	// imshow("segmented_image",segmented_image);

   // 


   //  
  
    //int maskSize = 5 ;
    //Mat output_image= Mat::zeros(image.rows,image.cols,image.type()) ; 
   // majority(image, output_image, maskSize);


    // Mat dilatedImage= Mat::zeros(image.rows,i;mage.cols,image.type()) ; 
    // int dilation_maskSize = 5; 
    // dilation(image,dilatedImage,dilation_maskSize);	//the input Image must be binary
    
    // image = dilatedImage ; 
    // Mat erodedImage= Mat::zeros(image.rows,image.cols,image.type()) ; 
    // int erosion_maskSize = 5;
    // erosion(image,erodedImage,erosion_maskSize);	//the input Image must be binary

   // connectedComponents(thresholdedImage,)	//code this later


	cout<<"Line 141"<<endl;
    //waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}

