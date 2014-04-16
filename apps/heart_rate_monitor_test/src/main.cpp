/*
 * author ingener
 *
 *
 */

#include <exception>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <heartrate/HeartRate.h>

int main(int argc, const char *argv[]) {

    std::cout << "heart rate monitor test" << std::endl;

    try {

        cv::Mat image = cv::imread("../data/test_data/test_db/data_1.png");

        cv::imshow("image", image);

        cv::waitKey(-1);

    } catch (const std::exception& e) {

        std::cerr << "exception: " << e.what() << std::endl;

    }

    return 0;
}
