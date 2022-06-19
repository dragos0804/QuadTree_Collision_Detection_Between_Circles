#include "application.h"

bool application::OnUserCreate()
{
	QTree = new quadtree(quadtree::Rectangle(0, 0, ScreenWidth(), ScreenHeight()));
	resetApp();
	return true;
}

bool application::OnUserUpdate(float time)
{
	Clear(olc::BLACK);
	collidingCircles.clear();
	QTree->clear();
	for (auto currentObject : objects)
	{
		QTree->insertQ(currentObject, collidingCircles);
		currentObject->updateObject(time);
		WrapCoordinates(currentObject->coordx, currentObject->coordy, currentObject->coordx, currentObject->coordy);
		DrawCircle(currentObject->coordx, currentObject->coordy, currentObject->radius, olc::CYAN);
	}
	DrawString(0, 40, "Objects colliding: " + std::to_string(collidingCircles.size()));
	for (auto currentObject : collidingCircles)
		DrawLine(currentObject.first->coordx, currentObject.first->coordy, currentObject.second->coordx, currentObject.second->coordy, olc::YELLOW);
	QTree->graphical_output(this);

	return true;
}

void application::WrapCoordinates(double inputX, double inputY, double& outputX, double& outputY)
{
	outputX = inputX;
	outputY = inputY;

	if (inputX < 0)
		outputX = inputX + (double)ScreenWidth();
	if (inputX >= (double)ScreenWidth())
		outputX = inputX - (double)ScreenWidth();
	if (inputY < 0)
		outputY = inputY + (double)ScreenHeight();
	if (inputY >= (double)ScreenHeight())
		outputY = inputY - (float)ScreenHeight();
}

void application::resetApp()
{
	objects.clear();
	QTree->clear();
	srand(time(NULL));
	for (int index = 0; index < 100; index++)
	{
		object* obj = new object(this);
		objects.push_back(obj);
		QTree->insertQ(obj, collidingCircles);
	}
}
