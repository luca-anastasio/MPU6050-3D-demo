// Copyright (c) 2017 Luca Anastasio
//
// GNU GENERAL PUBLIC LICENSE
//    Version 3, 29 June 2007
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <I2Cdev.h>
#include <MPU6050.h>
#include "filter2.h"

MPU6050 *sensor = new MPU6050();

// highPass GyroFilterX(Fix16(0.01), 100);
// lowPass AccFilterX(Fix16(0.9));
// complementaryFilter CompFilterX(Fix16(0.5));
//
// highPass GyroFilterY(Fix16(0.01), 100);
// lowPass AccFilterY(Fix16(0.9));
// complementaryFilter CompFilterY(Fix16(0.5));
//
// highPass GyroFilterZ(Fix16(0.01), 100);
// lowPass AccFilterZ(Fix16(0.9));
// complementaryFilter CompFilterZ(Fix16(0.5));

ImuFilter filter(sensor);

void setup(/* arguments */) {
  Fastwire::setup(400, false);
  sensor->initialize();
  sensor->setFullScaleAccelRange(3);
  sensor->setFullScaleGyroRange(3);
  Serial.begin(115200);
  filter.setSmoothFactor(0.99);
  filter.setGyroOffset(200, 200, 200);
}

void loop(/* arguments */) {

  // int16_t GyroX = GyroFilterX.filterData(sensor.getRotationX());
  // int16_t GyroY = GyroFilterY.filterData(sensor.getRotationY());
  // int16_t GyroZ = GyroFilterZ.filterData(sensor.getRotationZ());
  //
  // int16_t AccX = AccFilterX.filterData(sensor.getAccelerationX());
  // int16_t AccY = AccFilterY.filterData(sensor.getAccelerationY());
  // int16_t AccZ = AccFilterZ.filterData(sensor.getAccelerationZ());
  //
  // int16_t X = CompFilterX.filterData(GyroX, AccX);
  // int16_t Y = CompFilterY.filterData(GyroY, AccY);
  // int16_t Z = CompFilterZ.filterData(GyroZ, AccZ);
  //
  // Serial.print(X);
  // Serial.print(" ");
  // Serial.print(Y);
  // Serial.print(" ");
  // Serial.println(Z);

  filter.run();
  Serial.print(int16_t(filter.getPitch()));
  Serial.print(" ");
  Serial.print(int16_t(filter.getRoll()));
  Serial.print(" ");
  Serial.println(int16_t(filter.getYaw()));

  delay(50);
}
