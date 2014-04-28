/*
 * FFTWHeartRateRecognizer.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: ingener
 */

#include <heartrate/Log.h>
#include <heartrate/HeartRateTools.h>
#include <heartrate/FFTWHeartRateRecognizer.h>

namespace hrm {

const int max_frames_per_minute  = 7200;
const int ms_in_one_sample       = 8;

FFTWHeartRateRecognizer::FFTWHeartRateRecognizer(
        IHeartRateFrequencyVisualizer::Ptr hrFreqVisualizer) :
        _hrFreqVisualizer(hrFreqVisualizer) {

    _samples = std::vector<double>(max_frames_per_minute);
}

FFTWHeartRateRecognizer::~FFTWHeartRateRecognizer() {
}

HrmHeartRate hrm::FFTWHeartRateRecognizer::recognizeHeartRateValue(
        HrmMeasurement rawMeas) throw (HRRecognitionException)
{
//    if (rawMeasGraph.size()
//            != HeartRateTools::rountUpToNextPowerOfTwo(rawMeasGraph.size()))
//        return 80;
//
//    int N = rawMeasGraph.size();
//
//    shared_ptr<fftw_complex[]> in(new fftw_complex[N]);
//    shared_ptr<fftw_complex[]> out(new fftw_complex[N]);
//
//    fftw_complex* pin = in.get(), *pout = out.get();
//
//    for (int i = 0; i < N; ++i) {
//        pin[i][0] = rawMeasGraph[i].get<1>();
//        pin[i][1] = rawMeasGraph[i].get<1>();
//
//        pout[i][0] = 0;
//        pout[i][1] = 0;
//    }
//
//    fftw_plan _fftw_plan = fftw_plan_dft_1d(N, in.get(), out.get(),
//    FFTW_FORWARD, FFTW_ESTIMATE);
//
//    fftw_execute(_fftw_plan);
//
////    for (int i = 0; i < N; ++i) {
////        std::cout << sqrt(pout[i][0] * pout[i][0] + pout[i][1] * pout[i][1])
////                << ", ";
////    }
////    std::cout << std::endl;
//
//    FrequencyGraph freqGraph(N);
//    for (int i = 0; i < N; ++i) {
//        freqGraph[i] = sqrt(pout[i][0] * pout[i][0] + pout[i][1] * pout[i][1]);
//    }
//
//    _hrFreqVisualizer->visualize(freqGraph);
//    fftw_destroy_plan(_fftw_plan);

    Log() << rawMeas;

    return {HrmHeartRate::State::Valid, 80};
}

} /* namespace hrm */

