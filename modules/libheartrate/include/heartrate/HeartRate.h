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
#include <heartrate/HeartRateCommon.h>
#include <heartrate/HeartBeatRateTypes.h>
#include <heartrate/HeartRateTools.h>
#include <heartrate/types/Exception.h>
#include <heartrate/Log.h>

/*
 * HeartRate interfaces
 */
#include <heartrate/IHeartRateGenerator.h>
#include <heartrate/IHeartRateNumber.h>
#include <heartrate/IHeartRateVisualizer.h>
#include <heartrate/IHeartRateFrequencyVisualizer.h>
#include <heartrate/IHeartRateRecognizer.h>
#include <heartrate/ILog.h>
#include <heartrate/INV21FrameSource.h>
#include <heartrate/IRGBFrameDrawer.h>
#include <heartrate/IRGBFrameSource.h>
#include <heartrate/IRGBImageDrawer.h>

/*
 * HeartRate concrete classes
 */
#include <heartrate/HeartRateCounter.h>
#include <heartrate/NV21FrameSource.h>
#include <heartrate/RGBFrameSource.h>
#include <heartrate/RGBHeartRateGenerator.h>

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
#include <heartrate/mocks/MockNV21FrameSource.h>
#include <heartrate/mocks/MockRGBFrameSource.h>
#include <heartrate/mocks/MockHeartRateGenerator.h>
#include <heartrate/mocks/MockHeartRateNumber.h>
#include <heartrate/mocks/MockHeartRateVisualizer.h>
#include <heartrate/mocks/MockHeartRateRecognizer.h>
#include <heartrate/mocks/MockHeartRateFrequencyVisualizer.h>

#endif /* HEARTRATE_H_ */
