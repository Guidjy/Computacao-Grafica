#include "Slider.h"
#include "Vector2.h"
#include "gl_canvas2d.h"


Slider::Slider(Vector2 _pos, float _height, float _width)
{
	pos = _pos;
	height = _height;
	width = _width;
	buttonPos = Vector2(pos.x + width / 2, pos.y + height / 2);
	buttonRadius = height * 1.2;
	isClicked = false;
}

void Slider::render(int mouseX)
{
	CV::color(0, 0, 255);
	CV::rectFill(pos, Vector2(pos.x + width, pos.y + height));
	CV::color(0, 255, 0);
	CV::circleFill(buttonPos.x, buttonPos.y, (float)buttonRadius, 10);

	if (isClicked)
	{
		onDrag(mouseX);
	}
}

bool Slider::checkHover(int mouseX, int mouseY)
{
	return (mouseX >= pos.x && mouseX <= pos.x + width && mouseY >= pos.y && mouseY <= pos.y + height);
}

void Slider::onClick()
{
	isClicked = true;
}

void Slider::onRelease()
{
	isClicked = false;
}

void Slider::onDrag(int mouseX)
{
	int newX = mouseX;
	
	if (newX > pos.x + width)
	{
		newX = pos.x + width;
	}
	if (newX < pos.x)
	{
		newX = pos.x;
	}

	buttonPos.x = newX;
}