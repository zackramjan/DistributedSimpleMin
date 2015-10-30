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
	std::vector<Point> points;
	std::vector<Point> pointsNew;
	float energy;
	PointList();
	void add(Point p);
	float getEnergy();
	void shake();
	virtual ~PointList();
};

#endif /* POINTLIST_H_ */
