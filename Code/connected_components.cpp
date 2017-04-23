   int equal_labels(int label1, int label2, Mat& label_image);

   void connectedComponents(Mat& image,Mat& label_image)
   {
   	int label = 1;
	cv::Mat padded;
	int padding = 1;
	padded.create(image.rows + 2*padding, image.cols + 2*padding, image.type());
	padded.setTo(cv::Scalar::all(0));

	image.copyTo(padded(Rect(padding, padding, image.cols, image.rows)));
	//cv::imshow("padded image",padded);
	
	// cout<<"Line 13"<<endl;
   		for(int i= 1 ; i < padded.rows;i++)
   		{
   			for(int j=1 ; j< padded.cols;j++)
   			{
   				// cout<<i<<","<<j<<endl;

   				if((int)padded.at<uchar>(i,j) == 0)
   					continue; 
   				else
   				{
   					
   						if((int)padded.at<uchar>(i-1,j) == 0 && (int)padded.at<uchar>(i,j-1) == 0)
   						{
   							// cout<<"h1"<<endl;
   								label_image.at<uchar>(i,j) = label ;
   								label++ ;
   								// cout<<"label value = "<<(int)label_image.at<uchar>(i,j)<<endl;
   						}
   						else if((int)padded.at<uchar>(i-1,j) ==  255 && (int)padded.at<uchar>(i,j-1) == 255)
   						{
   							// cout<<"h2"<<endl;

   							if(label_image.at<uchar>(i-1,j)!=label_image.at<uchar>(i,j-1))
   							{
   								// cout<<"h21"<<endl;
   								int temp_label = equal_labels((int)label_image.at<uchar>(i-1,j),(int)label_image.at<uchar>(i,j-1), label_image);
   								label_image.at<uchar>(i,j) = temp_label;
   							}
   							else if(label_image.at<uchar>(i-1,j)==label_image.at<uchar>(i,j-1))
   							{
   								//cout<<"h22"<<endl;
   								label_image.at<uchar>(i,j) = label_image.at<uchar>(i-1,j);
							//	cout<<(int)label_image.at<uchar>(i,j)<<endl;
   							}

   						}
   						else if((int)padded.at<uchar>(i-1,j) ==  255 || (int)padded.at<uchar>(i,j-1) == 255)
   						{
   							// cout<<"h3"<<endl;

   							if((int)padded.at<uchar>(i-1,j)== 255 )
   							{
   								//cout<<"h31"<<endl;
   								label_image.at<uchar>(i,j) =label_image.at<uchar>(i-1,j) ; 
   							}
   							else if((int)padded.at<uchar>(i,j-1)== 255)
   							{
   								//cout<<"h32"<<endl;
   								label_image.at<uchar>(i,j) =label_image.at<uchar>(i,j-1) ; 
   							}
   						
	   					}

	   			//	if((int)label_image.at<uchar>(i,j)==0)
	   					// cout<<"here"<<endl;
   				}
   			}
   		}


   }
int equal_labels(int label1, int label2,Mat& label_image)
{
	//cout<<"Line 67"<<endl;
	int label = std::min(label1,label2);
	if(label == 0 )
		 cout<<"Error:: Minimum label coming out to be 0 which is not defined!!"<<endl;

	// cout<<"Label min = "<<label;
	for(int i= 0 ; i < label_image.rows;i++)
   		{
   			for(int j=0 ; j< label_image.cols;j++)
   			{
   				if(label_image.at<uchar>(i,j) == label1 || label_image.at<uchar>(i,j)== label2)
   					label_image.at<uchar>(i,j) = label;
   			}
   		}
	//cout<<"Line 77"<<endl;

   		return label ; 
}
void multiply(Mat& binary, Mat& src, Mat& dst)
{
	for(int i = 0 ; i <src.rows;i++)
	{
		for(int j = 0 ; j<src.cols;j++)
		{
			if((int)binary.at<uchar>(i,j) == 255)
			{
				dst.at<uchar>(i,j) = src.at<uchar>(i,j);
			}
		}
	}
}