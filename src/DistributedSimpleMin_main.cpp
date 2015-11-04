//============================================================================
// Name        : ForceMinRedis.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>
#include "Point.h"
#include "PointList.h"
using namespace std;

int main(int argc, char ** argv) {
	if (argc < 4) {
		cout << "usage simplemin file.csv hazelcast_server hazel_server_port" << endl << "ex: simplemin points.csv node022.hpc.vai.org 5701"
				<< endl;
		exit(0);
	}

	PointList system;
	system.fromFile(argv[1]);
	float prevTotalEnergy = system.totalEnergy;
	int badStreak = 0;
	float badStreakMax = 10000.0;
	float badStreakThrottle = 1.0;

	for (int i = 1; i < 10000000; i++) {
		system.trial(); //do a trial

		//count the number of consecutive times a trial fails to produce a better result
		badStreak = system.totalEnergy >= prevTotalEnergy ? badStreak + 1 : 0;

		//else we had a winning trial, it was better then our previous state.
		if (badStreak == 0) {
			cout << i << " e=" << system.totalEnergy << endl;
			badStreakThrottle = badStreakThrottle > 1.1 ? badStreakThrottle / 1.01 : 1.0;
		}

		//if we hit the badStreakMax number of failures, shake things up, even if it means taking a worse result.
		else if (badStreak > badStreakMax * badStreakThrottle) {
			system.shake();
			cout << "NO GAIN for " << badStreak << "trials, taking suboptimal e=" << system.totalEnergy << endl;
			badStreakThrottle *= 1.1; //increase the throttle;
			badStreak = 0;
		}
		prevTotalEnergy = system.totalEnergy;
	}
	system.print();
}
