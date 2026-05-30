#include "Circle.h"
#include "gl_canvas2d.h"
#include "Vector2.h"


Circle::Circle(Vector2 _pos, float _radius, int _div, std::array<float, 3> _color, bool _isFilled) : Shape(_pos, _color, _isFilled)
{
	radius = _radius;
	div = _div;
}

void Circle::render()
{
	Shape::render();

	if (isFilled)
	{
		CV::circleFill(pos, radius, div);
	}
	else
	{
		CV::circle(pos, radius, div);
	}
}