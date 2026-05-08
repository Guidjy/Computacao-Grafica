#pragma once
#include "Menu.h"
#include "SpaceBackground.h"
#include "Button.h"
#include "Text.h"
#include "Dificulties.h"

extern SpaceBackground* mainMenuBackground;
extern Button* easyButton;
extern Text* easyText;
extern Button* hardButton;
extern Text* hardText;
extern Dificulties difficulty;

void mainMenuInit(Menu*& self, int height, int width);

void setEasyDifficulty();

void setHardDifficulty();