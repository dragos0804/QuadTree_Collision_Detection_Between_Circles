#pragma once
#define euclidianDistance(x, y) (((x)*(x)) + ((y)*(y)))
#define clamp(x, y, z) std::max((y), std::min((z), (x)))
#include <vector>
#include "circle.h"
#include "olcPixelGameEngine.h"

class quadtree {
private:
	int MAX_OBJECTS;			//maximum amount of objects a quadtree can hold TODO add max amount of times the quadtree can split
	bool isSplit;				//true only if this quadtree has already been split
	std::vector<std::shared_ptr<quadtree>> nodes; // leaf subnodes
	std::vector<circle*> circles;
	struct Rectangle
	{
		double coordX, coordY;  //coordinates of the corner of the current rectangle
		double width, height;   //sizez of the sides
								//rectangle constuctor with parameters
		Rectangle(double coordX = 0, double coordY = 0, double width = 1, double height = 1) 
		{
			this->coordX = coordX;
			this->coordY = coordY;
			this->width = width;
			this->height = height;
		}
								//checks if the circle is inside the bounds of the current rectangle
		bool checkCircleBounds(double cx, double cy, double radius)
		{
								//calculate the AABB information (center, half-extents)
			double halfXAxis = this->width / 2;
			double halfYAxis = this->height / 2;

			double centerX = this->coordX + halfXAxis;
			double centerY = this->coordY + halfYAxis;
								//get difference between centers
			double differenceX = cx - centerX;
			double differenceY = cy - centerY;
								//clamps a value between a given range by limiting a position to an area 
			double clampedX = clamp(differenceX, -halfXAxis, halfXAxis);
			double clampedY = clamp(differenceY, -halfYAxis, halfYAxis);
								
			double closestX = centerX + clampedX;
			double closestY = centerY + clampedY;

			differenceX = closestX - cx;
			differenceY = closestY - cy;

			return euclidianDistance(differenceX, differenceY) <= radius * radius;
		}
	};
	Rectangle boundaries;
	
public:
	quadtree(Rectangle rectangle);
								//splits the quadtree into 4 sub-quadtrees
	void split(std::vector<std::pair<circle*, circle*>>& collidingCircles);
								//insertion into the quadtree
	void insertQ(circle* currentCircle, std::vector<std::pair<circle*, circle*>>& collidingCircles);

	void deleteQ(circle* currentCircle);

	void clear();

	void graphical_output(olc::PixelGameEngine* instance);

	friend class application;
};