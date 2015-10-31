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

using namespace std;

PointList::PointList() {
	this->points.clear();
	energy = 0.0;
	srand (time(NULL));
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
	if(t.energy < energy)
	{
		this->points = t.points;
		this->energy = t.energy;
	}
}

PointList::~PointList() {

}

//return the total "
float PointList::calcEnergy() {
	float e = 0.0;
	for(int i = 0; i < this->points.size(); i++)
		for(int j = 0; j < this->points.size(); j++)
			if(i != j) {
				e += (points[i] - points[j]);
			}
	energy = e;
	return e;
}

//print all the points
void PointList::print() {
	for(int i = 0; i != this->points.size(); i++)
		points.at(i).print();
}

void PointList::shake() {
	//float shakeProb = 0.1;
	float shakeProb = randFloat(probThatWeWillShake/2.0,probThatWeWillShake*2);
	for(int i = 0; i < this->points.size(); i++)
		if(randFloat(0,1) < shakeProb)
			this->points.at(i).move(randFloat(moveRangeFrom,moveRangeTo),randFloat(moveRangeFrom,moveRangeTo),randFloat(moveRangeFrom,moveRangeTo));
	calcEnergy();
}



//gen a random number with specified range
float PointList::randFloat(float M, float N)
{
    return M + (rand() / ( RAND_MAX / (N-M) ) ) ;
}

void PointList::supershake() {
	float shakeProb = randFloat(probThatWeWillShake/2.0,probThatWeWillShake*2);
	for(int i = 0; i < this->points.size(); i++)
		if(randFloat(0,1) < shakeProb)
				this->points.at(i).move(randFloat(moveRangeFrom*2,moveRangeTo*2),randFloat(moveRangeFrom*2,moveRangeTo*2),randFloat(moveRangeFrom*2,moveRangeTo*2));
	calcEnergy();

}
