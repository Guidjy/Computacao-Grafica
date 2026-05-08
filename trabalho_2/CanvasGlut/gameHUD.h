#pragma once
#include "Menu.h"
#include "Rect.h"
#include "Text.h"
#include "SpaceBackground.h"

extern SpaceBackground* background;
extern Text* lives;
extern Text* pointsText;
extern int points;

void gameHUDInit(Menu*& self, int height, int width);

// events
void HUDSetLives(int hp);

void HUDSetPoints(int p);
