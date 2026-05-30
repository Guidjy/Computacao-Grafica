#include "Shape.h"
#include "gl_canvas2d.h"
#include <iostream>


Shape::Shape(Vector2 _pos, std::array<float, 3> _color, bool _isFilled)
{
	pos = _pos;
	color = _color;
	isFilled = _isFilled;
}

void Shape::render(int mouseX, int mouseY)
{
	CV::color(color[0], color[1], color[2]);
}