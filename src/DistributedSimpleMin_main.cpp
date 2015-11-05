//============================================================================
// Name        : DistributedSimpleMin_main.cpp
// Author      :  Zack Ramjan
// Version     :
// Copyright   : Your copyright notice
// Description : hazelcast aware distributed random min
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
	PointList system; //my system
	system.fromFile(argv[1]); //intially populate the system from file

	//create the connection to a hazelcast server node.
	//We want the Keys:Values to be String:String in this case
	//cluster(localhost, 5901)
	DistributedMap<string,string> cluster(argv[2],stoi(argv[3],NULL));

	//assign this process a unique id to identify itself amongst the other processes working
	long machineID = cluster.getUniqueID();
	cout << "this process has workerID=" << machineID <<endl;

	float prevTotalEnergy = system.totalEnergy;
	int badStreak = 0; //my counter for failed trials
	float badStreakMax = 10000.0; //how many failed trials I accept before taking another workers state
	float badStreakThrottle = 1.0; //a throttle so that we can adjust badSteakMax

	for (int i = 1; i < 10000000; i++) {
		system.trial(); //do a trial

		//count the number of consecutive times a trial fails to produce a better result
		badStreak = system.totalEnergy >= prevTotalEnergy ? badStreak + 1 : 0;

		//else we had a winning trial, it was better then our previous state.
		if (badStreak == 0) {
			cout << i << " e=" << system.totalEnergy << endl;
			badStreakThrottle = badStreakThrottle > 1.1 ? badStreakThrottle / 1.01 : 1.0;
			cluster.put(to_string(machineID),system.toString()); //save this workers state to the cluster. They key is the machineID.
		}

		//if we hit the badStreakMax number of failures, Then grab a new state from the cluster.
		else if (badStreak > badStreakMax * badStreakThrottle) {
			vector<string> keys = cluster.getKeys(); //get a list of all the workerIDs from the cluster
			for(size_t j=0;j<keys.size();j++) //for each workerID in the cluster
			{
				PointList t;
				t.fromString(cluster.get(keys.at(j))); //create a new system from the workerID's state
				if(t.totalEnergy < system.totalEnergy) //is is better then what I currently have?
				{
					cout << i << " replacing this state e=" << system.totalEnergy << " with workerID=" << keys.at(j) << "'s state e=" << t.totalEnergy << endl;
					system.fromString(t.toString());
				}
			}
			badStreak=0; //reset our counter
		}
		prevTotalEnergy = system.totalEnergy;
	}
	system.print();
}
