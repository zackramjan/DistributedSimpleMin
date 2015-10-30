/*
 * Point.cpp
 *
 *  Created on: Oct 30, 2015
 *      Author: zackramjan
 */

#include "Point.h"
#include <cmath>

Point::Point(float e, float x, float y, float z) {
	this->e = e;
	this->x = x;
	this->y = y;
	this->z = z;

}

//overload "-" to return (e - distance)^2 of points "this" and "other"
//basically our "energy"
float Point::operator -(const Point other) {

	return pow(this->e - sqrt(pow(this->x - other.x,2.0) +  pow(this->y - other.y,2.0) +  pow(this->z - other.z,2.0)),2.0);
}

Point::~Point() {
	// TODO Auto-generated destructor stub
}

