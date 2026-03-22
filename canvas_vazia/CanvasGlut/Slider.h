#pragma once

#include "Rect.h"
#include "Vector2.h"
#include "Circle.h"
#include <array>


class Slider : public Rect
{
private:
	bool isClicked;
	Circle *holder;

public:
	Slider(Vector2 _pos, float _height, float _width, std::array<float, 3> _color = { 0, 0, 0 }, bool _isFilled = true);

	float getHolderX() { return holder->getPos().x; }
	void setHolderX(float _holderX)
	{
		if (_holderX < pos.x)
		{
			_holderX = pos.x;
		}
		else if (_holderX > pos.x + width)
		{
			_holderX = pos.x + width;
		}

		Vector2 newPos = holder->getPos();
		newPos.x = _holderX;
		holder->setPos(newPos);
	}

	void onClick() override;

	void onRelease() override;

	void onDrag(int mouseX);

	void render(int mouseX, int mouseY);
};

