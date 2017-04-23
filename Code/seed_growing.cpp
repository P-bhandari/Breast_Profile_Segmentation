
int Mod(int X,int Y);

void Method(Mat& array,Mat& check,int X,int Y,int delta)
{
   // cout<<X<<",,,"<<Y<<endl;
    int N = array.cols-1;
    int M = array.rows-1;
    check.at<uchar>(X,Y) = 255;
    // cout<<"h1"<<endl;
    if(X>0 && Y>0 && (int)check.at<uchar>(X-1,Y-1) ==0 && Mod((int)array.at<uchar>(X,Y) ,(int)array.at<uchar>(X-1,Y-1) )<delta )
    {
        // cout<<"h2"<<endl;
        Method(array,check,X-1,Y-1,delta);
        //check[X-1][Y-1] = 1;
    }
    if(Y>0 && (int)check.at<uchar>(X,Y-1) ==0 && Mod((int)array.at<uchar>(X,Y) ,(int)array.at<uchar>(X,Y-1) )<delta )
    {
        // cout<<"h3"<<endl;
        Method(array,check,X,Y-1,delta);
        //check[X][Y-1] = 1;
    }
    if(X+1<M && Y>0 && (int)check.at<uchar>(X+1,Y-1) ==0 && Mod((int)array.at<uchar>(X,Y) ,(int)array.at<uchar>(X+1,Y-1) )<delta )
    {
        // cout<<"h4"<<endl;
        Method(array,check,X+1,Y-1,delta);
        //check[X+1][Y-1] = 1;
    }
    if(X>0 && (int)check.at<uchar>(X-1,Y) ==0 && Mod((int)array.at<uchar>(X,Y) ,(int)array.at<uchar>(X-1,Y) )<delta )
    {
        // cout<<"h5"<<endl;
        Method(array,check,X-1,Y,delta);
        //check[X-1][Y] = 1;
    }
    if(X+1<M && (int)check.at<uchar>(X+1,Y) ==0 && Mod((int)array.at<uchar>(X,Y) ,(int)array.at<uchar>(X+1,Y) )<delta)
    {
        // cout<<"h6"<<endl;
        Method(array,check,X+1,Y,delta);
        //check[X+1][Y] = 1;
    }
    if(X>0 && Y+1<N && (int)check.at<uchar>(X-1,Y+1) ==0 && Mod((int)array.at<uchar>(X,Y) ,(int)array.at<uchar>(X-1,Y+1) )<delta  )
    {
        // cout<<"h7"<<endl;
        Method(array,check,X-1,Y+1,delta);
        //check[X-1][Y+1] = 1;
    }
    if(Y+1<N && (int)check.at<uchar>(X,Y+1) ==0 && Mod((int)array.at<uchar>(X,Y) ,(int)array.at<uchar>(X,Y+1) )<delta )
    {
        // cout<<"h8"<<endl;
        Method(array,check,X,Y+1,delta);
        //check[X][Y+1] = 1;
    }
    if(X+1<M && Y+1<N && (int)check.at<uchar>(X+1,Y+1) ==0 && Mod((int)array.at<uchar>(X,Y) ,(int)array.at<uchar>(X+1,Y+1) )<delta )
    {
        // cout<<"h9"<<endl;
        Method(array,check,X+1,Y+1,delta);
        //check[X+1][Y+1] = 1;
    }
}

int Mod(int X,int Y)
{
   // cout<<X<<"  "<<Y<<endl;
    if(X>Y)
        return X-Y;
    else
        return Y-X;
}


void seeded_region_growing(Mat& array,Mat& check,int delta)
{
   // int array[][3] = {{1,2,3},{1,2,3},{1,2,5}};
   // int check[][3] = {{0,0,0},{0,0,0},{0,0,0}};
   
   int i = 15;
   int j = 75 ;
   
   
   Method(array,check,i,j,delta);
   
   // for(int i=0;i<N;i++)
   // {
   //  for(int j=0;j<N;j++)
   //      cout<<check[i][j]<<"  ";
   //  cout<<endl;
   // }

  // return 0;
}
