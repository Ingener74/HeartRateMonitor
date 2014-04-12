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
#include <heartrate/HeartRateExceptions.h>
#include <heartrate/HeartRateTools.h>

/*
 * HeartRate interfaces
 */
#include <heartrate/IHeartRateGenerator.h>
#include <heartrate/IHeartRateNumber.h>
#include <heartrate/IHeartRateVisualizer.h>
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
#include <heartrate/RGB2PNGDataBaseFrameDrawer.h>
#include <heartrate/RGBFrameSource.h>
#include <heartrate/RGBHeartRateGenerator.h>

/*
 * Mock classes
 */
#include <heartrate/dummys/DummyNV21FrameSource.h>
#include <heartrate/dummys/DummyRGBFrameSource.h>
#include <heartrate/dummys/SimpleHeartRateGenerator.h>
#include <heartrate/dummys/SimpleHeartRateNumber.h>
#include <heartrate/dummys/SimpleHeartRateVisualizer.h>

#endif /* HEARTRATE_H_ */
