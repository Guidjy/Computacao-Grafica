#include "Button.h"


Button::Button(float _x, float _y, float _height, float _width, std::string _text, std::array<float, 3> _color)
{
	pos = Vector2(_x, _y);
	height = _height;
	width = _width;
	text = _text;
	color = _color;
}

void Button::render()
{
	CV::color(color[0], color[1], color[2]);
	CV::rectFill(pos, Vector2(pos.x + width, pos.y + height));
	CV::color(0, 0, 0);
	CV::text(pos.x + width * 0.2, pos.y + height / 2, text.c_str());
}

bool Button::is_hovering(int mouse_x, int mouse_y)
{
	return (mouse_x >= pos.x && mouse_x <= pos.x + width && mouse_y >= pos.y && mouse_y <= pos.y + height);
}