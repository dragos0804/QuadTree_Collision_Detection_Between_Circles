#pragma once
class circle
{
public:
	double coordx, coordy;
	double velocityX, velocityY;
	double accelerationX, accelerationY;
	double angle;
	int radius;
	circle(double x = 0, double y = 0, double vX = 0, double vY = 0, int r = 1, double a = 0)
	{
		this->coordx = x;
		this->coordy = y;
		this->velocityX = vX;
		this->velocityY = vY;
		this->radius = r;
		this->angle = a;
	}
};