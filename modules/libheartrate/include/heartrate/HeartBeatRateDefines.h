/*
 * hrm_defines.h
 *
 *  Created on: 26 нояб. 2013 г.
 *      Author: pavel
 */

#ifndef HRM_DEFINES_H_
#define HRM_DEFINES_H_

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

#define mySleep(ms){ usleep(ms * 1000); }

#endif /* HRM_DEFINES_H_ */
