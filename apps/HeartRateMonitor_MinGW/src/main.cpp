
#include <iostream>
#include <stdexcept>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char *argv[])
{
    using namespace std;

    try
    {
        cout << "HeartRateMonitor" << endl;

        cv::Mat image = cv::imread(argv[1]);

        cv::imshow("image", image);

        cv::waitKey();

    }
    catch (const std::exception& e)
    {
        cerr << "exception: " << e.what() << endl;
    }

    return 0;
}
