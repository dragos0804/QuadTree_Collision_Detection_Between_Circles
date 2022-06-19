#include "quadtree.h"

quadtree::quadtree(Rectangle rectangle)
{
	this->isSplit = false;
	this->boundaries = rectangle;
	this->MAX_OBJECTS = 10;
}

void quadtree::insertQ(circle* currentCircle, std::vector<std::pair<circle*, circle*>>& collidingCircles)
{
								//if the object does not fit in the current sub-quadtree, return
	if (boundaries.checkCircleBounds(currentCircle->coordx, currentCircle->coordy, currentCircle->radius) == false)
		return;
								//add in the quadtree only if the maximum amount of objects hasn't been reached
	if (isSplit == false && circles.size() < MAX_OBJECTS)
	{
		circles.push_back(currentCircle);
		for (auto anyCircle : circles)
		{						//checks whether the are identical or overlapping 
			if (currentCircle != anyCircle &&
				((currentCircle->coordx - anyCircle->coordx) * 
				(currentCircle->coordx - anyCircle->coordx)) + 
				((currentCircle->coordy - anyCircle->coordy) * 
				(currentCircle->coordy - anyCircle->coordy)) <= 
				(currentCircle->radius + anyCircle->radius) * 
				(currentCircle->radius + anyCircle->radius))
								//adds the colliding pair to the vector
				collidingCircles.push_back({ currentCircle, anyCircle });	
		}
	}
	else 
	{
		if (isSplit == false)
			split(collidingCircles);
		for (auto node : nodes)
			node->insertQ(currentCircle, collidingCircles);
	}
}

void quadtree::split(std::vector<std::pair<circle*, circle*>>& collidingCircles)
{
								//coordinates of the current corner
	double x = boundaries.coordX;
	double y = boundaries.coordY;
								//height and width of the split zone 
	double subWidth = boundaries.width / 2;
	double subHeight = boundaries.height / 2;
								// Bottom Left
	nodes.push_back(std::shared_ptr<quadtree>(new quadtree(Rectangle(x, y + subHeight, subWidth, subHeight))));
								// Bottom Right
	nodes.push_back(std::shared_ptr<quadtree>(new quadtree(Rectangle(x + subWidth, y + subHeight, subWidth, subHeight))));
								// Top Right
	nodes.push_back(std::shared_ptr<quadtree>(new quadtree(Rectangle(x + subWidth, y, subWidth, subHeight))));
								// Top Left
	nodes.push_back(std::shared_ptr<quadtree>(new quadtree(Rectangle(x, y, subWidth, subHeight))));


	for (auto currentObject : this->circles)
		for (int index = 0; index < nodes.size(); index++)
			nodes[index]->insertQ(currentObject, collidingCircles);
	this->circles.clear();
	this->isSplit = true;
}

void quadtree::deleteQ(circle* currentCircle)
{
								//if the object does not fit in the current sub-quadtree, return
	if (boundaries.checkCircleBounds(currentCircle->coordx, currentCircle->coordy, currentCircle->radius) == false)
		return;
								//if the sub-quadtree isn't split, we can iterate through it and delete the element
	if (isSplit == false)
	{
		for (int index = 0; index < circles.size(); index++)
		{
			if (circles[index] == currentCircle)
			{
				this->circles.erase(circles.begin() + index);
				return;
			}
		}
	}
								//if not, check another branch
	else			
	{
		for (auto node : nodes)
			node->deleteQ(currentCircle);
	}
}

void quadtree::clear()
{								//deleting all nodes from a sub-quadtree, then moving on to the next one
	if (isSplit == true)
	{
		for (auto node : nodes)
			node->clear();
		isSplit = false;
	}
	nodes.clear();
	circles.clear();
}

void quadtree::graphical_output(olc::PixelGameEngine* instance)
{
	if (isSplit == false)
		instance->DrawString(boundaries.coordX + 2, boundaries.coordY + 2, std::to_string(this->circles.size()), olc::MAGENTA);
	else
	{
		for (auto node : nodes)
			node->graphical_output(instance);
	}
	instance->DrawRect(boundaries.coordX, boundaries.coordY, boundaries.width, boundaries.height);
}
