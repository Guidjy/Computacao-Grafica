#include "Rect.h"
#include "gl_canvas2d.h"
#include "Vector2.h"


Rect::Rect(Vector2 _pos, float _height, float _width, std::array<float, 3> _color, bool _isFilled) : Shape(_pos, _color, _isFilled)
{
	height = _height;
	width = _width;

	updateVertices();
}

void Rect::updateVertices()
{
	vertices[0] = Vector2(pos.x, pos.y);
	vertices[1] = Vector2(pos.x + width, pos.y);
	vertices[2] = Vector2(pos.x, pos.y + height);
	vertices[3] = Vector2(pos.x + width, pos.y + height);
}

void Rect::render()
{
	Shape::render();

	if (isFilled)
	{
		CV::rectFill(pos, Vector2(pos.x + width, pos.y + height));
	}
	else
	{
		CV::rect(pos, Vector2(pos.x + width, pos.y + height));
	}
}