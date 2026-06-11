#include "GlobalSettings.h"
#include "mouseStates.h"


int screenWidth = 1200;
int screenHeight = 675;

int mouseX = 0;
int mouseY = 0;
int oldMouseX = 0;
int oldMouseY = 0;
int oldMouseState = HOVER;
int mouseState = HOVER;

const float SENSITIVITY = 0.005f;

std::list<int> pressedKeys = std::list<int>();