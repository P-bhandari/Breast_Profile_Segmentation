   void contrastStretching(Mat& image,Mat& contrast_enhanced_image)
   {
   		int min = 256; 
   		int max = -1; 
   		for(int i= 0 ; i <image.rows;i++)
   		{
   			for(int j = 0  ; j<image.cols;j++)
   			{
   				if(min>image.at<uchar>(i,j))
   					min = image.at<uchar>(i,j); 

   				if(max <image.at<uchar>(i,j)) 
   					max = image.at<uchar>(i,j); 
   			}
   		}
		// std::cout<<min<<endl;
  //  		std::cout<<max<<endl;
   		for(int i= 0 ; i <image.rows;i++)
   		{
   			for(int j = 0  ; j<image.cols;j++)
   			{
   				contrast_enhanced_image.at<uchar>(i,j) = (image.at<uchar>(i,j)-min )*255/(max-min) ;
   			}
   		}


   		
   }
