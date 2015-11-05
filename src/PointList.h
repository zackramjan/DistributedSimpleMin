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
#include <random>
#define MOVERANGEFROM  -1.0
#define MOVERANGETO 1.0
class PointList {
public:
	//the list of energy,x,y,z coordinates
	std::vector<Point> points;

	//holds current energy
	float totalEnergy;
	std::uniform_real_distribution<float> *randz;
	std::mt19937 *engine;

	//constructor
	PointList();

	//add a new point to the list of points
	void add(Point p);

	//get the aggregate energy of the points
	float calcEnergy();

	//jitter some of the points around randomly
	void shake();

	//do a trial, jitter things around, if its better then what we have, the we will MOST LIKELY accept it (but sometimes we just accept the bad shake too)
	void trial();

	//print the list
	void print();

	//return the state of this systen as a string
	std::string toString();

	//set the state of this system from the given string
	void fromString(std::string from);

	//set the state of this system from the given file
	void fromFile(std::string from);

	//generate a random flout between M and N
	float randFloat(float M, float N);


	//decon
	virtual ~PointList();
private:
	float moveRangeFrom;// = -1.;
	float moveRangeTo; // = 1.;
	float randomAcceptSubOptimal;
	//add a new point to the list of points without updating energy calc
	void addNoRecalc(Point p);


	static bool wayToSort(Point l, Point r);
};

#endif /* POINTLIST_H_ */
