#ifndef filter_h
#define filter_h

#include <stdint.h>
#include <fixmath.h>
#include "Arduino.h"

class expFilter {
protected:
  Fix16 average, smoothFactor, smoothFactorComp;
public:
  expFilter (Fix16 smooth);
};

class highPass : expFilter {
private:
  int16_t threshold;
public:
  highPass (Fix16 _smooth, int16_t _threshold);
  int16_t filterData(int16_t inData);
};

class lowPass : expFilter {
public:
  lowPass (Fix16 _smooth);
  int16_t filterData(int16_t inData);
};

class complementaryFilter : expFilter {
private:
  uint32_t interval;
public:
  complementaryFilter (Fix16 _smooth);
  int16_t filterData(int16_t inDataA, int16_t inDataB);
};

#endif // filter_h
