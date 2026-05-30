#pragma once

#include "Shape.h"


class Circle : public Shape
{
private:
	float radius;
	int div;
	
public:
	Circle(Vector2 _pos, float _radius, int _div, std::array<float, 3> _color = { 0, 0, 0 }, bool _isFilled = false);

	float getRadius() { return radius; }
	void setRadius(float _radius) { radius = _radius; }

	int getDiv() { return div; }
	void setDiv(int _div) { div = _div; }

	bool checkHover(int mouseX, int mouseY) override;

	bool checkClick(int mouseX, int mouseY, int mouseState) override;

	void render(int mouseX, int mouseY) override;
};

