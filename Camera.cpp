#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	this->int_param = Camera_int_param();
	this->dist_coeff = Camera_dist_coeff();
	this->coordinate = Coord3();
	this->pan = 0;
	this->tilt = 0;
	this->res_w = 0;
	this->res_h = 0;
	this->find_matrices();
}

Camera::Camera(Camera_int_param int_param, Camera_dist_coeff dist_coeff, Coord3 coordinate,
	double pan, double tilt, double res_w, double res_h)
{
	this->int_param = int_param;
	this->dist_coeff = dist_coeff;
	this->coordinate = coordinate;
	this->pan = pan;
	this->tilt = tilt;
	this->res_w = res_w;
	this->res_h = res_h;
	this->find_matrices();
	this->find_corners();
	this->find_coverage();
	this->find_zones_covered();
}

Camera::Camera(double cx, double cy, double fx, double fy, double k1, double k2, double k3,
	double p1, double p2, double x, double y, double z, double pan, double tilt,
	double res_w, double res_h)
{
	this->int_param = Camera_int_param(cx, cy, fx, fy);
	this->dist_coeff = Camera_dist_coeff(k1, k2, p1, p2, k3);
	this->coordinate = Coord3(x, y, z);
	this->pan = pan;
	this->tilt = tilt;
	this->res_w = res_w;
	this->res_h = res_h;
	this->find_matrices();
	this->find_corners();
	this->find_coverage();
	this->find_zones_covered();
}

void Camera::moveTo(double x, double y, double z)
{
	this->coordinate.reset_position(x, y, z);
	this->find_corners();
	this->find_coverage();
	this->find_zones_covered();
}

void Camera::moveTo(double pan, double tilt)
{
	this->pan = pan;
	this->tilt = tilt;
	this->find_matrices();
	this->find_corners();
	this->find_coverage();
	this->find_zones_covered();
}

void Camera::moveTo(double x, double y, double z, double pan, double tilt)
{
	this->coordinate.reset_position(x, y, z);
	this->pan = pan;
	this->tilt = tilt;
	this->find_matrices();
	this->find_corners();
	this->find_coverage();
	this->find_zones_covered();
}

// returns coordinate of object on screen in pixels
Coord2 Camera::coord_on_screen(World room)
{
	Coord2 temp = distortion_correction(world_to_cam(room.get_obj()));

	return Coord2(this->get_fx() * temp.get_x() + this->get_cx()
		, this->get_fy() * temp.get_y() + this->get_cy());
}

Coord2 Camera::coord_on_screen(Coord2 obj)
{
	Coord2 temp = distortion_correction(world_to_cam(Coord3(obj.get_x(), obj.get_y(), 0)));
	
	return Coord2(this->get_fx() * temp.get_x() + this->get_cx()
		, this->get_fy() * temp.get_y() + this->get_cy());
}

bool Camera::is_on_screen(Coord2 obj)
{
	Coord2 temp = coord_on_screen(obj);
	return (temp.get_x() > 0 && temp.get_y() > 0 && temp.get_x() < res_w	&& temp.get_y() < res_h);
}

// returns camera coordinate of obj
Coord3 Camera::world_to_cam(Coord3 obj_world)
{
	Coord3 temp = Coord3(obj_world.get_x() - this->get_x(), obj_world.get_y() - this->get_y(), obj_world.get_z() - this->get_z());
	
	return matrix_multiplier(rotation_matrix, temp);
}

// corrects tangential and radial distortion
Coord2 Camera::distortion_correction(Coord3 distorted)
{
	Coord2 temp = Coord2((distorted.get_x() / distorted.get_z()), (distorted.get_y() / distorted.get_z()));

	double r = sqrt(pow(temp.get_x(), 2) + pow(temp.get_y(), 2));

	return Coord2(temp.get_x() * (1 + this->get_k1() * pow(r, 2) + this->get_k2() * pow(r, 4) + this->get_k3() * pow(r, 6))
		+ (2 * this->get_p1() * temp.get_x() * temp.get_y() + this->get_p2() * (pow(r, 2) + 2 * pow(temp.get_x(), 2)))
		, temp.get_y() * (1 + this->get_k1() * pow(r, 2) + this->get_k2() * pow(r, 4) + this->get_k3() * pow(r, 6))
		+ (2 * this->get_p2() * temp.get_x() * temp.get_y() + this->get_p1() * (pow(r, 2) + 2 * pow(temp.get_y(), 2))));
}

