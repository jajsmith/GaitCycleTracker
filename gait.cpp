// GaitCycleTracker
// by Jonathan Smith
// 2016-10-01
//
// Compiles to gait
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include "sensorpoint.h"

using namespace std;
bool DEBUG = false;

int BASELINE_ACCEL_X = -3800;
int BASELINE_ACCEL_Z = 0;
int BASELINE_GYRO_Y = 0;

// Input:
// CSV with the following header:
//      [Datalogging: Item = 0 | Slave index = 0 (Execute 1) | Experiment index = 0 (Read All (Barebone))]
//      Timestamp,Timestamp (ms),accel.x,accel.y,accel.z,gyro.x,gyro.y,gyro.z,strain,analog_0,analog_1,current,enc-disp,enc-cont,enc-comm,VB,VG,Temp,Status1,Status2
// Streamed line by line
// eg:
//    `cat walkData1.csv | gait`

// Use accel.x, accel.z, gyro.y for v1

// Data Analysis:
//     Heel strike occurs when accel.x, accel.z, gyro.y all reach local minimums
//     within a short time of each other.

// Algorithm:
//     1. gyro.y reaches local minimum with negative value (enable: Heel Strike Detect)
//     2. accel.x reaches local minimum with negative value
//     3. accel.z reaches local minimum with negative value
//     4. if (accel.z < 0 && accel.x < 0):
//     5.     Heel Strike Detected!
//     2. gyro.y reaches local max with positive value (disable: Heel Strike Detect)



int main(int argc, char* argv[]){
	cout << "Welcome to Gait Cycle Tracker!" << endl;
	int heelStrikesDetected = 0;
	string line;

	list<SensorPoint*> points;
	bool stdSet = false;
	//Local Minimums
	SensorPoint* lmAccelX;
	SensorPoint* lmAccelZ;
	SensorPoint* lmGyroY;
	bool heelStrikeDetect = true;



	// Expect Two Header lines
  getline(cin,line);
  cout << "HEADER1: " << line << endl;
  getline(cin,line);
  cout << "HEADER2: " << line << endl;


	while ( std::getline(cin, line) ) {
		// Add data point to data structure
		if (line.empty()) break;
		SensorPoint* s = new SensorPoint(line);

		// Set initial data point if necessary
		if (points.empty()) {
			points.push_front(s);
			continue;
		}

		// Set local mins
		int lastGyroY = points.front()->gyroY;
		if ( (s->gyroY > lastGyroY) && (s->gyroY < BASELINE_GYRO_Y) ) {
			if ( (lmGyroY == 0) || (lastGyroY < lmGyroY->gyroY) ) {
				lmGyroY = points.front();
				heelStrikeDetect = true;
			}
		}

		int lastAccelZ = points.front()->accelZ;
		if ( (s->accelZ > lastAccelZ) && (s->accelZ < BASELINE_ACCEL_Z) ) {
			if ( (lmAccelZ == 0) || (lastAccelZ < lmAccelZ->accelZ) ) {
				lmAccelZ = points.front();
			}
		}

		int lastAccelX = points.front()->accelX;
		if ( (s->accelX > lastAccelX) && (s->accelX < BASELINE_ACCEL_X) ) {
			if ( (lmAccelX == 0) || (lastAccelX < lmAccelX->accelX) ) {
				lmAccelX = points.front();
			}
		}

		// Look for Heel Strike
		if ( (lmGyroY != 0) && (lmAccelZ != 0) && (lmAccelX != 0) && heelStrikeDetect ) {
			cout << "Heel Strike Detected at " << s->timestamp << "ms!" << endl;
			++heelStrikesDetected;
			heelStrikeDetect = false;
			// reset local mins
			lmGyroY = 0;
			lmAccelX = 0;
			lmAccelZ = 0;
		}

		points.push_front(s);
		// TODO: Cull points from list when they fade from relevance
		//points.pop_back();
	}

	cout << "Total Heel Strikes Detected: " << heelStrikesDetected << endl;
	//Clean up list
	while( !points.empty() ) {
		delete points.front();
		points.pop_front();
	}
}
