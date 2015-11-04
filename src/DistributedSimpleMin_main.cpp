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
#include "DistributedMap.h"
using namespace std;

int main(int argc, char ** argv) {
	if (argc < 4) {
		cout << "usage simplemin file.csv hazelcast_server hazel_server_port" << endl << "ex: simplemin points.csv node022.hpc.vai.org 5701" << endl;
		exit(0);
	}

	//read in the system coords from file
	PointList system;
	system.fromFile(argv[1]);

	//create the connection to a hazelcast server node.
	//We want the Keys:Values to be String:String in this case
	DistributedMap<string,string> cluster(argv[2],stoi(argv[3],NULL));

	//assign this process a unique id to identify itself amongst the other processes working
	long machineID = cluster.getUniqueID();
	cout << "unique instance ID for this worker: " << machineID <<endl;

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
			cluster.put(to_string(machineID),system.toString()); //save this result to the cluster
		}

		//if we hit the badStreakMax number of failures, Then grab a new state from the cluster.
		else if (badStreak > badStreakMax * badStreakThrottle) {
			vector<string> keys = cluster.getKeys();
			for(size_t i=0;i<keys.size();i++)
			{
				PointList t;
				t.fromString(cluster.get(keys.at(i)));
				if(t.totalEnergy < system.totalEnergy)
				{
					cout << "replacing state with current state e=" << system.totalEnergy << " with instance " << keys.at(i) << " e=" << t.totalEnergy << endl;
					system.fromString(t.toString());
				}
			}
		}
		prevTotalEnergy = system.totalEnergy;
	}
	system.print();
}
