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

HeartRate::HeartRate(HeartRateOutput heartRateOutput): _hro(heartRateOutput)
{
}

HeartRate::~HeartRate()
{
}

void HeartRate::putImage(int rows, int cols, const std::vector<char>& buffer)
{
	if (!_hro) throw runtime_error(string(__FUNCTION__) + " i have no heart rate output function");

	_hro(70);
}

}

