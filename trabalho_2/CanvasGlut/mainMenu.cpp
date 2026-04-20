#include "mainMenu.h"


void mainMenuInit(Menu*& self, int height, int width)
{
	self = new Menu(height, width, { 0, 0, 0 });
}