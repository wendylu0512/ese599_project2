#include "stdafx.h"
#include "Coord2.h"

Coord2::Coord2()
{
	this->x = 0;
	this->y = 0;
}

Coord2::Coord2(double x, double y)
{
	this->x = x;
	this->y = y;
}

void Coord2::move(double x_inc, double y_inc)
{
	this->x += x_inc;
	this->y += y_inc;
}

void Coord2::reset_position(double x, double y)
{
	this->x = x;
	this->y = y;
}

std::string Coord2::to_string()
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}