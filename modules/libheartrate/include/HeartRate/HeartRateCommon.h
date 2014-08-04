/*
 * HeartRateCommon.h
 *
 *  Created on: Apr 12, 2014
 *      Author: ingener
 */

#ifndef HEARTRATECOMMON_H_
#define HEARTRATECOMMON_H_

#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <tuple>
#include <limits>
#include <cmath>
#include <vector>
#include <deque>
#include <exception>
#include <algorithm>
#include <string>
#include <sstream>

#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/format.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <unistd.h>

#ifdef ANDROID // Android specified

#include <android/log.h>

#define HRM_TAG "Heart Rate Monitor Native"

#define LLDEBUG(...){__android_log_print(ANDROID_LOG_DEBUG, HRM_TAG, __VA_ARGS__);}
#define LLINFO(...){__android_log_print(ANDROID_LOG_INFO,  HRM_TAG, __VA_ARGS__);}
#define LLWARN(...){__android_log_print(ANDROID_LOG_WARN,  HRM_TAG, __VA_ARGS__);}
#define LLERROR(...){__android_log_print(ANDROID_LOG_ERROR, HRM_TAG, __VA_ARGS__);}

#else // Linux specified

#include <stdio.h>
#define LLDEBUG(...){printf(__VA_ARGS__);}
#define LLINFO(...){printf(__VA_ARGS__);}
#define LLWARN(...){printf(__VA_ARGS__);}
#define LLERROR(...){printf(__VA_ARGS__);}

#endif // For all platform

namespace hrm {

using namespace boost;

}  // namespace hrm

#endif /* HEARTRATECOMMON_H_ */
