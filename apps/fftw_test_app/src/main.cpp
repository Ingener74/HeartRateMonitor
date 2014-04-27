/*
 * main.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: ingener
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <stdexcept>

#include <boost/smart_ptr.hpp>
#include <boost/format.hpp>

#include <fftw3.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void draw_vector(const std::vector<double>& vector, cv::Mat& image,
        cv::Scalar color)
{
    if(image.empty())
        throw std::runtime_error("image is empty");
    if(vector.empty())
        throw std::runtime_error("vector is empty");

    double mx = std::numeric_limits<double>::min(),
            mn = std::numeric_limits<double>::max(),
            diff;

    for (auto& x : vector)
    {
        mx = std::max(mx, x);
        mn = std::min(mn, x);
    }
    diff = mx - mn;

    mx += diff * 0.1;
    mn -= diff * 0.1;

    diff = mx - mn;

    std::cout << "mx " << mx << ", mn " << mn << ", diff " << diff << std::endl;

    for (int i = 0, imax = vector.size() - 1; i < imax; ++i)
    {
        cv::Point p1(image.cols * i / double(vector.size()),
                image.rows - image.rows * ((vector[i] - mn) / diff)), p2(
                image.cols * (i + 1) / double(vector.size()),
                image.rows - image.rows * ((vector[i + 1] - mn) / diff));

        cv::line(image, p1, p2, color, 1);
    }

//    cv::line(image,
//            cv::Point(0,          image.rows - image.rows * ( (0 - mn) / diff )),
//            cv::Point(image.cols, image.rows - image.rows * ( (0 - mn) / diff )),
//            cv::Scalar(0, 145, 136), 1);
}

class TestClass
{
public:
    TestClass()
    {
    }
    virtual ~TestClass()
    {
    }

private:

    int a = 10;
    std::string b = "test string";
    std::vector<int> c =
    { 1, 2, 100, 200 };

};

int main(int argc, char **argv)
{
    try
    {
        using namespace boost;
        using namespace std;

        auto x = [](int i){ return i += 20; }(10);

        cout << "x from lambda " << x << endl;

        /*
         * Nyquist frequency
         * A frequency equal to half the current sample rate, which determines
         * the highest reproducible audio frequency for that rate.
         *
         * For example, audio CDs use a sample rate of 44,100 Hz because the
         * resulting Nyquist frequency is 22,050 Hz—just above the limit of
         * human hearing, 20,000 Hz. For the best audio quality, record and
         * edit at higher sample rates and then convert down if needed.
         */

        const int N = 512;

        const double sample_rate = 44100 /* sample per second */;

        /*
         * samples per minute
         *
         * 30 fps = 30 frames per second
         *
         * 60 sec = 1 min
         *
         * 30 [fps] * 60[second]  = frames per minute = 900 fpm [ frames per minute ]
         *
         * ~= 900 samples per minute [ spm ]
         *
         * {30 [fps], 60 [fps], 120 [fps]} * 60 [sec] = {900 [fpm] - 7200 [fpm]}
         *
         * 1 [fpm] = 1 [min] / 7200 [sample] = 60 [sec] / 7200 [sample] = 60 * 1000 [ms] / 7200 [sample] = 60000 [ms] / 7200 [sample] = 8 [ms / sample]
         *
         *
         */



        const double frequency = sample_rate / 2 /* Hz */;

        const double freq_prec = frequency / N; /* Hz in one dft output bin */

        const double periodsInSample = 20;

        const double cur_freq = frequency / N * periodsInSample;

        cout.precision(5);
        cout << "sample rate       = " << setw(20) << sample_rate << " sample per second" << endl;
        cout << "frequency         = " << setw(20) << frequency   << " Hz" << endl;
        cout << "freq prec         = " << setw(20) << freq_prec   << " Hz in one fft output bin" << endl;
        cout << "current frequency = " << setw(20) << cur_freq    << " Hz" << endl;

        vector<double> in(N), out(N / 2);
        double f1 = -M_PI, f2 = M_PI, fs = (f2 - f1) / N;

        for (int i = 0; i < N; ++i)
        {
            in[i] = sin(f1 + fs * i * periodsInSample);
        }

        auto fftin  = boost::make_shared<fftw_complex[]>(N);
        auto fftout = boost::make_shared<fftw_complex[]>(N);

        for (int i = 0; i < N; ++i)
        {
            fftin.get()[i][0] = in[i];
            fftin.get()[i][1] = in[i];

            fftout.get()[i][0] = 0;
            fftout.get()[i][1] = 0;
        }

        fftw_plan plan = fftw_plan_dft_1d(N, fftin.get(), fftout.get(),
                FFTW_FORWARD, FFTW_ESTIMATE);

        fftw_execute(plan);

        fftw_destroy_plan(plan);

        const int W = 640, H = 480;

        cv::Mat input(H, W, CV_8UC3, cv::Scalar(0, 0, 0));
        draw_vector(in, input, cv::Scalar(255, 0, 0));

        double ds = 0.0;
        for (int i = 0; i < N / 2; ++i)
        {
            out[i] = sqrt(fftout.get()[i][0] * fftout.get()[i][0] + fftout.get()[i][1] * fftout.get()[i][1]);

            cout << format("%1$4d) < %2$10d Hz - %3$10d Hz > --- %4$10d") % i % ds % (ds + freq_prec) % out[i] << std::endl;
            ds += freq_prec;
        }

        cv::Mat freq(H, W, CV_8UC3, cv::Scalar(0, 0, 0));
        draw_vector(out, freq, cv::Scalar(0, 255, 0));

        cv::imshow("signal", input);
        cv::imshow("freq", freq);

        cv::waitKey(-1);

    }
    catch (const std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
    }

    return 0;
}

