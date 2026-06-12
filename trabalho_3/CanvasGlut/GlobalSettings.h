#pragma once
#include <list>


// screen settings
extern int screenWidth;
extern int screenHeight;

// mouse state
extern int mouseX;
extern int mouseY;
extern int oldMouseX;
extern int oldMouseY;
extern int mouseState;
extern int oldMouseState;

// keyboard state
extern std::list<int> pressedKeys;

// terrain settings
extern const int TERRAIN_WIDTH;