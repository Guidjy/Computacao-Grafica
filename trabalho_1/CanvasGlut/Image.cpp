#include "Image.h"
#include "gl_canvas2d.h"


Image::Image(Vector2 _pos, std::string _imagePath, Canvas* _parentCanvas)
	: MovableRect(_pos, 1, 1, { 1, 1, 1 }, false, _parentCanvas)
{
	imagePath = _imagePath;
	bitMap = new Bmp(imagePath.c_str());

	setWidth(bitMap->getWidth());
	setHeight(bitMap->getHeight());
}

void Image::render(int mouseX, int mouseY)
{
	MovableRect::render(mouseX, mouseY);

	CV::translate(pos.x, pos.y);
	bitMap->render();
	CV::translate(0, 0);
}