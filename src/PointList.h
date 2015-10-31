/*
 * PointList.h
 *
 *  Created on: Oct 30, 2015
 *      Author: zackramjan
 */

#ifndef POINTLIST_H_
#define POINTLIST_H_
#include "Point.h"
#include <vector>

class PointList {
public:
	//the list of energy,x,y,z coordinates
	std::vector<Point> points;

	//holds current energy
	float energy;

	//constructor
	PointList();

	//add a new point to the list of points
	void add(Point p);

	//get the aggregate energy of the points
	float calcEnergy();

	//jitter some of the points around randomly
	void shake();

	//when we get stuck in a minima, fuck shit up
	void supershake();

	//do a trial, jitter things around, if its better then what we have, the we will MOST LIKELY accept it (but sometimes we just accept the bad shake too)
	void trial();

	//print the list
	void print();

	//decon
	virtual ~PointList();
private:
	float probThatWeWillShake = 0.1;
	float moveRangeFrom = -1.;
	float moveRangeTo = 1.;
	float randFloat(float M, float N);
};

#endif /* POINTLIST_H_ */
