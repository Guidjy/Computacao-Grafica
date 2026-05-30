#include "CheckBox.h"

CheckBox::CheckBox(float _x, float _y, float _height, float _width, std::string _text, std::array<float, 3> _color)
	: Button(_x, _y, _height, _width, _text, _color)
{
	checked = false;
}

void CheckBox::render()
{
	if (checked)
	{
		Button::setText("✓");
	}
	else
	{
		Button::setText("");
	}

	Button::render();
}