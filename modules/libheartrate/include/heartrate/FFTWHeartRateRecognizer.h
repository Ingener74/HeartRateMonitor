/*
 * FFTWHeartRateRecognizer.h
 *
 *  Created on: Apr 13, 2014
 *      Author: ingener
 */

#ifndef FFTWHEARTRATERECOGNIZER_H_
#define FFTWHEARTRATERECOGNIZER_H_

#include <fftw3.h>

#include <heartrate/IHeartRateRecognizer.h>
#include <heartrate/IHeartRateFrequencyVisualizer.h>

namespace hrm {

class FFTWHeartRateRecognizer: public IHeartRateRecognizer {
public:
    FFTWHeartRateRecognizer(IHeartRateFrequencyVisualizer::Ptr hrFreqVisualizer);
    virtual ~FFTWHeartRateRecognizer();

    virtual HeartRateValue recognizeHeartRateValue(
            RawMeasurementGraph rawMeasGraph) throw (HRRecognitionException);

private:
    IHeartRateFrequencyVisualizer::Ptr _hrFreqVisualizer;
};

} /* namespace hrm */

#endif /* FFTWHEARTRATERECOGNIZER_H_ */
