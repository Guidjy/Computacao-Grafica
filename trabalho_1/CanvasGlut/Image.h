#pragma once
#include "MovableRect.h"
#include "Bmp.h"
#include <string>


class Image : public MovableRect
{
private:
	Bmp* bitMap;
	
	std::string imagePath;

	bool isGrayscale;

public:
	Image(Vector2 _pos, std::string _imagePath, Canvas* _parentCanvas = nullptr);

	bool getIsGrayscale() { return bitMap->getIsGrayscale(); }
	void setIsGrayscale(bool _isGrayscale) { bitMap->setIsGrayscale(_isGrayscale); }

	void render(int mouseX, int mouseY) override;
};

