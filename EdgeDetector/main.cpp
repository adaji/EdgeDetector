//
//  main.cpp
//  EdgeDetector
//
//  Created by Ada Ji on 7/8/16.
//  Copyright © 2016 Kingsee. All rights reserved.
//

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

Mat src;
Mat dst; // Detected edges
int edgeThresh = 1;
int lowThreshold = 50; // TODO: Automatically find the optimized low threshold
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
const char* window_name = "Edge Map";

static void CannyThreshold(int, void*)
{
    blur( src, dst, Size(kernel_size, kernel_size) );
    Canny( dst, dst, lowThreshold, lowThreshold*ratio, kernel_size );
    imshow( window_name, dst );
    imwrite("../../images/detected_edges.bmp", dst); // TODO: Why is imwrite not working???
}

int main( int, char** argv )
{
    src = imread( argv[1] );
    if( src.empty() )
    {
        return -1;
    }
    resize(src, src, Size(src.cols/4, src.rows/4)); // Resize the image to display it in full
    cvtColor( src, src, COLOR_BGR2GRAY );
    namedWindow( window_name, WINDOW_AUTOSIZE);
    createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
    CannyThreshold(0, 0);

    waitKey(0);
    return 0;
}












