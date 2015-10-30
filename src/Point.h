/*
 * Point.h
 *
 *  Created on: Oct 30, 2015
 *      Author: zackramjan
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
public:
	Point(float e, float x, float y, float z);
	float operator-(const Point other);
	virtual ~Point();
	float e;
	float x;
	float y;
	float z;
};

#endif /* POINT_H_ */
