#include "filter.h"

expFilter::expFilter (Fix16 smooth) {
  smoothFactor = smooth;
  smoothFactorComp = Fix16(1)-smooth;
  average = 0;
}

highPass::highPass (Fix16 _smooth, int16_t _threshold) : expFilter(_smooth) {
  threshold = _threshold;
}

int16_t highPass::filterData (int16_t inData) {
  if ( abs(inData) < threshold )
    average = smoothFactor*inData + smoothFactorComp*average;
  return Fix16(inData) - average;
}

lowPass::lowPass (Fix16 _smooth) : expFilter(_smooth) {}

int16_t lowPass::filterData (int16_t inData) {
  average = smoothFactor*inData + smoothFactorComp*average;
  return average;
}

complementaryFilter::complementaryFilter (Fix16 _smooth) : expFilter(_smooth) {}

int16_t complementaryFilter::filterData (int16_t inDataA, int16_t inDataB) {
  Fix16 dt = Fix16( int16_t(millis()-interval) );
  dt /= 1000;
  average = smoothFactor*(average + Fix16(inDataA)*dt) + smoothFactorComp*Fix16(inDataB);
  interval = millis();
  return average;
}
