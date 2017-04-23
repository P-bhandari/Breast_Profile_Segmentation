void  thresholding(Mat& src,Mat& dst,int globalThreshold)
{
	dst = src.clone();
	for(int i = 0 ; i<src.rows;i++)
	{
		for(int j = 0 ; j<src.cols;j++)
		{
			if(src.at<uchar>(i ,j)>globalThreshold)
			{
				dst.at<uchar>(i,j)= 255 ;
			}
			else
				dst.at<uchar>(i,j)= 0 ;
		}
	}
}
