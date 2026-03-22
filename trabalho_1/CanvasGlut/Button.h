#pragma once

#include "gl_canvas2d.h"
#include "Vector2.h"
#include "Rect.h"
#include <string>
#include <array>
#include <functional>


class Button : public Rect
{
private:
	std::string text;

	std::function<void()> onClickCallback;

	void onHover();

	void onHoverExit();

public:
	Button(Vector2 _pos, float _height, float _width, std::string _text = "", std::array<float, 3> _color = {0, 0, 0},
			bool _isFilled = false, std::function<void()> _onClick = nullptr);
	virtual ~Button() {}

	std::string getText() { return text; }
	void setText(std::string _text) { text = _text; }

	std::function<void()> getOnClickCallback() { return onClickCallback; }
	void setOnClickCallback(std::function<void()> _onClick) { onClickCallback = _onClick; }

	virtual void onClick() override;

	virtual void render(int mouseX, int mouseY) override;
};
