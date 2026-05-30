#pragma once

#include "gl_canvas2d.h"
#include "Vector2.h"
#include "Rect.h"
#include <string>
#include <array>
#include <functional>


class Button : Rect
{
private:
	std::string text;

	bool isHovering;

	void onHover();

	void onHoverExit();

public:
	Button(Vector2 _pos, float _height, float _width, std::string _text="", std::array<float, 3> _color = {0, 0, 0}, 
			bool _isFilled = false, std::function<void()> _onClick = nullptr);

	std::string getText() { return text; }
	void setText(std::string _text) { text = _text; }

	std::function<void()> onClick;
	std::function<void()> getOnClick() { return onClick; }
	void setOnClick(std::function<void()> _onClick) { onClick = _onClick; }

	bool checkHover(int mouseX, int mouseY);

	bool checkClick(int mouseX, int mouseY, int mouseState);

	void render(int mouseX, int mouseY, int mouseState);
};
