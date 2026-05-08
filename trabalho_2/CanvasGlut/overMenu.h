#pragma once
#include "Menu.h"
#include "Rect.h"
#include "Text.h"
#include "SpaceBackground.h"

extern SpaceBackground* overBackground;
extern Rect* leaderBoard;
extern Text* title;
extern Text* first;
extern Text* second;
extern Text* third;

void overMenuInit(Menu*& self, int height, int width);

void getLeaderboard(int score);