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
	PointList();
	void add(Point p);
	virtual ~PointList();
};

#endif /* POINTLIST_H_ */
