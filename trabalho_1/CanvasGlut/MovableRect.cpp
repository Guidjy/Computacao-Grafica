#include "MovableRect.h"


MovableRect::MovableRect(Vector2 _pos, float _height, float _width, std::array<float, 3> _color, bool _isFilled, Canvas* _parentCanvas)
	:Rect(_pos, _height, _width, _color, _isFilled)
{
	isClicked = false;
	parentCanvas = _parentCanvas;
}

void MovableRect::onClick(int mouseX, int mouseY)
{
	isClicked = true;
}

void MovableRect::onRelease()
{
	isClicked = false;
}

void MovableRect::onDrag(int mouseX, int mouseY)
{
	Vector2 newPos = Vector2(mouseX, mouseY);

	// checks if new rect position is within the parent canvas
	if (parentCanvas)
	{
		float lowerBoundX = parentCanvas->getPos().x;
		float upperBoundX = parentCanvas->getPos().x + parentCanvas->getWidth();
		float lowerBoundY = parentCanvas->getPos().y;
		float upperBoundY = parentCanvas->getPos().y + parentCanvas->getHeight();

		if (newPos.x < lowerBoundX)
		{
			newPos.x = lowerBoundX;
		}
		if (newPos.x + width > upperBoundX)
		{
			newPos.x = upperBoundX - width;
		}
		if (newPos.y < lowerBoundY)
		{
			newPos.y = lowerBoundY;
		}
		if (newPos.y + height > upperBoundY)
		{
			newPos.y = upperBoundY - height;
		}
	}

	setPos(newPos);
}

void MovableRect::render(int mouseX, int mouseY)
{
	Rect::render(mouseX, mouseY);

	if (isClicked)
	{
		onDrag(mouseX, mouseY);
	}
}