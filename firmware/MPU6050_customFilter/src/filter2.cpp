#include "filter2.h"

complementaryFilter::complementaryFilter () {
  gyroOffset = 0;
  timeInterval = 0;
  gyroCalcOffset = 0;
}

void complementaryFilter::setSmoothFactor(Fix16 smooth) {
  smoothFactor = smooth;
  smoothFactorComp = Fix16(1) - smooth;
}

Fix16 complementaryFilter::filterData(int16_t Gyro, int16_t AccA, int16_t AccB) {
  Fix16 filteredGyro = Fix16(Gyro) - gyroCalcOffset;
  if ( abs(int16_t(filteredGyro)) < gyroOffset ) {
    gyroCalcOffset = smoothFactorComp*Fix16(Gyro) + smoothFactor*gyroCalcOffset;
  }
  Fix16 AccAngle = Fix16(AccA).atan2(Fix16(AccB)) *radToDeg;
  Fix16 dt = Fix16( int16_t(millis()-timeInterval) ) / 10000;
  averageValue = smoothFactor*(averageValue + (filteredGyro*dt) ) + smoothFactorComp*AccAngle;
  return averageValue;
}

void complementaryFilter::setGyroOffset(int16_t offset) {
  gyroOffset = offset;
}

ImuFilter::ImuFilter(MPU6050* _imu) {
  imu = _imu;
  ax = new int16_t;
  ay = new int16_t;
  az = new int16_t;
  gx = new int16_t;
  gy = new int16_t;
  gz = new int16_t;
}

Fix16 ImuFilter::getPitch() {
  return Pitch;
}

Fix16 ImuFilter::getRoll() {
  return Roll;
}

Fix16 ImuFilter::getYaw() {
  return Yaw;
}

void ImuFilter::setGyroOffset(int16_t x, int16_t y, int16_t z) {
  PitchFilter.setGyroOffset(x);
  RollFilter.setGyroOffset(y);
  YawFilter.setGyroOffset(z);
}

void ImuFilter::setSmoothFactor(Fix16 smooth) {
  PitchFilter.setSmoothFactor(smooth);
  RollFilter.setSmoothFactor(smooth);
  YawFilter.setSmoothFactor(smooth);
}

void ImuFilter::run() {
  imu->getMotion6(ax, ay, az, gx, gy, gz);
  Pitch = PitchFilter.filterData(*gx, *ay, *az);
  Roll = RollFilter.filterData(-*gy, *ax, *az);
  Yaw = YawFilter.filterData(*gz, *ax, *ay);
}
