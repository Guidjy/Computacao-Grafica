#include "Canvas.h"
#include "MovableRect.h"
#include "Image.h"


Canvas::Canvas(Vector2 _pos, float _height, float _width, std::array<float, 3> _color, bool _isFilled)
	: Rect(_pos, _height, _width, _color, _isFilled)
{
	canDrawRect = false;
	isDrawingRect = false;
	canInsertImage = false;
	isImageGrayscale = false;
	currentMousePos = Vector2(0, 0);
	mouseClickPos = Vector2(0, 0);
	mouseReleasePos = Vector2(0, 0);
	drawings = std::vector<MovableRect*>();
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

void Canvas::rotateImage()
{
	Image* image = nullptr;
	if (drawings.size() > 0)
	{
		// images are always added to the beggining of the list
		image = dynamic_cast<Image*>(drawings[0]);
	}
	
	if (image)
	{
		image->setRotation(image->getRotation() + 1);
	}
}

void Canvas::setImageScale(int scale)
{
	// images are always added to the beggining of the list
	Image* image = dynamic_cast<Image*>(drawings[0]);

	if (image)
	{
		image->setScale(scale);
	}
}

void Canvas::addDrawing(MovableRect* drawing)
{
	// checks if drawing is an image
	if (Image* image = dynamic_cast<Image*>(drawing))
	{
		// adds it to the beginning of hte list so that rects can be rendered on top of it
		drawings.insert(drawings.begin(), drawing);
	}
	else
	{
		drawings.push_back(drawing);
	}
}

void Canvas::tryAddRect(int mouseX, int mouseY)
{
	if (canDrawRect)
	{
		isDrawingRect = true;
		canDrawRect = false;

		MovableRect* newRect = new MovableRect(currentMousePos, 0, 0, { 0, 0, 0 }, false, this);
		addDrawing(newRect);
	}
}

void Canvas::tryAddImage(int mouseX, int mouseY)
{
	if (canInsertImage)
	{
		canInsertImage = false;

		Image* newImage = new Image(currentMousePos, ".\\images\\carol.bmp", this);
		if (isImageGrayscale)
		{
			newImage->setIsGrayscale(true);
		}

		addDrawing(newImage);
	}
}

void Canvas::onClick(int mouseX, int mouseY)
{
	if (!checkHover(mouseX, mouseY))
	{
		return;
	}

	setMouseClickPos(Vector2(mouseX, mouseY));

	tryAddRect(mouseX, mouseY);
	tryAddImage(mouseX, mouseY);

	for (int i = 0; i < drawings.size(); i++)
	{
		if (!isDrawingRect && !canInsertImage)
		{
			if (drawings[i]->checkHover(mouseX, mouseY))
			{
				drawings[i]->onClick(mouseX, mouseY);
				// only move one drawing on click
				break;
			}
		}
	}
}

void Canvas::onRelease()
{
	isDrawingRect = false;
	mouseReleasePos = currentMousePos;

	for (int i = 0; i < drawings.size(); i++)
	{
		drawings[i]->onRelease();
	}
}

void Canvas::render(int mouseX, int mouseY)
{
	Rect::render(mouseX, mouseY);

	setCurrentMousePos(Vector2(mouseX, mouseY));

	for (int i = 0; i < drawings.size(); i++)
	{
		drawings[i]->render(mouseX, mouseY);
	}

	if (isDrawingRect)
	{
		float height = currentMousePos.y - mouseClickPos.y;
		float width = currentMousePos.x - mouseClickPos.x;
		int lastRectIndex = drawings.size() - 1;

		drawings[lastRectIndex]->setHeight(height);
		drawings[lastRectIndex]->setWidth(width);
	}
}