/*
 * IImageDrawer.h
 *
 *  Created on: Jan 29, 2014
 *      Author: pavel
 */

#ifndef IIMAGEDRAWER_H_
#define IIMAGEDRAWER_H_

namespace hrm {

class IImageDrawer {
public:
    virtual ~IImageDrawer(){}

    virtual void drawImage() = 0;

protected:
    IImageDrawer(){}
};

}  // namespace hrm



#endif /* IIMAGEDRAWER_H_ */
