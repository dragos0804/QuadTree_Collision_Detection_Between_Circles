#include "object.h"

object::object(double x, double y, double vX, double vY, int r, double a)
{
	this->coordx = x;
	this->coordy = y;
	this->velocityX = vX;
	this->velocityY = vY;
	this->radius = r;
	this->angle = rand() % 5;
	createObject(20);
}

object::object(olc::PixelGameEngine* instance)
{

	coordx = rand() % instance->ScreenWidth();
	coordy = rand() % instance->ScreenHeight();

	velocityX = 1 + rand() % 15;
	velocityY = 1 + rand() % 15;
	
	radius = rand() % 15 + 5;
	spin = rand() % 5;
	createObject(20);
}

void object::createObject(int noOfVertices)
{
	for (int index = 0; index < noOfVertices; index++)
	{
		double a = ((double)index / (double)noOfVertices) * 6.28318;
		vectorOfVertices.push_back({radius * sin(a), radius * cos(a)});
	}
}

void object::updateObject(float time)
{
	this->velocityX += this->accelerationX * time;
	this->velocityY += this->accelerationY * time;

	this->coordx += this->velocityX * time;
	this->coordy += this->velocityY * time;
	
	this->angle += this->spin * time;

	this->accelerationX = 0;
	this->accelerationY = 0;
}
