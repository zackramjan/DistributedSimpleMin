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
	float e,x,y,z;
	while (infile >> e >> x >> y >>z)
	    points.add(Point(e,x,y,z));
	return points;
}

int main(int argc, char ** argv) {
	PointList points =  readPointsFromFile(argv[0]);
}
