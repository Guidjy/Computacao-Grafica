#pragma once
#include "Rect.h"
#include "Vector2.h"
#include <vector>


class Canvas : public Rect
{
private:
	bool canDrawRect;

	bool isDrawingRect;

	Vector2 currentMousePos;

	Vector2 mouseClickPos;

	Vector2 mouseReleasePos;

	std::vector<Rect*> rects;

public:
	Canvas(Vector2 _pos, float _height, float _width, std::array<float, 3> _color = { 0, 0, 0 }, bool _isFilled = false);

	bool getCanDrawRect() { return canDrawRect; }
	void setCanDrawRect(bool _canDrawRect) { canDrawRect = _canDrawRect; }

	bool getIsDrawingRect() { return isDrawingRect; }
	void setIsDrawingRect(bool _isDrawingRect) { isDrawingRect = _isDrawingRect; }

	Vector2 getCurrentMousePos() { return currentMousePos; }
	void setCurrentMousePos(Vector2 _currentMousePos);

	Vector2 getMouseClickPos() { return mouseClickPos; }
	void setMouseClickPos(Vector2 _mouseClickPos) { mouseClickPos = _mouseClickPos; }

	Vector2 getMouseReleasePos() { return mouseReleasePos; }
	void setMouseReleasePos(Vector2 _mouseReleasePos) { mouseReleasePos = _mouseReleasePos; }

	void addRect(Rect* _rect) { rects.push_back(_rect); }

	void onClick(int mouseX, int mouseY) override;

	void onRelease() override;

	void render(int mouseX, int mouseY) override;
};

