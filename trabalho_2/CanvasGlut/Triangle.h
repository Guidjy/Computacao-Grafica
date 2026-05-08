#pragma once
#include "Shape.h"
#include <array>

class Triangle : public Shape
{
private:
	float width;

	float height;

	std::array<Vector2, 3> vertices;

public:
	Triangle(float _width, float _height, Vector2 _pos, std::array<float, 3> _color, bool _isFilled);

	void render(int mouseX, int mouseY) override;
};

