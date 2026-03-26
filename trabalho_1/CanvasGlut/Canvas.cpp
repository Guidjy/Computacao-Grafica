#include "Canvas.h"
#include "MovableRect.h"


Canvas::Canvas(Vector2 _pos, float _height, float _width, std::array<float, 3> _color, bool _isFilled)
	: Rect(_pos, _height, _width, _color, _isFilled)
{
	canDrawRect = false;
	isDrawingRect = false;
	canMoveRect = false;
	currentMousePos = Vector2(0, 0);
	mouseClickPos = Vector2(0, 0);
	mouseReleasePos = Vector2(0, 0);
	rects = std::vector<MovableRect*>();
}


void Canvas::setCurrentMousePos(Vector2 _currentMousePos)
{
	currentMousePos = _currentMousePos;

	// keeps the current mouse position within the canvas
	if (currentMousePos.x < pos.x)
	{
		currentMousePos.x = pos.x;
	}
	if (currentMousePos.x > pos.x + width)
	{
		currentMousePos.x = pos.x + width;
	}
	if (currentMousePos.y < pos.y)
	{
		currentMousePos.y = pos.y + 1;
	}
	if (currentMousePos.y > pos.y + height)
	{
		currentMousePos.y = pos.y + height + 1;
	}
}

void Canvas::onClick(int mouseX, int mouseY)
{
	if (!checkHover(mouseX, mouseY))
	{
		return;
	}

	setMouseClickPos(Vector2(mouseX, mouseY));

	if (canDrawRect)
	{
		isDrawingRect = true;
		canMoveRect = false;
		canDrawRect = false;

		MovableRect* newRect = new MovableRect(currentMousePos, 0, 0, { 0, 0, 0 }, false, this);
		addRect(newRect);
	}

	for (int i = 0; i < rects.size(); i++)
	{
		if (!isDrawingRect)
		{
			if (rects[i]->checkHover(mouseX, mouseY))
			{
				rects[i]->onClick(mouseX, mouseY);
				// only move on rect on click
				break;
			}
		}
	}
}

void Canvas::onRelease()
{
	isDrawingRect = false;
	mouseReleasePos = currentMousePos;

	for (int i = 0; i < rects.size(); i++)
	{
		rects[i]->onRelease();
	}
}

void Canvas::render(int mouseX, int mouseY)
{
	Rect::render(mouseX, mouseY);

	setCurrentMousePos(Vector2(mouseX, mouseY));

	// render rects that were drawn
	for (int i = 0; i < rects.size(); i++)
	{
		rects[i]->render(mouseX, mouseY);
	}

	int i = rects.size() - 1;

	if (isDrawingRect)
	{
		float height = currentMousePos.y - mouseClickPos.y;
		float width = currentMousePos.x - mouseClickPos.x;

		rects[i]->setHeight(height);
		rects[i]->setWidth(width);
	}
}