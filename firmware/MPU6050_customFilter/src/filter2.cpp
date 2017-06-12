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

Fix16 complementaryFilter::filterData(Fix16 & Gyro, Fix16 & AccA, Fix16 & AccB) {
  Fix16 filteredGyro = Gyro - gyroCalcOffset;
  if ( abs(int16_t(filteredGyro)) < gyroOffset ) {
    gyroCalcOffset = smoothFactorComp*Gyro + smoothFactor*gyroCalcOffset;
  }
  Fix16 AccAngle = AccA.atan2(AccB) *fix16_rad_to_deg_mult;
  Fix16 dt = Fix16( int16_t(millis()-timeInterval) ) / 1000;
  averageValue = smoothFactor*(averageValue /*+ (filteredGyro*dt)*/ ) + smoothFactorComp*AccAngle;
  timeInterval = millis();
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
  AccX = *ax;
  AccY = *ay;
  AccZ = *az;
  GyroX = *gx;
  GyroY = *gy;
  GyroZ = *gz;
  Pitch = PitchFilter.filterData(GyroX, AccY, AccZ);
  Roll = RollFilter.filterData(GyroY, AccX, AccZ);
  Yaw = YawFilter.filterData(GyroZ, AccX, AccY);
}
