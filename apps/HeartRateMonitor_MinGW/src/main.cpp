
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char *argv[])
{
    using namespace std;

    cv::Mat image(480, 640, CV_8UC3);

    cv::imshow("image", image);

    cv::waitKey();

    cout << "HeartRateMonitor" << endl;

    return 0;
}
