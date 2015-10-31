//============================================================================
// Name        : ForceMinRedis.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include "Point.h"
#include "PointList.h"
using namespace std;




PointList readPointsFromFile(char *filename)
{
	PointList points;
	ifstream infile(filename);
	cout << "opening " << filename <<endl;
	float e,x,y,z;
	while (infile >> e >> x >> y >>z)
	{
		points.add(Point(e,x,y,z));
	}
	return points;
}

int main(int argc, char ** argv) {
	PointList system =  readPointsFromFile(argv[1]);
	float energy = system.energy;
	int badStreak = 0;
	float badStreakMax = 10000.0;

	for (int i=1;i<10000000;i++)
	{
		system.trial(); //do a trial

		//count the number of consecutive times a trial fails to produce a better result
		if (energy == system.energy)
			badStreak++;

		//else we had a winning trial, it was better then our previous state.
		else
		{
			cout << i << " e=" << system.energy <<endl;
			badStreak = 0;
		}

		//if we hit the badStreakMax number of failures, shake things up, even if it means taking a worse result.
		if(badStreak > badStreakMax)
		{
			system.supershake();
			cout << "NO GAIN for " << badStreakMax  << "trials, taking suboptimal e=" << system.energy <<  endl;
			badStreak = 0;
			badStreakMax = badStreakMax * 1.1; //increase the throttle
		}
		energy=system.energy;
	}

	system.print();
}
