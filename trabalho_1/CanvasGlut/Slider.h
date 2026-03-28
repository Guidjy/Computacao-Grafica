#pragma once

#include "Rect.h"
#include "Vector2.h"
#include "Circle.h"
#include <array>
#include <functional>


class Slider : public Rect
{
private:
	bool isClicked;

	Circle *holder;

	std::function<void()> onDragCallback;

public:
	Slider(Vector2 _pos, float _height, float _width, std::array<float, 3> _color = { 0, 0, 0 },
		bool _isFilled = true, std::function<void()> _onReleaseCallback = nullptr);

	float getHolderX() { return holder->getPos().x; }
	void setHolderX(float _holderX);

	std::function<void()> getOnDragCallback() { return onDragCallback; }
	void setOnDragCallback(std::function<void()> _onReleaseCallback) { onDragCallback = _onReleaseCallback; }

	// returns a 0 - 1 value based on the holder's position in the slider
	float getSliderValue();

	void onClick() override;

	void onRelease() override;

	void onDrag(int mouseX);

	void render(int mouseX, int mouseY);
};

