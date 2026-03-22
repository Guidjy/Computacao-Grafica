#include "Circle.h"
#include "gl_canvas2d.h"
#include "Vector2.h"
#include "math.h"
#include "mouseStates.h"


Circle::Circle(Vector2 _pos, float _radius, int _div, std::array<float, 3> _color, bool _isFilled) : Shape(_pos, _color, _isFilled)
{
	radius = _radius;
	div = _div;
}

bool Circle::checkHover(int mouseX, int mouseY)
{
	return sqrt(pow((mouseX - pos.x), 2) + pow((mouseY - pos.y), 2));
}

bool Circle::checkClick(int mouseX, int mouseY, int mouseState)
{
	return checkHover(mouseX, mouseY) && mouseState == CLICK;
}

void Circle::render(int mouseX, int mouseY)
{
	Shape::render(mouseX, mouseY);

	if (isFilled)
	{
		CV::circleFill(pos, radius, div);
	}
	else
	{
		CV::circle(pos, radius, div);
	}
}