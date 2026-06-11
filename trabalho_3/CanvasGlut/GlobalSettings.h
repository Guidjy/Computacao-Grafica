#pragma once
#include <list>

extern int screenWidth;
extern int screenHeight;

extern int mouseX;
extern int mouseY;
extern int oldMouseX;
extern int oldMouseY;
extern int mouseState;
extern int oldMouseState;

extern const float SENSITIVITY;

extern std::list<int> pressedKeys;