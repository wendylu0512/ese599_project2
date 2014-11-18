#include "stdafx.h"
#include "Coord3.h"

Coord3::Coord3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Coord3::Coord3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Coord3::move(double x_inc, double y_inc, double z_inc)
{
	this->x += x_inc;
	this->y += y_inc;
	this->z += z_inc;
}

void Coord3::reset_position(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

string Coord3::to_string()
{
	return (Coord2::to_string()) + std::to_string(z);
}