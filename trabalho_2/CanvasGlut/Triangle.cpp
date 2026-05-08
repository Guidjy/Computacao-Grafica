#include "Triangle.h"
#include "gl_canvas2d.h"

Triangle::Triangle(float _width, float _height, Vector2 _pos, std::array<float, 3> _color, bool _isFilled)
	: Shape(_pos, _color, _isFilled)
{
	width = _width;
	height = _height;
	
	float hw = width / 2;
	float hh = height / 2;
	vertices = { pos + Vector2(0, -hh), pos + Vector2(hw, hh), pos + Vector2(-hw, hh) };
}

void Triangle::render(int mouseX, int mouseY)
{
	CV::triangleFill(vertices);
}