/*
 * HeartRate.cpp
 *
 *  Created on: Aug 4, 2014
 *      Author: pavel
 */

#include <HeartRate/HeartRate.h>

namespace heartrate
{

using namespace std;

HeartRate::HeartRate(HeartRateOutput heartRateOutput)
{
}

HeartRate::~HeartRate()
{
}

void HeartRate::putImage(int rows, int cols, const std::vector<char>& buffer)
{
	if (!_hro) throw runtime_error(__FUNCTION__ + "i have no heart rate output function");

	_hro(70);
}

}

