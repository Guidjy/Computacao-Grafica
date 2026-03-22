#pragma once

#include "Shape.h"
#include <vector>
#include <array>


class Menu
{
private:
	std::vector<Shape*> components;

	float height;

	float width;

	std::array<float, 3> backgroundColor;

public:
	Menu(float _height, float _width, std::array<float, 3> _backgroundColor = {1, 1, 1});

	std::vector<Shape*> getComponents() { return components; }
	void addComponent(Shape* component);

	float getHeight() { return height; }
	void setHeight(float _height) { height = _height; }

	float getWidth() { return width; }
	void setWidth(float _width) { width = _width; }

	void onClick(int mouseX, int mouseY, int mouseState);

	void onRelease();

	void render(int mouseX, int mouseY);
};

