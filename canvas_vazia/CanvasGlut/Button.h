#pragma once

#include "gl_canvas2d.h"
#include "Vector2.h"
#include <string>
#include <array>


class Button
{
	float height;
	float width;
	Vector2 pos;
	std::string text;
	std::array<float, 3> color;

public:
	Button(float _x, float _y, float _height, float _width, std::string _text, std::array<float, 3> _color = { 1, 1, 1 });

	void render();

	bool is_hovering(int mouse_x, int mouse_y);
};

