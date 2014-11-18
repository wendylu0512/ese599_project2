#include "stdafx.h"
#include "Screen.h"

Screen::Screen()
{
	this->bottom_right = Coord2(100, 100);
	this->top_left = Coord2(0, 0);
}

Screen::Screen(Coord2 top_left, Coord2 bottom_right, double s)
{
	this->bottom_right = bottom_right;
	this->top_left = top_left;
	this->s = s;
}

Screen::Screen(Coord2 top_left, double width, double height, double s)
{
	this->top_left = top_left;
	this->bottom_right = Coord2((top_left.get_x() + width) , (top_left.get_y() + height));
	this->s = s;
}