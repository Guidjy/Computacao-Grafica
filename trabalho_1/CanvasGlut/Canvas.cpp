#include "Canvas.h"


Canvas::Canvas(Vector2 _pos, float _height, float _width, std::array<float, 3> _color, bool _isFilled)
	: Rect(_pos, _height, _width, _color, _isFilled)
{
	canDrawRect = false;
	isDrawingRect = false;
	currentMousePos = Vector2(0, 0);
	mouseClickPos = Vector2(0, 0);
	mouseReleasePos = Vector2(0, 0);
	rects = std::vector<Rect*>();
}


void Canvas::setCurrentMousePos(Vector2 _currentMousePos)
{
	currentMousePos = _currentMousePos;

	// keeps the current mouse position within the canvas
	if (currentMousePos.x < pos.x)
	{
		currentMousePos.x = pos.x;
	}
	else if (currentMousePos.x > pos.x + width)
	{
		currentMousePos.x = pos.x + width;
	}
	else if (currentMousePos.y < pos.y)
	{
		currentMousePos.y = pos.y;
	}
	else if (currentMousePos.y > pos.y + height)
	{
		currentMousePos.y = pos.y;
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
		canDrawRect = false;

		Rect* newRect = new Rect(currentMousePos, 0, 0);
		addRect(newRect);
	}
}

void Canvas::onRelease()
{
	isDrawingRect = false;
	mouseReleasePos = currentMousePos;
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

	if (isDrawingRect)
	{
		int i = rects.size() - 1;
		float height = currentMousePos.y - mouseClickPos.y;
		float width = currentMousePos.x - mouseClickPos.x;

		rects[i]->setHeight(height);
		rects[i]->setWidth(width);
	}
}