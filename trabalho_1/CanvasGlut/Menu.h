#pragma once

#include "Shape.h"
#include <vector>


class Menu
{
private:
	std::vector<Shape*> components;

public:
	Menu();

	std::vector<Shape*> getComponents() { return components; }
	void addComponent(Shape* component);

	void onClick(int mouseX, int mouseY, int mouseState);

	void onRelease();

	void render(int mouseX, int mouseY);
};

