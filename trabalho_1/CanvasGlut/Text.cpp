#include "Text.h"
#include "gl_canvas2d.h"


Text::Text(Vector2 _pos, std::string _text, std::array<float, 3> _color)
	: Shape(_pos, _color)
{
	text = _text;
}

void Text::render(int mouseX, int mouseY)
{
	Shape::render(mouseX, mouseY);

	CV::text(pos.x, pos.y, text.c_str());
}