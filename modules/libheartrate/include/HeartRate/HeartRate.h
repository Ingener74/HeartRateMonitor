/*
 * NewHeartRate.h
 *
 *  Created on: Aug 4, 2014
 *      Author: pavel
 */

#ifndef NEWHEARTRATE_H_
#define NEWHEARTRATE_H_

#include <HeartRate/HeartRateCommon.h>

namespace heartrate
{

class HeartRate
{
public:
	using Ptr = std::shared_ptr<HeartRate>;
	using HeartRateOutput = std::function<void(double)>;

	HeartRate(HeartRateOutput heartRateOutput);
	virtual ~HeartRate();

	void putImage(int rows, int cols, const std::vector<char>& buffer);

private:
	HeartRateOutput _hro;
};

}

#endif /* NEWHEARTRATE_H_ */
