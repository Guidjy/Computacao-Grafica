#include "GlobalSettings.h"
#include "mouseStates.h"
#include "gl_canvas2d.h"


// screen settings
int screenWidth = 1920;
int screenHeight = 1080;

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


void updateMousePosition()
{
	oldMouseX = mouseX;
	oldMouseY = mouseY;
}

void renderBackground()
{
	CV::color(0, 0, 0);
	CV::rectFill(0, 0, screenWidth, screenHeight);
	CV::translate(screenWidth / 2, screenHeight / 2);
}

void renderHUD()
{
	CV::color(1, 1, 1);

	float hw = screenWidth / 2;
	float hh = screenHeight / 2;

	CV::text(-hw + 10, 20 - hh, "Move Camera: WASD");
	CV::text(-hw + 10, 40 - hh, "Move Vehicle: Arrow Keys");
	CV::text(-hw + 10, 60 - hh, "Increase/Decrease Hill Size: Z/X");
	CV::text(-hw + 10, 80 - hh, "Rotate Surface: Mouse Drag");
}