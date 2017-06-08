#ifndef filter_h
#define filter_h

#include <stdint.h>

class mobileWindow {
private:
  int16_t* buffer;
  int8_t index, order;
  int32_t currentSum;
  int32_t SpecialSum;
  float smooth;
  float expvalue;
public:
  mobileWindow (int8_t _order);
  ~mobileWindow();
protected:
  void processData(int16_t inData);
  void mediapond(int16_t);
  int16_t getData();
  int16_t getSpecialdata();
  float expfilter(int16_t);
};

class lowPass : mobileWindow {
public:
  lowPass (int8_t __order);
  int16_t filter(int16_t data);
};

class highPass : mobileWindow {
public:
  highPass (int8_t __order);
  int16_t filter(int16_t data);
};

#endif // filter_h
