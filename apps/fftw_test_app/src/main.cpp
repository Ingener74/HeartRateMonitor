/*
 * main.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: ingener
 */

#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>

#include <boost/smart_ptr.hpp>

#include <fftw3.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void draw_vector(const std::vector<double>& vector, cv::Mat& image, cv::Scalar color){

    double
    mx = std::numeric_limits<double>::min(),
    mn = std::numeric_limits<double>::max(),
    diff;

    for(const double& x: vector){
        mx = std::max(mx, x);
        mn = std::min(mn, x);
    }
    diff = mx - mn;

    mx += diff * 0.1;
    mn -= diff * 0.1;

    diff = mx - mn;

    std::cout << "mx " << mx << ", mn " << mn << ", diff " << diff << std::endl;

    for (int i = 0, imax = vector.size() - 1; i < imax; ++i) {
        cv::Point
        p1(image.cols *  i      / double(vector.size()), image.rows - image.rows * ( (vector[i]     - mn) / diff )),
        p2(image.cols * (i + 1) / double(vector.size()), image.rows - image.rows * ( (vector[i + 1] - mn) / diff ));

        cv::line(image, p1, p2, color, 1);
    }

//    cv::line(image,
//            cv::Point(0,          image.rows - image.rows * ( (0 - mn) / diff )),
//            cv::Point(image.cols, image.rows - image.rows * ( (0 - mn) / diff )),
//            cv::Scalar(0, 145, 136), 1);
}

int main(int argc, char **argv) {

    try {

        using namespace boost;

        const int N = 256;
//        const int N = 2048;
//        const int N = 2048*2;

        std::vector<double> in(N), out(N);

        double f1 = -M_PI, f2 = M_PI, fs = (f2 - f1) / N;

        for(int i = 0; i < N; ++i){
//            in[i] = sin(f1 + fs*i*16) + 1.7*cos(f1 + fs*i*32);
            in[i] = sin(f1 + fs*i*70);
        }

        shared_ptr<fftw_complex[]> fftin(new fftw_complex[N]);
        shared_ptr<fftw_complex[]> fftout(new fftw_complex[N]);

        for(int i = 0; i < N; ++i){
            fftin.get()[i][0] = in[i];
            fftin.get()[i][1] = in[i];

            fftout.get()[i][0] = 0;
            fftout.get()[i][1] = 0;
        }

        fftw_plan plan = fftw_plan_dft_1d(N, fftin.get(), fftout.get(), FFTW_FORWARD, FFTW_ESTIMATE);

        fftw_execute(plan);

        fftw_destroy_plan(plan);

        const int W = 640, H = 480;

        cv::Mat input(H, W, CV_8UC3, cv::Scalar(0, 0, 0));
        draw_vector(in, input, cv::Scalar(255, 0, 0));

        for(int i = 0; i < N; ++i){
            out[i] = sqrt(
                    fftout.get()[i][0]*fftout.get()[i][0] +
                    fftout.get()[i][1]*fftout.get()[i][1]);
//            out[i] = fftout.get()[i][0];
        }

        cv::Mat freq(H, W, CV_8UC3, cv::Scalar(0, 0, 0));
        draw_vector(out, freq, cv::Scalar(0, 255, 0));

        cv::imshow("signal", input);
        cv::imshow("freq",   freq);

        cv::waitKey(-1);

    } catch (const std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }

    return 0;
}

