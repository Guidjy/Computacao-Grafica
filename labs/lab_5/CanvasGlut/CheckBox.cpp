#include "CheckBox.h"
#include "gl_canvas2d.h"
#include "Vector2.h"


CheckBox::CheckBox(Vector2 _pos, float _size, std::array<float, 3> _color, bool _isFilled, std::function<void()> _onClick)
	: Button(_pos, _size, _size, "", _color, _isFilled, _onClick)
{
	isChecked = false;
	size = _size;
}

void CheckBox::check()
{
	isChecked = !isChecked;
}

void CheckBox::onClick()
{
	Button::onClick();

	check();
}

void CheckBox::render(int mouseX, int mouseY)
{
	Button::render(mouseX, mouseY);

	if (isChecked)
	{
		Vector2 point1 = Vector2(pos.x + size / 5, pos.y + size / 2);
		Vector2 point2 = Vector2(pos.x + size / 2, pos.y + size - size / 5);
		Vector2 point3 = Vector2(pos.x + size - size / 5, pos.y + size / 5);
		CV::color(color[0] * 1.5, color[1] * 1.5, color[2] * 1.5);
		CV::line(point1, point2);
		CV::line(point2, point3);
	}
}