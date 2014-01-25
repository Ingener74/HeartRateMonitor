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

#define D(...){__android_log_print(ANDROID_LOG_DEBUG, HRM_TAG, __VA_ARGS__);}
#define I(...){__android_log_print(ANDROID_LOG_INFO,  HRM_TAG, __VA_ARGS__);}
#define W(...){__android_log_print(ANDROID_LOG_WARN,  HRM_TAG, __VA_ARGS__);}
#define E(...){__android_log_print(ANDROID_LOG_ERROR, HRM_TAG, __VA_ARGS__);}

#else // Linux specified

#include <stdio.h>
#define D(...){printf(__VA_ARGS__);}
#define I(...){printf(__VA_ARGS__);}
#define W(...){printf(__VA_ARGS__);}
#define E(...){printf(__VA_ARGS__);}

#endif // For all platform

#define mySleep(ms){ usleep(ms * 1000); }
#define myFree(x){ if(x) delete x; x = 0; }

#endif /* HRM_DEFINES_H_ */
