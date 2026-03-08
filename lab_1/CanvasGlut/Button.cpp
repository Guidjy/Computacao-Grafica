#include "Button.h"


Button::Button(float _x, float _y, float _height, float _width, std::string _text, std::array<float, 3> _color)
{
	pos = Vector2(_x, _y);
	height = _height;
	width = _width;
	text = _text;
	color = _color;
	isHovering = false;
}

void Button::render()
{
	CV::color(color[0], color[1], color[2]);
	CV::rectFill(pos, Vector2(pos.x + width, pos.y + height));
	CV::color(0, 0, 0);
	CV::text(pos.x + width * 0.2, pos.y + height / 2, text.c_str());
}

bool Button::checkHover(int mouseX, int mouseY)
{
	if (mouseX >= pos.x && mouseX <= pos.x + width && mouseY >= pos.y && mouseY <= pos.y + height)
	{
		onHover();
	}
	else
	{
		onHoverExit();
	}

	return isHovering;
}

void Button::onHover()
{
	if (!isHovering)
	{
		color = { color[0] * 0.8f, color[1] * 0.8f, color[2] * 0.8f };
		isHovering = true;
	}
}

void Button::onHoverExit()
{
	if (isHovering)
	{
		color = { color[0] / 0.8f, color[1] / 0.8f, color[2] / 0.8f };
		isHovering = false;
	}
}