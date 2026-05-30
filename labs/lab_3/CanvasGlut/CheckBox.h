#pragma once

#include "Button.h"


class CheckBox : public Button
{
private:
	bool isChecked;

	float size;

public:
	CheckBox(Vector2 _pos, float _size, std::array<float, 3> _color = { 0, 0, 0 },
		bool _isFilled = false, std::function<void()> _onClick = nullptr);

	void check();

	void onClick() override;

	void render(int mouseX, int mouseY);
};

