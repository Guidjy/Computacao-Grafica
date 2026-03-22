#include "Button.h"
#include "gl_canvas2d.h"
#include "mouseStates.h"
#include <iostream>


Button::Button(Vector2 _pos, float _height, float _width, std::string _text, std::array<float, 3> _color, bool _isFilled, std::function<void()> _onClick)
	: Rect(_pos, _height, _width, _color, _isFilled)
{
	text = _text;
	isHovering = false;
	onClickCallback = _onClick;
}

void Button::onHover()
{
	if (!isHovering)
	{
		isHovering = true;
		color = { color[0] * 0.8f, color[1] * 0.8f, color[2] * 0.8f };
	}
}

void Button::onHoverExit()
{
	if (isHovering)
	{
		isHovering = false;
		color = { color[0] / 0.8f, color[1] / 0.8f, color[2] / 0.8f };
	}
}

void Button::onClick()
{
	if (onClickCallback)
	{
		onClickCallback();
	}
}

void Button::render(int mouseX, int mouseY)
{
	Rect::render(mouseX, mouseY);

	CV::color(1 / color[0], 1 / color[1], 1 / color[2]);
	CV::text(pos.x + width / 6, pos.y + height / 2, text.c_str());

	if (checkHover(mouseX, mouseY))
	{
		onHover();
	}
	else
	{
		onHoverExit();
	}
}