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
using namespace std;

int main(int argc, char ** argv) {
	vector<Point> points =  readPointsFromFile(argv[0]);





	return 0;
}


vector<Point> readPointsFromFile(char *filename)
{
	vector<Point> points;
	ifstream infile(filename);
	float e,x,y,z;
	while (infile >> e >> x >> y >>z)
	{
	    points.push_back(Point(e,x,y,z));
	}
	return points;
}


