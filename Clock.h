#ifndef CLOCK_H
#define CLOCK_H

#include <string>
using namespace std;

class Clock
{
protected:
	
	double t_inc;	// time increment 
	double angle_turn; //angle change
	double t;
	double angle;

public:
	Clock();
	Clock(double t);


	void time_increment();
	void angle_change();
	void add(double t_inc);
	void rotate(double angle_turn);
	void set_time_inc(double t_inc);
	void set_angle_turn(double angle_turn);

	double get_t() { return t; }
	double get_angle() { return angle; }
	

};

#endif