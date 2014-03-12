#include "highgui.h"

int main(int argc, char** argv)
{
    IplImage* img = cvLoadImage(argv[1]);

    //cvNamedWindow("Title", CV_WINDOW_AUTOSIZE);
    
    cvShowImage("helloworld", img);

    cvWaitKey(0);

    cvReleaseImage(&img);

    return 0;
}
