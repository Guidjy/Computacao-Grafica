#include "Slider.h"
#include "gl_canvas2d.h"


Slider::Slider(Vector2 _pos, float _height, float _width, std::array<float, 3> _color, bool _isFilled)
	:Rect(_pos, _height, _width, _color, _isFilled)
{
	Vector2 holderPos;
	holderPos.x = pos.x + width / 2;
	holderPos.y = pos.y + height / 2;

	float holderRadius = height / 2 * 1.5;
	std::array<float, 3> holderColor = { color[0] * 0.7f, color[1] * 0.7f, color[2] * 0.7f };

	holder = new Circle(holderPos, holderRadius, 20, holderColor, true);

	isClicked = false;
}

void Slider::render(int mouseX, int mouseY)
{
	Rect::render(mouseX, mouseY);
	holder->render(mouseX, mouseY);

	if (isClicked)
	{
		onDrag(mouseX);
	}
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

	holder->setPos(Vector2(newX, holder->getPos().y));
}