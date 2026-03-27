#pragma once
#include "Vector2.h"
#include "Rect.h"
#include <vector>


class MovableRect;
class Image;


class Canvas : public Rect
{
private:
	bool canDrawRect;

	bool isDrawingRect;

	bool canInsertImage;

	bool isImageGrayscale;

	Vector2 currentMousePos;

	Vector2 mouseClickPos;

	Vector2 mouseReleasePos;

	std::vector<MovableRect*> drawings;

	void addDrawing(MovableRect* drawing);

	void tryAddRect(int mouseX, int mouseY);

	void tryAddImage(int mouseX, int mouseY);

public:
	Canvas(Vector2 _pos, float _height, float _width, std::array<float, 3> _color = { 0, 0, 0 }, bool _isFilled = false);

	bool getCanDrawRect() { return canDrawRect; }
	void setCanDrawRect(bool _canDrawRect) { canDrawRect = _canDrawRect; }

	bool getIsDrawingRect() { return isDrawingRect; }
	void setIsDrawingRect(bool _isDrawingRect) { isDrawingRect = _isDrawingRect; }

	bool getCanInsertImage() { return canInsertImage; }
	void setCanInsertImage(bool _canInsertImage) { canInsertImage = _canInsertImage; }

	bool getIsImageGrayscale() { return isImageGrayscale; }
	void setIsImageGrayscale(bool _isImageGrayscale) { isImageGrayscale = _isImageGrayscale; }

	Vector2 getCurrentMousePos() { return currentMousePos; }
	void setCurrentMousePos(Vector2 _currentMousePos);

	Vector2 getMouseClickPos() { return mouseClickPos; }
	void setMouseClickPos(Vector2 _mouseClickPos) { mouseClickPos = _mouseClickPos; }

	Vector2 getMouseReleasePos() { return mouseReleasePos; }
	void setMouseReleasePos(Vector2 _mouseReleasePos) { mouseReleasePos = _mouseReleasePos; }

	// rotates the most recently added image 90 degrees
	void rotateImage();

	void onClick(int mouseX, int mouseY) override;

	void onRelease() override;

	void render(int mouseX, int mouseY) override;
};

