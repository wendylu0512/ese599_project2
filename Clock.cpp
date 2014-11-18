#include "stdafx.h"
#include "Clock.h"


Clock::Clock()
{
	this->t = 0;
	this->t_inc = 1;
}

Clock::Clock(double t)
{
	this->t = 0;
	this->t_inc = 1;

}

void Clock::time_increment()
{
	this->t.add(this->t_inc);

}


void Clock::set_time_inc(double t_inc)
{
	this->t_inc = t_inc;

}

void Clock::angle_change()
{
	this->angle.rotate(this->angle_turn)
}

void Clock::set_angle_turn(double angle_change)
{
	this->angle_turn = angle_turn;

	if (this->get_t() == 10)
		angle_turn = -40;

}
