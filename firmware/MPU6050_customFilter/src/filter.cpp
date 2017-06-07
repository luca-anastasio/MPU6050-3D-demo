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
void mobileWindow::mediapond(int16_t inData){
int8_t contatore=0;
int8_t dividendo=1;
if (index==order)
index=-1;
for (int8_t i = index +1; contatore < order ; i++){
SpecialSum= buffer[i]*(contatore/order);
contatore++;
dividendo++;
if (i==order) {
  i=0;
}
}
}

int16_t mobileWindow::getData () {
  return (currentSum/order);
}

int16_t mobileWindow::getSpecialdata(){
  return (SpecialSum/order);
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
  mediapond(data);
  int16_t returnValue = data - getSpecialdata();
  return returnValue;
}
