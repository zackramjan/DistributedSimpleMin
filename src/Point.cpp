/*
 * Point.cpp
 *
 *  Created on: Oct 30, 2015
 *      Author: zackramjan
 */

#include "Point.h"
#include <cmath>
#include <iostream>
using namespace std;

//constructor from given coordinates
Point::Point(float e, float x, float y, float z) {
	this->size = e;
	this->energy = 0.0;
	set(x,y,z);
}

//set the value of this point
void Point::set(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}


//overload "-" to return (e - distance)^2 of points "this" and "other"
//basically our "energy"
float Point::operator -(const Point other) {

	return pow(this->size - sqrt(pow(this->x - other.x,2.0) +  pow(this->y - other.y,2.0) +  pow(this->z - other.z,2.0)),2.0);
}


//print this point
void Point::print() {
	cout << size << "\t" << x << "\t" << y << "\t" << z << "\t" << endl;
}

Point::~Point() {
	// TODO Auto-generated destructor stub
}

//move this point by the specified distance
void Point::move(float i, float j, float k) {
	set(x+i,y+j,z+k);
}
