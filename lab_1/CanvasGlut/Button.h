#pragma once

#include "gl_canvas2d.h"
#include "Vector2.h"
#include <string>
#include <array>


class Button
{
private:
	float height;
	float width;

	Vector2 pos;

	std::string text;

	std::array<float, 3> color;

	bool isHovering;

public:
	// constructor, getters and setters
	Button(float _x, float _y, float _height, float _width, std::string _text, std::array<float, 3> _color = { 1, 1, 1 });

	float getHeight() { return height; };
	void setHeight(float _height) { height = _height; };

	float getWidth() { return width; };
	void setWidth(float _width) { width = _width; };

	Vector2 getPos() { return pos; };
	void setPos(Vector2 _pos) { pos = _pos; };

	std::string getString() { return text; };
	void setString(std::string _text) { text = _text; };

	std::array<float, 3> getcColor() { return color; };
	void setColor(std::array<float, 3> _color) { color = _color; };

	bool getIsHovering() { return isHovering; };
	void setIsHovering(bool _isHovering) { isHovering = _isHovering; };


	void render();

	bool checkHover(int mouseX, int mouseY);

	void onHover();

	void onHoverExit();
};
