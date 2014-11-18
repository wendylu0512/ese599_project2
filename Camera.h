#ifndef Camera_H
#define Camera_H

#include "Coord3.h"
#include "Camera_int_param.h"
#include "Camera_dist_coeff.h"
#include "World.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define PI 3.14159265

class Camera
{
private:
	Camera_int_param int_param;		// intrinsic parameter
	Camera_dist_coeff dist_coeff;	// distortion coefficient
	Coord3 coordinate;	// camera position in world
	double pan, tilt;	// pan and tilt in radian
	double res_w, res_h;	// resolution (width, height)
	double intrinsic_matrix[3][3];
	double rotation_matrix[3][3];
	double inverse_intrinsic_matrix[3][3];
	double inverse_rotation_matrix[3][3];
	Coord2 top_left_corner, top_right_corner, bottom_left_corner, bottom_right_corner;	// world coordinates of screen corners
	Coord2 top_right_cover, bottom_left_cover;	// camera coverage in world
	vector<int> zones_covered;

public:
	Camera();
	Camera(Camera_int_param int_param, Camera_dist_coeff dist_coeff, Coord3 coordinate,
		double pan, double tilt, double res_w, double res_h);
	Camera(double cx, double cy, double fx, double fy, double k1, double k2, double k3,
		double p1, double p2, double x, double y, double z, double pan, double tilt,
		double res_w, double res_h);

	void moveTo(double x, double y, double z);
	void moveTo(double pan, double tilt);
	void moveTo(double x, double y, double z, double pan, double tilt);

	Coord3 get_coord() { return coordinate; }

	double get_cx() { return int_param.get_cx(); }
	double get_cy() { return int_param.get_cy(); }
	double get_fx() { return int_param.get_fx(); }
	double get_fy() { return int_param.get_fy(); }

	double get_k1() { return dist_coeff.get_k1(); }
	double get_k2() { return dist_coeff.get_k2(); }
	double get_k3() { return dist_coeff.get_k3(); }
	double get_p1() { return dist_coeff.get_p1(); }
	double get_p2() { return dist_coeff.get_p2(); }

	double get_tilt() { return tilt; }
	double get_pan() { return pan; }

	double get_res_w() { return res_w; }
	double get_res_h() { return res_h; }

	double get_x() { return coordinate.get_x(); }
	double get_y() { return coordinate.get_y(); }
	double get_z() { return coordinate.get_z(); }

	Coord2 get_top_left_corner() { return top_left_corner; }
	Coord2 get_top_right_corner() { return top_right_corner; }
	Coord2 get_bottom_left_corner() {return bottom_left_corner; }
	Coord2 get_bottom_right_corner() { return bottom_right_corner; }

	Coord2 get_top_right_cover() { return top_right_cover; }
	Coord2 get_bottom_left_cover() { return bottom_left_cover; }

	Coord2 coord_on_screen(World room);	// returns screen coordinate of object
	Coord2 coord_on_screen(Coord2 obj);
	bool is_on_screen(Coord2 obj);	// true if obj is on the screen

	string to_string();
	string to_string_placement();
	string to_string_zone(int i);

	Coord2 cam_to_world(Coord2 obj_scr);

	vector<int> get_zones_covered() { return zones_covered; }

private:
	// word_to_cam(Coord3) and distortion_correction(Coord3) are called from coord_on_screen(World)
	Coord3 world_to_cam(Coord3 obj);	// convert world coordinate to camera coordinate
	Coord2 distortion_correction(Coord3 distorted);	// correct distortion

	// sin(double) and cos(double) takes angle as RADIAN
	double deg_to_rad(double angle_degree){ return angle_degree * PI / 180.0; }

	double determinantOfMinor(int row, int col, double matrix[3][3]);
	double determinant(double matrix[3][3]);
	void inverse_matrix(double in[3][3], double out[3][3]);
	void find_matrices();
	Coord3 matrix_multiplier(double matrix[3][3], Coord3 vector);
	Coord3 matrix_multiplier(double matrix[3][3], Coord2 vector);
	Coord3 scaler(Coord3 vector, double scale_to);

	void find_corners();
	void find_coverage();

	int zone_calculator(int x_coord, int y_coord);
	void find_zones_covered();
};

#endif