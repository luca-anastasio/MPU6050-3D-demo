#include "filter.h"

mobileWindow::mobileWindow (int8_t _order) {
  order = _order;
  buffer = new int16_t[order];
  index = 0;
  smooth=0.2;
  expvalue=0;
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

float mobileWindow::expfilter(int16_t Indata) {
int16_t currentvalue=Indata;
expvalue=((smooth*currentvalue)+((1-smooth)*expvalue));
return expvalue;
}

void mobileWindow::mediapond(int16_t inData){
int8_t dividendo=1;
int8_t index2=0;
SpecialSum=0;
buffer[index]=inData;
index2=index;
for (int8_t contatore=1 ; contatore <=order ; contatore++){
  if (index==order-1)
  index2=-1;
  SpecialSum=SpecialSum+( buffer[index2+1]*(contatore/order));
dividendo++;
index2++;
if (index2==order-1) {
  index2=0;
}

}
index++;
if(index == order){
index = 0;}
}

int16_t mobileWindow::getData () {
  return (currentSum/order);
}

int16_t mobileWindow::getSpecialdata(){
  return (SpecialSum/(order/2));
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
  int16_t result=expfilter(data);
  return result;
}
