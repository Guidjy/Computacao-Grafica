#pragma once

#include <string>
#include "Vector2.h"
#include "Shape.h"


class Text : public Shape
{
private:
	std::string text;

public:
	Text(Vector2 _pos, std::string _text, std::array<float, 3> _color = { 0, 0, 0 });

	std::string getText() { return text; }
	void setText(std::string _text) { text = _text; }

	bool checkHover(int mouseX, int mouseY) { return false; }

	bool checkClick(int mouseX, int mouseY, int mouseState) { return false; }

	void render(int mouseX, int mouseY) override;
};

