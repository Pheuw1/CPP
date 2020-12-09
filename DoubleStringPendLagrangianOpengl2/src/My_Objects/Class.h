#pragma once

#ifndef CLASS_H
#define CLASS_H

constexpr float pi = 3.1415926f;
constexpr float g = 1.0f;
constexpr float dt = 0.01f;
// maybe use template next time
class array_2d
{
	int width;
	int height;

public:

	float** array;

	array_2d(int Width, int Height);

	~array_2d();

	int get_width();
	int get_heigth();
};

class Line
{
public:

	float angle;
	float length;
	float pos[4];//fisrt two are xy beggining and last two are xy end

	Line(float X, float Y, float A, float L);

	void end_of_line();

};

class Circle
{

	float radius;
	

public:
	int n_of_points;
	float* point_array;
	float x;
	float y;

	Circle(int N_of_points, float X, float Y, float R);
	Circle();

	~Circle();

	void points();

	void draw();
};

class DEP//Double_Elastic_Pendulum
{
	float pos[2];
	///constants 1
	float m1;
	float k1;
	float r_length1;
	///constants 2
	float m2;
	float k2;
	float r_length2;

public:

	DEP(float X, float Y, float l1, float a1, float r_l1, float K1, float M1, float a2, float l2, float r_l2, float K2, float M2);

	//Draw 1
	Line line1;
	Circle circle1;
	//Draw 2
	Line line2;
	Circle circle2;

	//Coordinate 1
	float angle1;
	float length1;
	//Coordinate 2
	float angle2;
	float length2;

	/// speed a1
	float da1;
	/// speed l1
	float dl1;
	/// speed a2
	float da2;
	/// speed l2
	float dl2;

	float dda1(float A1, float DA1);
	float dda2(float A2, float DA2);
	float ddl1(float L1, float DL1);
	float ddl2(float l2, float DL2);

	float* calc_steps_RK4(int state);

	void update();
};
#endif

/*apply runge kutta method then worry about code
void update()
{
	dda1 = -(1 / length1) * (2 * da1 * dl1 + g * cosf(angle1) + (k2 / m1) * (length2 - r_length2) * sinf(angle1 - angle2));

	dda2 = -(1 / length2) * (2 * dl2 * da2 - (k1 / m1) * (length1 - r_length1) * sinf(angle1 - angle2));

	ddl1 = da1 * da1 * length1 - g * sinf(angle1) - (k1 / m1) * (length1 - r_length1) + (k2 / m1) * (length2 - r_length2) * cosf(angle1 - angle2);

	ddl2 = da2 * da2 * length2 - (k2 / m2) * (length2 - r_length2) - (k2 / m1) * (length2 - r_length2) + (k1 / m1) * (length1 - r_length1) * cosf(angle1 - angle2);

	dl1 += ddl1 * dt;
	length1 += dl1 * dt * damp;

	da1 += dda1 * dt;
	angle1 += da1 * dt * damp;

	dl2 += ddl2 * dt;
	length2 += dl2 * dt * damp;

	da2 += dda2 * dt;
	angle2 += da2 * dt * damp;

	void draw() {
	int a = 0;
*/
