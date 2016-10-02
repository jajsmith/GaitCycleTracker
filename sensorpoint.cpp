#include "sensorpoint.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

SensorPoint::SensorPoint(string data) {
  //cout << "D: " << data << endl;
  stringstream ssdata(data);
  string item;
  for( int i=0; i < 7 && std::getline(ssdata, item, ','); i++ ) {
    stringstream ssitem(item);
    if (i==1) {
      if (!(ssitem >> timestamp)) {
        cout << "ERROR parsing timestamp" << endl;
      }
    } else if (i==2) {
      if (!(ssitem >> accelX)) {
        cout << "ERROR parsing acceleration X" << endl;
      }
    } else if (i==4) {
      if (!(ssitem >> accelZ)) {
        cout << "ERROR parsing acceleration Z" << endl;
      }
    } else if (i==6) {
      if (!(ssitem >> gyroY)) {
        cout << "ERROR parsing gyro Y" << endl;
      }
    }
  }
  cout << "Point(time:" << timestamp << " accelX:" << accelX << " accelZ:" << accelZ << " gyroY:" << gyroY << ")" << endl;
}
