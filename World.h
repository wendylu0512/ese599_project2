#ifndef WORLD_H
#define WORLD_H


#include "Coord3.h"
#include <string>

using namespace std;

class World
{
protected:
	double width, length;
	Coord3 object;
	double x_inc, y_inc;	// x and y increment of the object

public:
	World();
	World(double obj_x, double obj_y, double obj_z, double width, double length);
	World(Coord3 obj, double width, double length);

	void move_object_to(double x, double y, double z);
	void object_increment();
	void object_decrement();

	//void object_up();
	//void object_down();
	//void object_left();
	//void object_right();
	void set_object_inc(double x_inc, double y_inc);


	Coord3 get_obj() { return object; }
	double get_obj_x() { return object.get_x(); }
	double get_obj_y() { return object.get_y(); }
	double get_obj_z() { return object.get_z(); }

	double get_width() { return width; }
	double get_length() { return length; }


	string to_string();
};

#endif