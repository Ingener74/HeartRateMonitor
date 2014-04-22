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

class OpenCVHRFreqVisualizer: public hrm::IHeartRateFrequencyVisualizer
{
public:
    OpenCVHRFreqVisualizer()
    {
    }
    virtual ~OpenCVHRFreqVisualizer()
    {
    }

    virtual void visualize(const hrm::FrequencyGraph& graph)
            throw (hrm::HRVisualizeException)
    {

        double mx = std::numeric_limits<double>::min(), mn =
                std::numeric_limits<double>::max(), diff;

        for (const double& x : graph)
        {
            mx = std::max(mx, x);
            mn = std::min(mn, x);
        }
        diff = mx - mn;

        mx += diff * 0.1;
        mn -= diff * 0.1;

        diff = mx - mn;

        cv::Mat image(480, 640, CV_8UC3, cv::Scalar(0, 0, 0));
        cv::putText(image,
                (boost::format("graph size %1%") % int(graph.size())).str(),
                cv::Point(12, 24), cv::FONT_HERSHEY_PLAIN, 1,
                cv::Scalar(0, 255, 0));

        for (int i = 0, imax = graph.size() - 1; i < imax; ++i)
        {
            cv::Point
            p1(image.cols *  i      / double(graph.size()), image.rows - image.rows * ( (graph[i]     - mn) / diff )),
            p2(image.cols * (i + 1) / double(graph.size()), image.rows - image.rows * ( (graph[i + 1] - mn) / diff ));

            cv::line(image, p1, p2, cv::Scalar(0, 255, 0), 1);
        }
        cv::imshow("freq vis", image);
//        cv::moveWindow("freq vis", 0, 480);
        if (cv::waitKey(1) == 27)
        {
            throw hrm::HeartRateException("esc pressed");
        }
    }

private:
};

class OpenCVHRMVisualizer: public hrm::IHeartRateVisualizer
{
public:
    OpenCVHRMVisualizer()
    {
    }
    virtual ~OpenCVHRMVisualizer()
    {
    }

    virtual void visualizeHeartRate(hrm::MeasurementGraph heartRateMeasuredGraph)
    {

        cv::Mat image(480, 640, CV_8UC3, cv::Scalar(0, 0, 0));

        hrm::Measurement f = heartRateMeasuredGraph.front(), l =
                heartRateMeasuredGraph.back();

        hrm::TimeStamp allTime = l.get<0>() - f.get<0>();

        for (int i = 0, imax = heartRateMeasuredGraph.size() - 1; i < imax; ++i)
        {
            hrm::Measurement
            m1 = heartRateMeasuredGraph[i],
            m2 = heartRateMeasuredGraph[i + 1];

            cv::Point p1(
                    std::max<int>(0, std::min<int>(image.cols * (m1.get<0>() - f.get<0>()) / allTime, image.cols)),
                    std::max<int>(0, std::min<int>(image.rows * m1.get<1>(), image.rows)));
            cv::Point p2(
                    std::max<int>(0, std::min<int>(image.cols * (m2.get<0>() - f.get<0>()) / allTime, image.cols)),
                    std::max<int>(0, std::min<int>(image.rows * m2.get<1>(), image.rows)));

            cv::line(image, p1, p2, cv::Scalar(255, 0, 0));
        }

        cv::imshow("OpenCV heart rate visualizer", image);
//        cv::moveWindow("OpenCV heart rate visualizer", 0, 0);

        if (cv::waitKey(1) == 27)
        {
            throw hrm::HeartRateException("esc pressed");
        }
    }
};

class OpenCVRGBFrameDrawer: public hrm::IRGBFrameDrawer
{
public:
    OpenCVRGBFrameDrawer()
    {
    }
    virtual ~OpenCVRGBFrameDrawer()
    {
    }

    virtual void drawFrame(hrm::FrameRGB frame) throw (hrm::DrawError)
    {

        cv::Mat image(frame.getFormat().rect._rows,
                frame.getFormat().rect._cols, CV_8UC3, frame.getData());

        cv::imshow("OpenCV RGB frame drawer", image);
//        cv::moveWindow("OpenCV RGB frame drawer", 640, 0);

        if (cv::waitKey(1) == 27)
        {
            throw hrm::DrawError("esc pressed");
        }
    }
};

int main(int argc, const char *argv[])
{
    using namespace hrm;

    std::cout << "heart rate monitor test" << std::endl;

    try
    {
        auto rgbfs = make_shared<PNGDataBase2RGBFrameSource>("../data/test_data/test_db");

        auto hrg = make_shared<RGBHeartRateGenerator>(rgbfs, make_shared<OpenCVRGBFrameDrawer>());

        auto hrr = make_shared<FFTWHeartRateRecognizer>(make_shared<OpenCVHRFreqVisualizer>());

        auto hrn = make_shared<mock::MockHeartRateNumber>();

        auto hrv = make_shared<OpenCVHRMVisualizer>();

        HeartRateCounter hrc(hrg, hrr, hrn, hrv);

        hrc.run();

//        cv::Mat image = cv::imread("../data/test_data/test_db/data_1.png");
//        cv::imshow("image", image);
//        cv::waitKey(-1);
    }
    catch (const std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
    }
    return 0;
}
