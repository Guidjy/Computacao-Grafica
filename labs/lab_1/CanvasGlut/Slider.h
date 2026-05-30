#pragma once

#include "gl_canvas2d.h"
#include "Vector2.h"


class Slider
{
public:
	Vector2 pos;
	float height;
	float width;
	Vector2 buttonPos;
	float buttonRadius;
	bool isClicked;


	Slider(Vector2 _pos, float _height, float _width);
	
	void render(int mouseX);

	bool checkHover(int mouseX, int mouseY);

	void onClick();

	void onRelease();

	void onDrag(int mouseX);
};

