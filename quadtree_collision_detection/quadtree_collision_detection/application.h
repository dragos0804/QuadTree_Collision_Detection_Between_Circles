#pragma once
#include "olcPixelGameEngine.h"
#include "object.h"
#include "circle.h"
#include "quadtree.h"

class application : public olc::PixelGameEngine
{
private:
	std::vector<object*> objects;
	std::vector<std::pair<circle*, circle*>> collidingCircles;
	quadtree* QTree;

public:
	application()
	{
		sAppName = "QuadTree_Application";
	}
	bool OnUserCreate() override;
	bool OnUserUpdate(float time) override;
	void WrapCoordinates(double inputX, double inputY, double& outputX, double& outputY);
	void resetApp();
};