#pragma once
#include <Class.h>
#include <algorithm>
#include <vertexbuffer.h>

//#define CALL_MEMBER_FN(ptrToMember,object)  ((object).*(ptrToMember))




///Class implementations

///array class

array_2d::array_2d(int Width, int Height)
	: width(Width), height(Height), array(new float* [Width]) 
{
	for (int i = 0; i < Width; i++) { array[i] = new float[Height]; }
}


array_2d::~array_2d() 
{
	for (int i = 0; i < width; i++) { delete[] array[i]; } 
	delete[] array;
}

int array_2d::get_width() { return width; }
int array_2d::get_heigth() { return height; }


///line class 
void Line::end_of_line()
{
	pos[2] = pos[0] + cosf(angle) * length;
	pos[3] = pos[1] + sinf(angle) * length;
}
Line::Line(float X, float Y, float A, float L)
	: pos{ X,Y , X + cosf(A) * L, Y+ sinf(A) * L },
	angle(A), length(L) {; }





///circle class

void Circle::points()
{
	float a = 0.0f;
	const float a_final = 2.0f * pi;
	const float increment = a_final / n_of_points;


	for (int i = 0; i < n_of_points * 2; i += 2)
	{
		point_array[i] = x + cosf(a) * radius;
		point_array[i + 1] = y + sinf(a) * radius;
		a += increment;
	}

}
Circle::Circle(int N_of_points, float X, float Y, float R)
: x ( X), y ( Y),//position
radius ( R),
n_of_points ( N_of_points),//precision
point_array ( new float[n_of_points * 2]) //array of points to draw
{points();}


Circle::~Circle(){delete[] point_array;}



DEP::DEP(float X, float Y, float l1, float a1, float r_l1, float K1, float M1,
	float l2, float a2, float r_l2, float K2, float M2)
	:
	pos{X,Y},

	length1(l1),angle1(a1),r_length1(r_l1),m1(M1),k1(K1),angle2(a2),length2(l2),r_length2(r_l2),k2(K2),m2(M2),

	line1(Line(pos[0],pos[1],a1,l1)),
	circle1(Circle(20,pos[0]+cosf(a1)*l1,pos[1]+sinf(a1)*l1,m1)),

	line2(Line(circle1.x, circle1.y,a1,l2)),
	circle2(Circle(20,circle1.x+cosf(a2)*l2,circle1.y+sinf(a2)*l2,m2)),

	da1(0.0),
	da2(0.0),

	dl1(0.0),
	dl2(0.0)

{}

/// this is my attempt at passing in expressions in a function
/// i ended up making different functions for each expressions and making a function point as their substitue

float DEP::dda1(float A1, float DA1) { return -(1 / length1) * (2 * DA1 * dl1 + g * cosf(A1) + (k2 / m1) * (length2 - r_length2) * sinf(A1 - angle2)); }
float DEP::dda2(float A2, float DA2) { return -(1 / length2) * (2 * dl2 * DA2 - (k1 / m1) * (length1 - r_length1) * sinf(angle1 - A2)); }
float DEP::ddl1(float L1, float DL1) { return  da1 * da1 * L1 - g * sinf(angle1) - (k1 / m1) * (L1 - r_length1) + (k2 / m1) * (length2 - r_length2) * cosf(angle1 - angle2); }//doesnt depend on first derivative useless parameter necessary to generalize
float DEP::ddl2(float l2, float DL2) { return   da2 * da2 * length2 - (k2 / m2) * (length2 - r_length2) - (k2 / m1) * (length2 - r_length2) + (k1 / m1) * (length1 - r_length1) * cosf(angle1 - angle2); }//doesnt depend on first derivative useless parameter necessary to generalize



float* DEP::calc_steps_RK4(int state)
{
	typedef float (DEP::* compute)(float, float);
	compute ddx;
	float x;
	float dx;


	if (state == 0) {
		x = this->angle1;
		dx = this->da1;
		ddx = &DEP::dda1;
	}
	else if (state == 1) {
		x = this->length1;
		dx = this->dl1;
		ddx = &DEP::ddl1;
	}
	else if (state == 2) {
		x = this->angle2;
		dx = this->da2;
		ddx = &DEP::dda2;
	}
	else {
		x = this->length2;
		dx = this->dl2;
		ddx = &DEP::ddl2;
	}

	float Kx[4];
	float Kdx[4];

	Kx[0] = (this->*ddx)(x, dx);//CALL_MEMBER_FN(ddx,*this)) expands to ((object).*(ptrToMember))
	Kx[1] = (this->*ddx)(x + dt * Kx[0] / 2,dx);
	Kx[2] = (this->*ddx)(x + dt * Kx[1] / 2,dx);
	Kx[3] = (this->*ddx)(x + dx + dt * Kx[2],dx);

	Kdx[0] = (this->*ddx)(x,dx);
	Kdx[1] = (this->*ddx)(x,dx + dt * Kdx[0] / 2);
	Kdx[2] = (this->*ddx)(x,dx + dt * Kdx[1] / 2);
	Kdx[3] = (this->*ddx)(x,dx + dt * Kdx[2]);

	float step_x = x + dt / 6 * (Kx[0] + 2 * Kx[1] + 2 * Kx[2] + Kx[3]);
	float step_dx = dx + dt / 6 * (Kdx[0] + 2 * Kdx[1] + 2 * Kdx[2] + Kdx[3]);
	float steps[2] = { step_x,step_dx };

	return (steps);

}

void DEP::update() {

	float arr_steps[4 * 2];
	for (int i = 0; i < 4 * 2; i += 2) {
		arr_steps[i] = calc_steps_RK4(i / 2)[0];
		arr_steps[i + 1] = calc_steps_RK4(i / 2)[1];
	}

	angle1 = arr_steps[0];
	da1 = arr_steps[1];
	length1 = arr_steps[2];
	dl1 = arr_steps[3];
	angle2 = arr_steps[4];
	da2 = arr_steps[5];
	length2 = arr_steps[6];
	dl2 = arr_steps[7];



	line1.angle = angle1;
	line1.length = length1;
	circle1.x = line1.pos[2];
	circle1.y = line1.pos[3];

	line1.end_of_line();
	circle1.points();


	line2.angle = angle2;
	line2.length = length2;
	circle2.x = line2.pos[2];
	circle2.y = line2.pos[3];

	line2.pos[0] = circle1.x; line2.pos[1] = circle1.y;
	line2.end_of_line();
	circle2.points();

};




