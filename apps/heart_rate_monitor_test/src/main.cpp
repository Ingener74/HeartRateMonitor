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

class OpenCvHeartRateVisualizer
{
public:
    OpenCvHeartRateVisualizer()
    {
    }
    virtual ~OpenCvHeartRateVisualizer()
    {
    }

    void setFreq(cv::Mat freqImage)
    {
    }
    void setHeartRate(cv::Mat heartRateImage)
    {
    }
    void setMockImage(cv::Mat image)
    {
    }
    void start()
    {
    }

private:
    cv::Mat common;
    boost::thread _thread;
};

class OpenCVHRFreqVisualizer: public hrm::IHeartRateFrequencyVisualizer
{
public:
    OpenCVHRFreqVisualizer()
    {
    }
    virtual ~OpenCVHRFreqVisualizer()
    {
    }

    virtual void visualize(const hrm::HrmFrequencyGraph& graph)
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
        if (cv::waitKey(1) == 27) throw hrm::HRVisualizeException(
                "esc pressed");
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

    virtual void visualizeHeartRate(hrm::HrmMeasurementGraph heartRateMeasuredGraph)
            throw (hrm::HRVisualizeException)
    {
        if(heartRateMeasuredGraph.size() < 2)
            return;

        cv::Mat image(480, 640, CV_8UC3, cv::Scalar(0, 0, 0));

        auto
        f = heartRateMeasuredGraph.front(),
        l = heartRateMeasuredGraph.back();

        auto allTime = l.timeStamp - f.timeStamp;

        auto
        maxV = std::numeric_limits<hrm::HrmMeasurement::Value>::min(),
        minV = std::numeric_limits<hrm::HrmMeasurement::Value>::max();

        for(const auto& m: heartRateMeasuredGraph){
            maxV = std::max(m.value, maxV);
            minV = std::min(m.value, minV);
        }

        auto valueDiff = maxV - minV;

        maxV += valueDiff * .1;
        minV -= valueDiff * .1;
        valueDiff = maxV - minV;

        for (int i = 0, imax = heartRateMeasuredGraph.size() - 1; i < imax; ++i)
        {
            auto
            m1 = heartRateMeasuredGraph[i],
            m2 = heartRateMeasuredGraph[i + 1];

            auto x1 = std::max<int>(0, std::min<int>(image.cols * (m1.timeStamp - f.timeStamp) / allTime, image.cols));
            auto y1 = std::max<int>(0, std::min<int>(image.rows * (m1.value - minV)/ valueDiff, image.rows));

            auto x2 = std::max<int>(0, std::min<int>(image.cols * (m2.timeStamp - f.timeStamp) / allTime, image.cols));
            auto y2 = std::max<int>(0, std::min<int>(image.rows * (m2.value - minV)/ valueDiff, image.rows));

            cv::Point p1(x1, y1);
            cv::Point p2(x2, y2);

            cv::line(image, p1, p2, cv::Scalar(0, 0, 255), 3);

//            int x = std::max<int>(0, std::min<int>(image.cols * (m1.timeStamp - f.timeStamp) / allTime, image.cols));
//            cv::Point
//            p3(x, 0),
//            p4(x, image.rows - 1);
//            cv::line(image, p3, p4, cv::Scalar(0,255,0));
        }

        cv::imshow("OpenCV heart rate visualizer", image);
        if (cv::waitKey(1) == 27) throw hrm::HeartRateException("esc pressed");
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

    virtual void drawFrame(hrm::FrameRGB frame) throw (hrm::HRDrawException)
    {
        cv::Mat image(frame.getFormat().rect._rows,
                frame.getFormat().rect._cols, CV_8UC3, frame.getData());

        cv::imshow("OpenCV RGB frame drawer", image);
        if (cv::waitKey(1) == 27) throw hrm::HRDrawException("esc pressed");
    }
};

int main(int argc, const char *argv[])
{
    using namespace hrm;

    std::cout << "heart rate monitor test" << std::endl;

    try
    {
        OpenCvHeartRateVisualizer vis;

        auto rgbfs = make_shared<PNGDataBase2RGBFrameSource>("../data/test_data/test_db");

        auto hrg = make_shared<RGBHeartRateGenerator>(rgbfs, make_shared<OpenCVRGBFrameDrawer>());

        auto hrr = make_shared<FFTWHeartRateRecognizer>(make_shared<OpenCVHRFreqVisualizer>());

        auto hrn = make_shared<mock::MockHeartRateNumber>();

        auto hrv = make_shared<OpenCVHRMVisualizer>();

        HeartRateCounter hrc(hrg, hrr, hrn, hrv);

        vis.start();
        hrc.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
    }
    return 0;
}
