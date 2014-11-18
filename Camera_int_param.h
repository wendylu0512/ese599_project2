#ifndef CAMERA_INT_PARAM_H
#define CAMERA_INT_PARAM_H

#include <string>
using namespace std;

class Camera_int_param
{
protected:
	double cx, cy;
	double fx, fy;

public:
	Camera_int_param();
	Camera_int_param(double cx, double cy, double fx, double fy);

	string to_string();

	double get_cx() { return cx; }
	double get_cy() { return cy; }
	double get_fx() { return fx; }
	double get_fy() { return fy; }
};

#endif