#pragma once

#include "Vector2.h"
#include <array>


class Shape
{
protected:
	// - Rectangle: Upper right vertix
	// - Circle: Center
	Vector2 pos;
	std::array<float, 3> color;
	bool isFilled;

public:
	Shape(Vector2 _pos, std::array<float, 3> _color = { 0, 0, 0 }, bool _isFilled = false);

	Vector2 getPos() { return pos; }
	void setPos(Vector2 _pos) { pos = _pos; }

	std::array<float, 3> getColor() { return color; }
	void setColor(std::array<float, 3> _color) { color = _color; }

	bool getIsFilled() { return isFilled; }
	void setIsFilled(bool _isFilled) { isFilled = _isFilled; }

	virtual void render();
};