#include "mainMenu.h"

// components
SpaceBackground* mainMenuBackground = nullptr; 
Button* easyButton = nullptr;
Text* easyText = nullptr;
Button* hardButton = nullptr;
Text* hardText = nullptr;
Dificulties difficulty;

void mainMenuInit(Menu*& self, int height, int width)
{
	self = new Menu(height, width, { 0, 0, 0 });

	// background
	mainMenuBackground = new SpaceBackground(height, width);
	// startButton
	float bw = 200;
	easyButton = new Button(Vector2(width / 2 - bw / 2, height / 2 - height / 4), bw / 2, bw, "", { 1, 1, 0 }, true, setEasyDifficulty);
	easyText = new Text(Vector2(width / 2 - bw / 2 + bw/2 - 40, height / 2 - height / 4 + bw/4), "Easy Mode");
	// difficulty checkbox
	hardButton = new Button(Vector2(width / 2 - bw / 2, height / 2), bw / 2, bw, "", { 1, 1, 0 }, true, setHardDifficulty);
	hardText = new Text(Vector2(width / 2 - bw / 2 + bw / 2 - 40, height / 2 + bw/4), "Hard Mode");

	self->addComponent(mainMenuBackground);
	self->addComponent(easyButton);
	self->addComponent(easyText);
	self->addComponent(hardButton);
	self->addComponent(hardText);
}

void setEasyDifficulty()
{
	difficulty = EASY;
	currentMenu = GAME;
}

void setHardDifficulty()
{
	difficulty = HARD;
	currentMenu = GAME;
}