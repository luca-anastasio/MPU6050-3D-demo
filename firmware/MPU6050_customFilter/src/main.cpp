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
#include "filter.h"

MPU6050 sensor;
highPass exampleFilter(8);

void setup(/* arguments */) {
  Fastwire::setup(400, false);
  sensor.initialize();
  Serial.begin(115200);
}

void loop(/* arguments */) {
  int16_t rawData = sensor.getRotationY();
  int16_t smoothData = exampleFilter.filter(rawData);

  Serial.print(rawData);
  Serial.print(" ");
  Serial.println(smoothData);
  delay(100);
}
