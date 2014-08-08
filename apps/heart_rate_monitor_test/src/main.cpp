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

#include <HeartRate/HeartRate.h>

using namespace cv;
using namespace std;
using namespace heartrate;

int main(int argc, const char *argv[])
{
	std::cout << "Heart rate monitor test" << std::endl;

	try
	{
		HeartRate hr([](double heartRate)
		{
			cout << "Heart rate " << heartRate << endl;
		});

		auto vc = make_shared<VideoCapture>(0);

		for (;vc->isOpened();)
		{
			Mat image;
			*vc >> image;

			hr.putImage(image.rows, image.cols, vector<char>(image.data, image.data + image.rows * image.cols * 3));

			if (image.rows && image.cols)
			{
				imshow("Output", image);
				if (waitKey(10) == 27)
				{
					break;
				}
			}
		}
	}
	catch ( std::exception const & e )
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