string Camera::to_string()
{
	return "INT_PARAM\t" + int_param.to_string() + "\nDIST_COEFF\t" + dist_coeff.to_string()
		+ "\nCOORDINATE\t" + coordinate.to_string() + "\nPAN: " + std::to_string(pan)
		+ "\tTILT: " + std::to_string(tilt) + "\nRES_W: " + std::to_string(res_w)
		+ "\tRES_H: " + std::to_string(res_h);
}

string Camera::to_string_placement()
{
	return "(" + std::to_string((int)this->get_x()) + ", " + std::to_string((int)this->get_y()) 
		+ ", " + std::to_string((int)this->get_z()) + ")" + " pan: " + std::to_string((int)pan) + " tilt: " + std::to_string((int)tilt);
}

string Camera::to_string_zone(int i)
{
	string temp;
	int k;
	if (i == 0)
	{
		if (zones_covered.size() < 29)
			k = zones_covered.size();
		else
			k = 29;

		for (int j = 0; j < k; j++)
			temp += (std::to_string(zones_covered[j]) + " ");
	}

	else
	{
		if (zones_covered.size() < 29)
			return "";
		else
		{
			for (int j = 29; j < zones_covered.size(); j++)
				temp += (std::to_string(zones_covered[j]) + " ");
		}
	}
	

	

	return "coverage: " + temp;
}

void Camera::find_matrices()
{
	double sin_pan = sin(this->deg_to_rad(this->get_pan()));
	double sin_tilt = sin(this->deg_to_rad(this->get_tilt()));
	double cos_pan = cos(this->deg_to_rad(this->get_pan()));
	double cos_tilt = cos(this->deg_to_rad(this->get_tilt()));

	this->intrinsic_matrix[0][0] = this->get_fx();
	this->intrinsic_matrix[0][1] = 0;
	this->intrinsic_matrix[0][2] = this->get_cx();
	this->intrinsic_matrix[1][0] = 0;
	this->intrinsic_matrix[1][1] = this->get_fy();
	this->intrinsic_matrix[1][2] = this->get_cy();
	this->intrinsic_matrix[2][0] = 0;
	this->intrinsic_matrix[2][1] = 0;
	this->intrinsic_matrix[2][2] = 1;

	this->rotation_matrix[0][0] = cos_pan;
	this->rotation_matrix[0][1] = sin_pan;
	this->rotation_matrix[0][2] = 0;
	this->rotation_matrix[1][0] = -sin_pan * sin_tilt;
	this->rotation_matrix[1][1] = cos_pan * sin_tilt;
	this->rotation_matrix[1][2] = -cos_tilt;
	this->rotation_matrix[2][0] = -sin_pan * cos_tilt;
	this->rotation_matrix[2][1] = cos_pan * cos_tilt;
	this->rotation_matrix[2][2] = sin_tilt;

	inverse_matrix(intrinsic_matrix, inverse_intrinsic_matrix);
	inverse_matrix(rotation_matrix, inverse_rotation_matrix);
}

double Camera::determinantOfMinor(int row, int col, double matrix[3][3])
{
	int x1 = col == 0 ? 1 : 0;
	int x2 = col == 2 ? 1 : 2;
	int y1 = row == 0 ? 1 : 0;
	int y2 = row == 2 ? 1 : 2;

	return (matrix[y1][x1] * matrix[y2][x2]) - (matrix[y1][x2] * matrix[y2][x1]);
}

double Camera::determinant(double matrix[3][3])
{
	return (matrix[0][0] * determinantOfMinor(0, 0, matrix)) - (matrix[0][1] * determinantOfMinor(0, 1, matrix))
		+ (matrix[0][2] * determinantOfMinor(0, 2, matrix));
}

void Camera::inverse_matrix(double in[3][3], double out[3][3])
{
	double det = determinant(in);
	double oneOverDeterminant = 1.0 / det;

	for (int y = 0; y < 3; y++)
	for (int x = 0; x < 3; x++)
	{
		out[y][x] = determinantOfMinor(x, y, in) * oneOverDeterminant;

		if (((x + y) % 2) == 1)
			out[y][x] = -out[y][x];
	}
}

Coord3 Camera::matrix_multiplier(double matrix[3][3], Coord3 vector)
{
	return Coord3(matrix[0][0] * vector.get_x() + matrix[0][1] * vector.get_y() + matrix[0][2] * vector.get_z()
		, matrix[1][0] * vector.get_x() + matrix[1][1] * vector.get_y() + matrix[1][2] * vector.get_z()
		, matrix[2][0] * vector.get_x() + matrix[2][1] * vector.get_y() + matrix[2][2] * vector.get_z());
}

