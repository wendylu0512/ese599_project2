#include "stdafx.h"
#include "Camera_int_param.h"

Camera_int_param::Camera_int_param()
{
	cx = 0;
	cy = 0;
	fx = 0;
	fy = 0;
}

Camera_int_param::Camera_int_param(double cx, double cy, double fx, double fy)
{
	this->cx = cx;
	this->cy = cy;
	this->fx = fx;
	this->fy = fy;
}

string Camera_int_param::to_string()
{
	return "cx:" + std::to_string(cx) + " cy:" + std::to_string(cy)
		+ " fx" + std::to_string(fx) + " fy:" + std::to_string(fy);
}