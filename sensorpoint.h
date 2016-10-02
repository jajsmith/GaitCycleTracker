#ifndef __SENSORPOINT_H__
#define __SENSORPOINT_H__
#include <string>
#include <iostream>
#include <queue>

using namespace std;

// SensorPoint
// Carries a datapoint from a sensor
// Is created by passing the constructor a line formatted like this:
//      Timestamp,Timestamp (ms),accel.x,accel.y,accel.z,gyro.x,gyro.y,gyro.z,strain,analog_0,analog_1,current,enc-disp,enc-cont,enc-comm,VB,VG,Temp,Status1,Status2

class SensorPoint {
public:
  int timestamp;
  int accelX;
  int accelZ;
  int gyroY;
  string tag;

  SensorPoint(string);

};

// TODO: Overload print operator

#endif
