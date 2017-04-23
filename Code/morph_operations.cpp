   void erosion(Mat& src, Mat& dst,int windowSize);
   void opening(Mat& src, Mat& dst, int windowSize);
   void clean(Mat& src, Mat& dst, int windowSize);
   void holefill(Mat& src, Mat& dst, int windowSize);


   void dilation(Mat& src, Mat& dst,int windowSize)
    {

	   for(int i=(windowSize-1)/2; i<src.rows -(windowSize-1)/2; i++)
	   {
	      for(int j=(windowSize-1)/2; j<src.cols-(windowSize-1)/2; j++)
	      {
	        int max = 0;
	         for(int a=-(windowSize-1)/2; a<=(windowSize-1)/2; a++){
	             for(int b=-(windowSize-1)/2; b<=(windowSize-1)/2; b++){
	                   if(src.at<uchar>(i+a,j+b) > max)
	                      max = src.at<uchar>(i+a,j+b);
	             }  /*  ends loop over b */
	         }  /* ends loop over a */
	         dst.at<uchar>(i,j) = max;
	      }  /* ends loop over j */
	   }  /* ends loop over i */
    }

    void erosion(Mat& src, Mat& dst,int windowSize)
    {

	   for(int i=(windowSize-1)/2; i<src.rows -(windowSize-1)/2; i++)
	   {
	      for(int j=(windowSize-1)/2; j<src.cols-(windowSize-1)/2; j++)
	      {
	        int min = 255;
	         for(int a=-(windowSize-1)/2; a<=(windowSize-1)/2; a++){
	             for(int b=-(windowSize-1)/2; b<=(windowSize-1)/2; b++){
	                   if(src.at<uchar>(i+a,j+b) < min)
	                      min = src.at<uchar>(i+a,j+b);
	             }  /*  ends loop over b */
	         }  /* ends loop over a */
	         dst.at<uchar>(i,j) = min;
	      }  /* ends loop over j */
	   }  /* ends loop over i */
    }

    void opening(Mat& src, Mat& dst, int windowSize)
    {
    	Mat temp = Mat::zeros(src.rows,src.cols,src.type()) ; 
    	erosion(src,temp,windowSize);
    	dilation(temp,dst,windowSize);
    }

    void clean(Mat& src, Mat& dst, int windowSize)
    {
    	for(int i=(windowSize-1)/2; i<src.rows -(windowSize-1)/2; i++)
	   {
	      for(int j=(windowSize-1)/2; j<src.cols-(windowSize-1)/2; j++)
	      {
	         
	         int flag = 0;
	         if(src.at<uchar>(i,j) != 255)
	         	continue;
	         for(int a=-(windowSize-1)/2; a<=(windowSize-1)/2; a++)
	         {
	             for(int b=-(windowSize-1)/2; b<=(windowSize-1)/2; b++)
	             {
	                   if(src.at<uchar>(i+a,j+b) ==255)
	                   	{
	                   		flag = 1; 
	                   		break;
	                   	}
	             } 

	             if(flag == 1)
	             	break;
	         }  /* ends loop over a */

	         if(flag == 0)
	         	dst.at<uchar>(i,j)= 0 ;	
	         else
	         	dst.at<uchar>(i,j)=255;
	      }  /* ends loop over j */
	   }  /* ends loop over i */

    }

    void holefill(Mat& src, Mat& dst, int windowSize)
    {
    	for(int i=(windowSize-1)/2; i<src.rows -(windowSize-1)/2; i++)
	   {
	      for(int j=(windowSize-1)/2; j<src.cols-(windowSize-1)/2; j++)
	      {
	         
	         int flag = 0;
	         if(src.at<uchar>(i,j) != 0)
	         {
	         	dst.at<uchar>(i,j) = 255;
	         	continue;
	         }	
	         for(int a=-(windowSize-1)/2; a<=(windowSize-1)/2; a++)
	         {
	             for(int b=-(windowSize-1)/2; b<=(windowSize-1)/2; b++)
	             {
	                   if(src.at<uchar>(i+a,j+b) ==0)
	                   	{
	                   		flag = 1; 
	                   		break;
	                   	}
	             } 

	             if(flag == 1)
	             	break;
	         }  /* ends loop over a */

	         if(flag == 0)
	         	dst.at<uchar>(i,j)= 255 ;	
	         else
	         	dst.at<uchar>(i,j)=0;
	      }  /* ends loop over j */
	   }  /* ends loop over i */

    }

    void majority(Mat& src, Mat& dst, int windowSize)
    {

	   for(int i=(windowSize-1)/2; i<src.rows -(windowSize-1)/2; i++)
	   {
	      for(int j=(windowSize-1)/2; j<src.cols-(windowSize-1)/2; j++)
	      {
	      	 int count = 0 ;
	      	 if(src.at<uchar>(i,j) == 255)
	         	continue;
	         for(int a=-(windowSize-1)/2; a<=(windowSize-1)/2; a++)
	         {
	             for(int b=-(windowSize-1)/2; b<=(windowSize-1)/2; b++)
	             {
	                   if(src.at<uchar>(i+a,j+b) == 255)
	                      count++;
	             }  /*  ends loop over b */
	         }  /* ends loop over a */
	         if(count >= ceil(windowSize*windowSize*0.55))
	         	dst.at<uchar>(i,j) = 255;
	      }  /* ends loop over j */
	   }  /* ends loop over i */
    }