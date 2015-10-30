/*
 * PointList.cpp
 *
 *  Created on: Oct 30, 2015
 *      Author: zackramjan
 */

#include "PointList.h"

PointList::PointList() {
	this->points.clear();

}

void PointList::add(Point p) {
	this->points.push_back(p);
}

PointList::~PointList() {
	// TODO Auto-generated destructor stub
}

//return the total "
float PointList::getEnergy() {
	float e = 0.0;
	for(int i = 0; i != this->points.size(); i++)
		for(int j = 0; j != this->points.size(); j++)
			if(i != j)
				e += (points[i] - points[j]);
	energy = e;
	return e;
}

void PointList::shake() {

}
