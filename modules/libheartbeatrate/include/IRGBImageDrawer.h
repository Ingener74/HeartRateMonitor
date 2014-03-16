/*
 * IRGBImageDrawer.h
 *
 *  Created on: Mar 15, 2014
 *      Author: ingener
 */

#ifndef IRGBIMAGEDRAWER_H_
#define IRGBIMAGEDRAWER_H_

#include <memory>

#include "HeartBeatRateTypes.h"

namespace hrm {

class IRGBImageDrawer {
public:
	typedef std::shared_ptr<IRGBImageDrawer> Ptr;

	virtual ~IRGBImageDrawer() {
	}

	virtual void drawImage(RGBImage image) = 0;
protected:
	IRGBImageDrawer() {
	}
};

}  // namespace hrm

#endif /* IRGBIMAGEDRAWER_H_ */
