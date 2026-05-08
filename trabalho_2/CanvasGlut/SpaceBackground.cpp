#include "SpaceBackground.h"
#include "Vector2.h"
#include <stdlib.h>

#define STAR_COUNT 200


SpaceBackground::SpaceBackground(float _height, float _width)
	: Rect(Vector2(0, 0), _height, _width, { 0, 0, 0 }, true)
{ 
	stars = std::list<Circle*>();

	for (int i = 0; i < STAR_COUNT; i++)
	{
		Vector2 pos = Vector2(rand() % (int)width, rand() % (int)height);
		Circle* star = new Circle(pos, (rand() % 5) + 1, 5, { 1, 1, 1 }, true);
		stars.push_back(star);
	}
}

void SpaceBackground::render(int mouseX, int mouseY)
{
	Rect::render(mouseX, mouseY);

	for (Circle* star : stars)
	{
		Vector2 newPos = star->getPos();
		newPos.y += 1;
		if (newPos.y > height)
		{
			newPos.y = 0;
		}
		star->setPos(newPos);

		star->render(mouseX, mouseY);
	}
}