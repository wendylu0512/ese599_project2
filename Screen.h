#ifndef SCREEN_H
#define SCREEN_H

#include "Coord2.h"

class Screen
{
private:
	Coord2 top_left;
	Coord2 bottom_right;
	double s;

public:
	Screen();
	Screen(Coord2 top_left, Coord2 bottom_right, double s);
	Screen(Coord2 top_left, double width, double height, double s);

	Coord2 get_top_left() { return top_left; }
	Coord2 get_bottom_right() { return bottom_right; }

	int get_width() { return (int)(bottom_right.get_x() - top_left.get_x()); }
	int get_height() { return (int)(bottom_right.get_y() - top_left.get_y()); }

	int get_top() { return (int)top_left.get_y(); }
	int get_bottom() { return (int)bottom_right.get_y(); }
	int get_left() { return (int)top_left.get_x(); }
	int get_right() { return (int)bottom_right.get_x(); }

	double get_s() { return s; }
};

#endif
