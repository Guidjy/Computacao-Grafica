#include "GlobalSettings.h"
#include "mouseStates.h"


// screen settings
int screenWidth = 1200;
int screenHeight = 675;

// mouse state
int mouseX = 0;
int mouseY = 0;
int oldMouseX = 0;
int oldMouseY = 0;
int oldMouseState = HOVER;
int mouseState = HOVER;

// keyboard state
std::list<int> pressedKeys = std::list<int>();

// terrain settings
const int TERRAIN_WIDTH = 100.0f;