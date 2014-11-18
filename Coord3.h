#ifndef COORD3_H
#define COORD3_H

#include "Coord2.h"
#include <string>
using namespace std;

class Coord3 :Coord2
{
protected:
	double z;

public:
	Coord3();
	Coord3(double x, double y, double z);

	void move(double x_inc, double y_inc, double z_inc);
	void reset_position(double x, double y, double z);
	string to_string();

	double get_x() { return Coord2::get_x(); }
	double get_y() { return Coord2::get_y(); }
	double get_z() { return z; }
};

#endif