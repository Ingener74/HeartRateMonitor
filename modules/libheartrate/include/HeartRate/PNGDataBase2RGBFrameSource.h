/*
 * PNGDataBase2RGBFrameSource.h
 *
 *  Created on: Apr 13, 2014
 *      Author: ingener
 */

#ifndef PNGDATABASE2RGBFRAMESOURCE_H_
#define PNGDATABASE2RGBFRAMESOURCE_H_

#include <HeartRate/IRGBFrameSource.h>

namespace hrm {

class PNGDataBase2RGBFrameSource: public IRGBFrameSource {
public:
    PNGDataBase2RGBFrameSource(const std::string& dataBaseDir);
    virtual ~PNGDataBase2RGBFrameSource();

    virtual FrameSharedLockedRGB getFrame();

private:
    std::string _dataBaseDir;
    property_tree::ptree _dataBase;
    int _currentFrame, _frameCount;

    TimeStamp _delay;
    TimeStamp _fsTimeStamp;

    shared_mutex _frameMutex;
    FrameRGB _frame;
};

} /* namespace hrm */

#endif /* PNGDATABASE2RGBFRAMESOURCE_H_ */
