#ifndef CAMERA_DIST_COEFF_H
#define CAMERA_DIST_COEFF_H

#include <string>
using namespace std;

class Camera_dist_coeff
{
protected:
	double k1, k2, p1, p2, k3;

public:
	Camera_dist_coeff();
	Camera_dist_coeff(double k1, double k2, double p1, double p2, double k3);

	string to_string();

	double get_k1() { return k1; }
	double get_k2() { return k2; }
	double get_p1() { return p1; }
	double get_p2() { return p2; }
	double get_k3() { return k3; }
};

#endif