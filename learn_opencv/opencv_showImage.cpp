#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int agrc, char* argv[])
{
    Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    namedWindow("Display Window", CV_WINDOW_AUTOSIZE);
    imshow("Display Window", image);

    waitKey(0);

    return 0;
}
