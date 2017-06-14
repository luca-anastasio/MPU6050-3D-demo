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



ImuFilter filter(sensor);

void setup(/* arguments */) {
  Fastwire::setup(400, false);
  sensor->initialize();
  sensor->setFullScaleAccelRange(1);
  sensor->setFullScaleGyroRange(1);
  Serial.begin(115200);
  filter.setSmoothFactor(0.98, 0.999, 0.01);
  filter.setGyroOffset(200, 200, 200);
}

void loop(/* arguments */) {

   filter.run();


  Serial.print(int16_t(filter.getPitch()));
  Serial.print(" ");
  Serial.print(int16_t(filter.getRoll()));
  Serial.print(" ");
  Serial.println(int16_t(filter.getYaw()));
  Serial.flush();
  // Fix16 pitch = filter.getPitch()/133;
  // Fix16 roll = filter.getRoll()/133;
  // Fix16 yaw = filter.getYaw()/133;
  //
  // Fix16 t0 = yaw.cos();
  // Fix16 t1 = yaw.sin();
  // Fix16 t2 = roll.cos();
  // Fix16 t3 = roll.sin();
  // Fix16 t4 = pitch.cos();
  // Fix16 t5 = pitch.sin();
  //
  // Fix16 quatW = t0 * t2 * t4 + t1 * t3 * t5;
  // Fix16 quatX = t0 * t3 * t4 - t1 * t2 * t5;
  // Fix16 quatY = t0 * t2 * t5 + t1 * t3 * t4;
  // Fix16 quatZ = t1 * t2 * t4 - t0 * t3 * t5;
  //
  // char packet[14];
  //
  // packet[0] = '$';
  // packet[1] = 2;
  // packet[2] = (char)(int32_t)quatW>>16;
  // packet[3] = (char)(int32_t)quatW>>24;
  // packet[4] = (char)(int32_t)quatX>>16;
  // packet[5] = (char)(int32_t)quatX>>24;
  // packet[6] = (char)(int32_t)quatY>>16;
  // packet[7] = (char)(int32_t)quatY>>24;
  // packet[8] = (char)(int32_t)quatZ>>16;
  // packet[9] = (char)(int32_t)quatZ>>24;
  // packet[12] = '\r';
  // packet[13] = '\n';
  //
  // Serial.write(packet, 14);
}
