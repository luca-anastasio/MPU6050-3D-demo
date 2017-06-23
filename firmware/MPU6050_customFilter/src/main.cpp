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

#define FILTER_DEMO_OUTPUT
//#define PROCESING_OUTPUT

#if ( defined(FILTER_DEMO_OUTPUT) && defined(PROCESING_OUTPUT))
  #error "only one at time"
#endif

ImuFilter filter(sensor);
Integrator pitchIntegrator(0);

void setup(/* arguments */) {
  Fastwire::setup(400, false);
  sensor->initialize();
  sensor->setFullScaleAccelRange(1);
  sensor->setFullScaleGyroRange(1);
  Serial.begin(115200);

  filter.setSmoothFactor(0.9, 0.999, 0.01);
  filter.setGyroOffset(200, 200, 200);
}

void loop(/* arguments */) {

  filter.run();
  Serial.flush();
  Serial.print(int16_t(filter.getPitch()));
  Serial.print(" ");
  #ifdef PROCESING_OUTPUT
  Serial.print(int16_t(filter.getRoll()));
  Serial.print(" ");
  Serial.print(int16_t(filter.getYaw()));
  Serial.println(" ");
  #endif

  #ifdef FILTER_DEMO_OUTPUT
  int16_t gyroPitch = pitchIntegrator.integrate(sensor->getRotationX());
  Serial.print(gyroPitch);
  Serial.print(" ");
  Fix16 ay = Fix16(sensor->getAccelerationY());
  Fix16 az = Fix16(sensor->getAccelerationZ());
  int16_t accPitch = int16_t(ay.atan2(az)*fix16_rad_to_deg_mult*80);
  Serial.println(accPitch);
  #endif

  delay(50);

}
