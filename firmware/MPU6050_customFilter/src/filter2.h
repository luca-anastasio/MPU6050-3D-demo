#ifndef filter2_h
#define filter2_h

#include <fixmath.h>
#include <Arduino.h>
#include <MPU6050.h>

class complementaryFilter {
private:
  Fix16 smoothFactor, smoothFactorComp, gyroCalcOffset, averageValue;
  uint32_t timeInterval;
  int16_t gyroOffset;
public:
  complementaryFilter();
  void setSmoothFactor(Fix16 smooth);
  Fix16 filterData(Fix16 & Gyro, Fix16 & AccA, Fix16 & AccB);
  void setGyroOffset(int16_t offset);
};

class ImuFilter {
private:
  Fix16 AccX, AccY, AccZ,
        GyroX, GyroY, GyroZ,
        Pitch, Roll, Yaw;
  int16_t *ax, *ay, *az, *gx, *gy, *gz;
  MPU6050* imu;
  complementaryFilter PitchFilter, RollFilter, YawFilter;
public:
  ImuFilter(MPU6050* _imu);
  Fix16 getPitch();
  Fix16 getRoll();
  Fix16 getYaw();
  void setGyroOffset(int16_t x, int16_t y, int16_t z);
  void setSmoothFactor(Fix16 smooth);
  void run();
};

#endif // filter2_h
