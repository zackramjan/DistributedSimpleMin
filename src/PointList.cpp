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

