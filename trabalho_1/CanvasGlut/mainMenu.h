// main menu components, yaout and events


#pragma once
#include "Menu.h"
#include "Rect.h"
#include "Button.h"
#include "CheckBox.h"
#include "Slider.h"
#include "Text.h"
#include "Canvas.h"


extern Rect* navBar;
extern Button* insertRectButton;
extern Button* insertImageButton;
extern Button* rotateImageButton;
extern Text* rotateImageButtonText;
extern CheckBox* setGrayscaleCheckBox;
extern Text* setGrayscaleCheckBoxText;
extern Slider* focusSlider;
extern Text* focusSliderText;
extern Canvas* canvasSurface;

void mainMenuInit(Menu*& self, int height, int width);

// events

void drawRect();

void insertImage();

void setImageGrayscale();

void rotateImage();