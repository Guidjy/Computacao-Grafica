#pragma once
#include "Rect.h"
#include "Circle.h"
#include <list>

class SpaceBackground : public Rect
{
private:
	std::list<Circle*> stars;

public:
	SpaceBackground(float _height, float _width);

	void render(int mouseX, int mouseY) override;
};

