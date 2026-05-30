#pragma once

#include "Shape.h"
#include "Vector2.h"
#include <array>


class Rect : public Shape
{
protected:
	float height;
	float width;
	std::array<Vector2, 4> vertices;

private:
	void updateVertices();

public:
	Rect(Vector2 _pos, float _height, float _width, std::array<float, 3> _color = { 0, 0, 0 }, bool _isFilled = false);

	float getHeight() { return height; }
	void setHeight(float _height) { height = _height; updateVertices(); }

	float getWidth() { return width; }
	void setWidth(float _width) { width = _width; updateVertices(); }

	bool getIsFilled() { return isFilled; }
	void setIsFilled(bool _isFilled) { isFilled = _isFilled; }

	void render() override;
};

