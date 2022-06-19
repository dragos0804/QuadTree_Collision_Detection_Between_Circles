#pragma once
#include "olcPixelGameEngine.h"
#include "quadtree.h"
#include "circle.h"
#include <vector>

class object : public circle
{
private:
	std::vector <std::pair<double, double>> vectorOfVertices;
	void createObject(int noOfVertices);
	double spin;
public:
	object();
	object(double x, double y, double vX, double vY, int r, double a);
	object(olc::PixelGameEngine* instance);
	void updateObject(float time);
};