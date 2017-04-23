void insertionSort(int window[], int windowSize);

void medianFiter(int windowSize, Mat& src, Mat& dst)
{
        
        int window[windowSize*windowSize];
 		int windowCount ;
       
        for(int y = (windowSize-1)/2; y < src.rows - (windowSize-1)/2; y++)
        {
            for(int x = (windowSize-1)/2; x <src.cols - (windowSize-1)/2; x++)
            {
            	//cout <<"x = "<<x<<endl;
 				windowCount = 0 ;
                // Pick up window element
 				for(int k =-(windowSize-1)/2 ; k<=(windowSize-1)/2;k++)
 				{
 					for(int l=-(windowSize-1)/2;l<=(windowSize-1)/2;l++)
 					{
                           	// cout <<"windowCount = "<<windowCount<<endl;
                           	// cout<<" y = "<<y+k <<endl;
                           	// cout<<"X =  "<<x+l <<endl;
 						window[windowCount] = src.at<uchar>(y+ k ,x +l);
 						//cout<<"Line 24"<<endl;
 						windowCount++;
 					}
 				}

  
                // sort the window to find median
                insertionSort(window,windowSize);
                //cout<<"y, x = "<<y<<","<<x <<endl;

   				//cout<<"Window = "<<window[(windowSize*windowSize -1)/2];
                // assign the median to centered element of the matrix


                dst.at<uchar>(y-(windowSize-1)/2,x-(windowSize-1)/2) = window[(windowSize*windowSize -1)/2];
   				//cout<<"Line 30"<<endl;
   				//return ;
            }
        // }
		}
}

void insertionSort(int window[], int windowSize)
{
	// cout<<"Line 39"<<endl;
    int temp, i , j;
    for(i = 0; i < windowSize*windowSize; i++){
        temp = window[i];
        for(j = i-1; j >= 0 && temp < window[j]; j--){
            window[j+1] = window[j];
        }
        window[j+1] = temp;
    }
    // cout<<"Line 47"<<endl;
}