/*
 * RGB2PNGDataBaseFrameDrawer.h
 *
 *  Created on: Apr 2, 2014
 *      Author: ingener
 */

#ifndef RGB2PNGDATABASEFRAMEDRAWER_H_
#define RGB2PNGDATABASEFRAMEDRAWER_H_

#include "IRGBFrameDrawer.h"

namespace hrm {

class RGB2PNGDataBaseFrameDrawer: public IRGBFrameDrawer {
public:
    RGB2PNGDataBaseFrameDrawer(const std::string& dataBaseDir);
    virtual ~RGB2PNGDataBaseFrameDrawer();

    virtual void drawFrame(FrameRGB frame) throw (drawError);

private:
    std::string _dataBaseDir;
    int _counter;
    boost::property_tree::ptree _dataBase;
};

} /* namespace hrm */

#endif /* RGB2PNGDATABASEFRAMEDRAWER_H_ */
