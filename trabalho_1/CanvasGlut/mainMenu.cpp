#include "mainMenu.h"
#include "gl_canvas2d.h"
#include "Vector2.h"
#include "Rect.h"
#include "Button.h"
#include "Slider.h"
#include "CheckBox.h"
#include "Text.h"


// components
Rect* navBar = NULL;
Button* insertRectButton = NULL;
Button* insertImageButton = NULL;
Button* rotateImageButton = NULL;
Text* rotateImageButtonText = NULL;
CheckBox* setGrayscaleCheckBox = NULL;
Text* setGrayscaleCheckBoxText = NULL;
Slider* focusSlider = NULL;
Text* focusSliderText = NULL;
Rect* canvasSurface = NULL;


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
	insertImageButton = new Button(Vector2(navBar->getWidth() / 5 * 1 + margin, buttonY), buttonHeight, buttonWidth, "Image", {0.494, 0.796, 0.580}, true);
	rotateImageButton = new Button(Vector2(navBar->getWidth() / 5 * 2 + margin, buttonY), buttonHeight, buttonHeight, "", { 0.447, 0.537, 0.855 }, true);
	rotateImageButtonText = new Text(Vector2(navBar->getWidth() / 5 * 2 + margin + buttonHeight + 5, buttonY + buttonHeight / 2), "rotate image", { 1, 1, 1 });
	setGrayscaleCheckBox = new CheckBox(Vector2(navBar->getWidth() / 5 * 3 + margin, buttonY), buttonHeight, { 0.447, 0.537, 0.855 }, true);
	setGrayscaleCheckBoxText = new Text(Vector2(navBar->getWidth() / 5 * 3 + margin + buttonHeight + 5, buttonY + buttonHeight / 2), "image grayscale", { 1, 1, 1 });
	focusSlider = new Slider(Vector2(navBar->getWidth() / 5 * 4 + margin, buttonY + buttonHeight / 3), buttonHeight / 4, buttonWidth - margin, { 0.447, 0.537, 0.855 }, true);
	focusSliderText = new Text(Vector2(navBar->getWidth() / 5 * 4 + margin, buttonY + buttonHeight / 3 + 30), "image grayscale", { 1, 1, 1 });

	self->addComponent(navBar);
	self->addComponent(insertRectButton);
	self->addComponent(insertImageButton);
	self->addComponent(rotateImageButton);
	self->addComponent(rotateImageButtonText);
	self->addComponent(setGrayscaleCheckBox);
	self->addComponent(setGrayscaleCheckBoxText);
	self->addComponent(focusSlider);
	self->addComponent(focusSliderText);

	// canvas
	float canvasX = width / 16;
	float canvasY = navBar->getHeight() + height / 9;
	float canvasWidth = width - canvasX * 2;
	float canvasHeight = height - navBar->getHeight() - height / 9 * 2;

	canvasSurface = new Rect(Vector2(canvasX, canvasY), canvasHeight, canvasWidth, { 1, 1, 1 }, true);
	self->addComponent(canvasSurface);
}