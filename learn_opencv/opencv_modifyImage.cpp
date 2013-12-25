#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int agrc, char* argv[])
{
    Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat grayImage;

    cvtColor(image, grayImage, CV_BGR2GRAY);

    imwrite("grayLena.jpg", grayImage);


    namedWindow("Color Window", CV_WINDOW_AUTOSIZE);
    namedWindow("Gray Window", CV_WINDOW_AUTOSIZE);
    imshow("Color Window", image);
    imshow("Gray Window", grayImage);

    waitKey(0);

    return 0;
}
