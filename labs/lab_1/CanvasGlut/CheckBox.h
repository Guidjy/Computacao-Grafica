#pragma once
#include "Button.h"


class CheckBox : public Button
{
public:
	bool checked;

	CheckBox(float _x, float _y, float _height, float _width, std::string _text, std::array<float, 3> _color = { 1, 1, 1 });

	void render();
};

