#pragma once
#include "Rect.h"
#include "Canvas.h"
#include "Vector2.h"

class MovableRect : public Rect
{
private:
	bool isClicked;

	Canvas* parentCanvas;

public:
	MovableRect(Vector2 _pos, float _height, float _width, std::array<float, 3> _color = { 0, 0, 0 }, 
		bool _isFilled = false, Canvas* _parentCanvas = nullptr);

	bool getIsClicked() { return isClicked; }

	void onClick(int mouseX, int mouseY) override;

	void onDrag(int mouseX, int mouseY);

	void onRelease() override;

	virtual void render(int mouseX, int mouseY) override;
};

