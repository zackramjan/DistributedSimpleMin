/*
 * PointList.cpp
 *
 *  Created on: Oct 30, 2015
 *      Author: zackramjan
 */

#include "PointList.h"
#include "Point.h"
#include <algorithm>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sstream>
#include <fstream>

using namespace std;

PointList::PointList() {
	this->points.clear();
	totalEnergy = 0.0;
	srand (time(NULL));
	moveRangeFrom = MOVERANGEFROM;
	moveRangeTo = MOVERANGETO;
}

//add a point to the list
void PointList::add(Point p) {
	this->points.push_back(p);
	calcEnergy();
}

void PointList::trial() {
	PointList t;
	t.points = points;
	t.shake();
	if(t.totalEnergy < totalEnergy)
	{
		this->points = t.points;
		this->totalEnergy = t.totalEnergy;
	}
	else if( randFloat(0.0,20000.0) < 1.0)
	{
		this->points = t.points;
		this->totalEnergy = t.totalEnergy;
		cout << "randomly taking suboptimal e=" << this->totalEnergy << endl;
	}
}

PointList::~PointList() {}

//return the total energy
float PointList::calcEnergy() {
	totalEnergy = 0.0;
	for(size_t i = 0; i < this->points.size(); i++)
	{
		points[i].energy = 0.0;
		for(size_t j = 0; j < this->points.size(); j++)
			if(i != j)
				points[i].energy += (points[i] - points[j]); // "-" is overloaded in Point to calculate force between 2 points, see Points.cpp::operator-().
		totalEnergy += points[i].energy;
	}
	sort(points.begin(),points.end(),wayToSort);
	return totalEnergy;
}

//print all the points
void PointList::print() {
	for(size_t i = 0; i != this->points.size(); i++)
		points.at(i).print();
}


void PointList::shake() {
	for(size_t i = 0; i < this->points.size(); i++)
		if(randFloat(0,this->points.size()*2.0) < 0.0+i+(points.size()*0.1)) //the higher the energy of the point, the more likely we will shake it.
			this->points.at(i).move(randFloat(moveRangeFrom,moveRangeTo),randFloat(moveRangeFrom,moveRangeTo),randFloat(moveRangeFrom,moveRangeTo)); //move point a little bit
	calcEnergy();
}

//gen a random number with specified range
float PointList::randFloat(float M, float N)
{
    return M + (rand() / ( RAND_MAX / (N-M) ) ) ;
}

bool PointList::wayToSort(Point l, Point r) {
	return l.energy < l.energy;
}

//return this list as a string
std::string PointList::toString() {
	std::ostringstream buff;
	for(size_t i = 0; i < this->points.size(); i++)
		buff << points.at(i).toString() << endl;
	 return buff.str();

}

//create this list form the given string
void PointList::fromString(std::string from) {
	points.clear();
	istringstream buff (from);
	string line;
	while(getline(buff,line))
		this->add(Point(line));

}

//import this list from the given file
void PointList::fromFile(std::string from) {
	ifstream infile(from);
	cout << "opening " << from << endl;
	float e, x, y, z;
	while (infile >> e >> x >> y >> z) {
		this->add(Point(e, x, y, z));
	}
}
