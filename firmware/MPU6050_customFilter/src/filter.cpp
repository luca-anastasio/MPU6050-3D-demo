#include "filter.h"

mobileWindow::mobileWindow (int8_t _order) {
  order = _order;
  buffer = new int16_t[order];
  index = 0;
}

mobileWindow::~mobileWindow() {
  delete buffer;
}

void mobileWindow::processData (int16_t inData) {
  currentSum += inData;
  currentSum -= buffer[index];
  buffer[index] = inData;
  index++;
  if(index > order) index = 0;
}

int16_t mobileWindow::getData () {
  return (currentSum/order);
}

lowPass::lowPass (int8_t __order) : mobileWindow(__order) {
}

int16_t lowPass::filter (int16_t data) {
  processData(data);
  return getData();
}

highPass::highPass (int8_t __order) : mobileWindow(__order) {
}

int16_t highPass::filter (int16_t data) {
  processData(data);
  int16_t returnValue = data - getData();
  return returnValue;
}
