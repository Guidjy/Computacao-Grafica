#pragma once
#include "MovableRect.h"
#include "Bmp.h"
#include <string>


class Image : public MovableRect
{
private:
	Bmp* bitMap;
	
	std::string imagePath;

public:
	Image(Vector2 _pos, std::string _imagePath, Canvas* _parentCanvas = nullptr);

	void render(int mouseX, int mouseY) override;
};