Coord3 Camera::matrix_multiplier(double matrix[3][3], Coord2 vector)
{
	return Coord3(matrix[0][0] * vector.get_x() + matrix[0][1] * vector.get_y() + matrix[0][2]
		, matrix[1][0] * vector.get_x() + matrix[1][1] * vector.get_y() + matrix[1][2]
		, matrix[2][0] * vector.get_x() + matrix[2][1] * vector.get_y() + matrix[2][2]);
}

// This function is to scale coordinate ONLY in cam_to_world
Coord3 Camera::scaler(Coord3 vector, double scale_to)
{
	double scale = -scale_to / vector.get_z();

	return Coord3(vector.get_x() * scale, vector.get_y() * scale, vector.get_z() * scale);
}

Coord2 Camera::cam_to_world(Coord2 obj_scr)
{
	Coord3 temp_coord = matrix_multiplier(inverse_rotation_matrix, matrix_multiplier(inverse_intrinsic_matrix, obj_scr));
	temp_coord = scaler(temp_coord, this->get_z());

	temp_coord.reset_position(temp_coord.get_x() + this->get_x(), temp_coord.get_y() + this->get_y(), temp_coord.get_z() + this->get_z());
	return Coord2(temp_coord.get_x(), temp_coord.get_y());
}

void Camera::find_corners()
{
	top_left_corner = cam_to_world(Coord2(0, 0));
	top_right_corner = cam_to_world(Coord2(this->get_res_w(), 0));
	bottom_left_corner = cam_to_world(Coord2(0, this->get_res_h()));
	bottom_right_corner = cam_to_world(Coord2(this->get_res_w(), this->get_res_h()));
}

void Camera::find_coverage()
{
	double x_min, y_min, x_max, y_max;
	
	x_min = top_left_corner.get_x();
	x_max = top_left_corner.get_x();

	y_min = top_left_corner.get_y();
	y_max = top_left_corner.get_y();

	if (top_right_corner.get_x() < x_min)
		x_min = top_right_corner.get_x();
	if (top_right_corner.get_x() > x_max)
		x_max = top_right_corner.get_x();
	if (top_right_corner.get_y() < y_min)
		y_min = top_right_corner.get_y();
	if (top_right_corner.get_y() > y_max)
		y_max = top_right_corner.get_y();

	if (bottom_right_corner.get_x() < x_min)
		x_min = bottom_right_corner.get_x();
	if (bottom_right_corner.get_x() > x_max)
		x_max = bottom_right_corner.get_x();
	if (bottom_right_corner.get_y() < y_min)
		y_min = bottom_right_corner.get_y();
	if (bottom_right_corner.get_y() > y_max)
		y_max = bottom_right_corner.get_y();

	if (bottom_left_corner.get_x() < x_min)
		x_min = bottom_left_corner.get_x();
	if (bottom_left_corner.get_x() > x_max)
		x_max = bottom_left_corner.get_x();
	if (bottom_left_corner.get_y() < y_min)
		y_min = bottom_left_corner.get_y();
	if (bottom_left_corner.get_y() > y_max)
		y_max = bottom_left_corner.get_y();

	top_right_cover = Coord2(x_max, y_max);
	bottom_left_cover = Coord2(x_min, y_min);
}

int Camera::zone_calculator(int x_coord, int y_coord)
{
	if ((x_coord >= 0) && (y_coord >= 0) && (x_coord / 100 < 10) && (y_coord / 100 < 10))
		return (((x_coord / 100) * 10) + (y_coord / 100));
	else
		return -1;
}

void Camera::find_zones_covered()
{
	Coord2 temp;
	int zone_cur, zone_prev;
	bool found = false;
	
	zones_covered.clear();
	
	zone_prev = -1;

	for (int i = 0; i <= (int) this->get_res_h(); i += 4)
	{
		for (int j = 0; j <= (int) this->get_res_w(); j += 4)
		{	
			temp = this->cam_to_world(Coord2(j, i));
			zone_cur = zone_calculator((int)temp.get_x(), (int)temp.get_y());
			if ((zone_cur != zone_prev) && (zone_cur != -1))
			{
				found = false;
				for (int k = 0; k < zones_covered.size(); k++)
				{
					if (zones_covered[k] == zone_cur)
					{
						found = true;
						break;
					}
				}
				if (!found)
					zones_covered.push_back(zone_cur);
			}
			zone_prev = zone_cur;
		}
	}
	sort(zones_covered.begin(), zones_covered.end());
}