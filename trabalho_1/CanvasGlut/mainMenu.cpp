#include "mainMenu.h"
#include "gl_canvas2d.h"
#include "Vector2.h"
#include "Rect.h"
#include "Button.h"
#include "Slider.h"
#include "CheckBox.h"
#include "Text.h"
#include <iostream>
#include <math.h>


// components
Rect* navBar = nullptr;
Button* insertRectButton = nullptr;
Button* insertImageButton = nullptr;
Button* rotateImageButton = nullptr;
Text* rotateImageButtonText = nullptr;
CheckBox* setGrayscaleCheckBox = nullptr;
Text* setGrayscaleCheckBoxText = nullptr;
Slider* scaleSlider = nullptr;
Text* scaleSliderText = nullptr;
Canvas* canvasSurface = nullptr;


void mainMenuInit(Menu*& self, int height, int width)
{
	self = new Menu(height, width, { 0.118, 0.129, 0.141 });

	// navbar components
	navBar = new Rect(Vector2(0, 0), height / 6, width, { 0.259, 0.271, 0.286 }, true);
	float margin = navBar->getWidth() / 5 * 0.2;
	float buttonHeight = navBar->getHeight() / 2;
	float buttonWidth = navBar->getWidth() / 5 * 0.8;
	float buttonY = navBar->getHeight() / 2 - buttonHeight / 2;

	insertRectButton = new Button(Vector2(navBar->getWidth() / 5 * 0 + margin, buttonY), buttonHeight, buttonWidth, "Rectangle", { 0.494, 0.796, 0.580 }, true);
	insertRectButton->setOnClickCallback(drawRect);

	insertImageButton = new Button(Vector2(navBar->getWidth() / 5 * 1 + margin, buttonY), buttonHeight, buttonWidth, "Image", {0.494, 0.796, 0.580}, true);
	insertImageButton->setOnClickCallback(insertImage);

	rotateImageButton = new Button(Vector2(navBar->getWidth() / 5 * 2 + margin, buttonY), buttonHeight, buttonHeight, "", { 0.447, 0.537, 0.855 }, true);
	rotateImageButtonText = new Text(Vector2(navBar->getWidth() / 5 * 2 + margin + buttonHeight + 5, buttonY + buttonHeight / 2), "rotate image", { 1, 1, 1 });
	rotateImageButton->setOnClickCallback(rotateImage);

	setGrayscaleCheckBox = new CheckBox(Vector2(navBar->getWidth() / 5 * 3 + margin, buttonY), buttonHeight, { 0.447, 0.537, 0.855 }, true);
	setGrayscaleCheckBoxText = new Text(Vector2(navBar->getWidth() / 5 * 3 + margin + buttonHeight + 5, buttonY + buttonHeight / 2), "image grayscale", { 1, 1, 1 });
	setGrayscaleCheckBox->setOnClickCallback(setImageGrayscale);

	scaleSlider = new Slider(Vector2(navBar->getWidth() / 5 * 4 + margin, buttonY + buttonHeight / 3), buttonHeight / 4, buttonWidth - margin, { 0.447, 0.537, 0.855 }, true);
	scaleSliderText = new Text(Vector2(navBar->getWidth() / 5 * 4 + margin, buttonY + buttonHeight / 3 + 30), "image scale", { 1, 1, 1 });
	scaleSlider->setOnDragCallback(setImageScale);

	self->addComponent(navBar);
	self->addComponent(insertRectButton);
	self->addComponent(insertImageButton);
	self->addComponent(rotateImageButton);
	self->addComponent(rotateImageButtonText);
	self->addComponent(setGrayscaleCheckBox);
	self->addComponent(setGrayscaleCheckBoxText);
	self->addComponent(scaleSlider);
	self->addComponent(scaleSliderText);

	// canvas
	float canvasX = width / 16;
	float canvasY = navBar->getHeight() + height / 9;
	float canvasWidth = width - canvasX * 2;
	float canvasHeight = height - navBar->getHeight() - height / 9 * 2;

	canvasSurface = new Canvas(Vector2(canvasX, canvasY), canvasHeight, canvasWidth, { 1, 1, 1 }, true);
	self->addComponent(canvasSurface);
}

void drawRect()
{
	canvasSurface->setCanDrawRect(true);
	canvasSurface->setCanInsertImage(false);
}

void insertImage()
{
	canvasSurface->setCanInsertImage(true);
	canvasSurface->setCanDrawRect(false);
	// image scale = 1
	scaleSlider->setHolderX(0);
}

void setImageGrayscale()
{
	canvasSurface->setIsImageGrayscale(!canvasSurface->getIsImageGrayscale());
}

void setImageScale()
{
	float sliderValue = scaleSlider->getSliderValue();
	
	// 4 differents scales
	int scale = ceil(sliderValue * 4);
	canvasSurface->setImageScale(scale);
}

void rotateImage()
{
	canvasSurface->rotateImage();
}