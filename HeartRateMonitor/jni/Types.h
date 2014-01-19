/*
 * Types.h
 *
 *  Created on: Jan 19, 2014
 *      Author: pavel
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <time.h>

namespace hrm {

class TimeCounter {
public:
    TimeCounter() :
            _time(0), _delta(0) {
    }
    virtual ~TimeCounter() {
    }
    double timeElapsedInMS() {
        struct timespec tm;
        clock_gettime(CLOCK_MONOTONIC, &tm);

        uint64_t t1 = tm.tv_sec * 1000000000LL + tm.tv_nsec;
        double t = double(t1 / 1e6);
        _delta = t - _time;
        _time = t;
        return _delta;
    }

private:
    double _time, _delta;
};

class Frame {
public:
    Frame(uint32_t rows = 0, uint32_t cols = 0, uint32_t bytesPerPixel = 0) :
            _rows(rows), _cols(cols), _bytesPerPixel(bytesPerPixel), _data(
                    (_rows && _cols && _bytesPerPixel) ?
                            new uint8_t[_rows * _cols * _bytesPerPixel] :
                            0
                            ) {
    }
    virtual ~Frame() {
        if(_data)
            delete[] _data;
        _data = 0;
    }
    Frame(const Frame& frame){
    }
    Frame& operator=(const Frame& frame){
        return *this;
    }

    uint32_t getRows() const {
        return _rows;
    }
    uint32_t getCols() const {
        return _cols;
    }
    uint32_t getBytesPerPixel() const {
        return _bytesPerPixel;
    }
    uint8_t* getData(){
        return _data;
    }

private:
    uint32_t _rows, _cols, _bytesPerPixel;
    uint8_t * _data;
};

}  // namespace hrm

#endif /* TYPES_H_ */
