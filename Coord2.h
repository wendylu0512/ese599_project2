#ifndef COORD2_H
#define COORD2_H

#include <string>

using namespace std;

class Coord2
{
protected:
	double x;
	double y;

public:
	Coord2();
	Coord2(double x, double y);

	void move(double x_inc, double y_inc);
	void reset_position(double x, double y);
	string to_string();

	double get_x() { return x; }
	double get_y() { return y; }
};

#endif