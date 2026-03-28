#include "Image.h"
#include "gl_canvas2d.h"


Image::Image(Vector2 _pos, std::string _imagePath, Canvas* _parentCanvas)
	: MovableRect(_pos, 1, 1, { 1, 1, 1 }, false, _parentCanvas)
{
	imagePath = _imagePath;
	bitMap = new Bmp(imagePath.c_str());

	setWidth(bitMap->getWidth());
	originalWidth = width;
	setHeight(bitMap->getHeight());
	originalHeight = height;
}

void Image::setScale(int _scale)
{
	bitMap->setScale(_scale);

	setHeight(originalHeight * _scale);
	setWidth(originalWidth * _scale);
}

void Image::render(int mouseX, int mouseY)
{
	MovableRect::render(mouseX, mouseY);

	CV::translate(pos.x, pos.y);
	bitMap->render();
	CV::translate(0, 0);
}