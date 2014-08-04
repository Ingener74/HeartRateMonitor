/*
 * HeartRate.h
 *
 *  Created on: Apr 12, 2014
 *      Author: ingener
 */

#ifndef HEARTRATE_H_
#define HEARTRATE_H_

/*
 * HeartRate commons
 */
#include <HeartRate/HeartRateCommon.h>
#include <HeartRate/HeartBeatRateTypes.h>
#include <HeartRate/HeartRateTools.h>

/*
 * HeartRate interfaces
 */
#include <HeartRate/IHeartRateGenerator.h>
#include <HeartRate/IHeartRateNumber.h>
#include <HeartRate/IHeartRateVisualizer.h>
#include <HeartRate/IHeartRateFrequencyVisualizer.h>
#include <HeartRate/IHeartRateRecognizer.h>
#include <HeartRate/INV21FrameSource.h>
#include <HeartRate/IRGBFrameDrawer.h>
#include <HeartRate/IRGBFrameSource.h>
#include <HeartRate/IRGBImageDrawer.h>

/*
 * HeartRate concrete classes
 */
#include <HeartRate/HeartRateCounter.h>
#include <HeartRate/NV21FrameSource.h>
#include <HeartRate/RGBFrameSource.h>
#include <HeartRate/RGBHeartRateGenerator.h>

#ifdef PNG_FOUND
#include <heartrate/RGB2PNGDataBaseFrameDrawer.h>
#include <heartrate/PNGDataBase2RGBFrameSource.h>
#endif

#ifdef FFTW3_FOUND
#include <heartrate/FFTWHeartRateRecognizer.h>
#endif

/*
 * Mock classes
 */
#include <HeartRate/mocks/MockNV21FrameSource.h>
#include <HeartRate/mocks/MockRGBFrameSource.h>
#include <HeartRate/mocks/MockHeartRateGenerator.h>
#include <HeartRate/mocks/MockHeartRateNumber.h>
#include <HeartRate/mocks/MockHeartRateVisualizer.h>
#include <HeartRate/mocks/MockHeartRateRecognizer.h>
#include <HeartRate/mocks/MockHeartRateFrequencyVisualizer.h>

#endif /* HEARTRATE_H_ */
