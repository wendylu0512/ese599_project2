#include "stdafx.h"
#include "Camera_dist_coeff.h"

Camera_dist_coeff::Camera_dist_coeff()
{
	k1 = 0;
	k2 = 0;
	p1 = 0;
	p2 = 0;
	k3 = 0;
}

Camera_dist_coeff::Camera_dist_coeff(double k1, double k2, double p1, double p2, double k3)
{
	this->k1 = k1;
	this->k2 = k2;
	this->p1 = p1;
	this->p2 = p2;
	this->k3 = k3;
}

string Camera_dist_coeff::to_string()
{
	return "k1:" + std::to_string(k1) + " k2:" + std::to_string(k2)
		+ " p1:" + std::to_string(p1) + " p2:" + std::to_string(p2)
		+ " k3:" + std::to_string(k3);
}