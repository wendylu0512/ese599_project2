#include "stdafx.h"
#include "World.h"

 default world:
// width = 1000, length = 1000, object at (500, 500)
World::World()
{
	this->object = Coord3(500, 500, 0);
	this->width = 1000;
	this->length = 1000;
	this->x_inc = 50;
	this->y_inc = 100;
}

World::World(double obj_x, double obj_y, double obj_z, double width, double length)
{
	this->object = Coord3(obj_x, obj_y, obj_z);
	this->width = width;
	this->length = length;
	this->x_inc = 50;
	this->y_inc = 100;

}

World::World(Coord3 obj, double width, double length)
{
	this->object = obj;
	this->width = width;
	this->length = length;
	this->x_inc = 50;
	this->y_inc = 100;
}

void World::move_object_to(double x, double y, double z)
{
	this->object.reset_position(x, y, z);
}

string World::to_string()
{
	return "WIDTH: " + std::to_string(width) + "\tLENGTH: " + std::to_string(length)
		+ "\nOBJECT AT: " + this->object.to_string();
}


void World::object_increment()
{
	this->object.move(this->x_inc, this->y_inc, 0);
	
	if (this->get_obj_x() < 20)
		x_inc *= -1;
	else if (this->get_obj_x() > width - 20)
		x_inc *= -1;
	else if (this->get_obj_y() < 20)
		y_inc *= -1;
	else if (this->get_obj_y() > length - 20)
		y_inc *= -1;
}  

void World::object_decrement()
{
	this->object.move(-(this->x_inc), -(this->y_inc), 0);

	if (this->get_obj_x() < 20)
		x_inc *= -1;
	else if (this->get_obj_x() > width - 20)
		x_inc *= -1;
	else if (this->get_obj_y() < 20)
		y_inc *= -1;
	else if (this->get_obj_y() > length - 20)
		y_inc *= -1;
}  


/*
void World::object_up()
{
	this->object.move(0, (this->y_inc), 0);

	if (this->get_obj_x() < 20)
		x_inc *= -1;
	else if (this->get_obj_x() > width - 20)
		x_inc *= -1;
	else if (this->get_obj_y() < 20)
		y_inc *= -1;
	else if (this->get_obj_y() > length - 20)
		y_inc *= -1;
}

void World::object_down()
{
	this->object.move(0, -(this->y_inc), 0);

	if (this->get_obj_x() < 20)
		x_inc *= -1;
	else if (this->get_obj_x() > width - 20)
		x_inc *= -1;
	else if (this->get_obj_y() < 20)
		y_inc *= -1;
	else if (this->get_obj_y() > length - 20)
		y_inc *= -1;
}

void World::object_left()
{
	this->object.move(-(this->x_inc), 0, 0);

	if (this->get_obj_x() < 20)
		x_inc *= -1;
	else if (this->get_obj_x() > width - 20)
		x_inc *= -1;
	else if (this->get_obj_y() < 20)
		y_inc *= -1;
	else if (this->get_obj_y() > length - 20)
		y_inc *= -1;
}

void World::object_right()
{
	this->object.move((this->x_inc), 0, 0);

	if (this->get_obj_x() < 20)
		x_inc *= -1;
	else if (this->get_obj_x() > width - 20)
		x_inc *= -1;
	else if (this->get_obj_y() < 20)
		y_inc *= -1;
	else if (this->get_obj_y() > length - 20)
		y_inc *= -1;
}

*/

void World::set_object_inc(double x_inc, double y_inc)
{
	this->x_inc = x_inc;
	this->y_inc = y_inc;
}