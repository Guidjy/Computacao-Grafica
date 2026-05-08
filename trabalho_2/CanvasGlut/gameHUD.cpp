#include "gameHUD.h"

// components
SpaceBackground* background = nullptr;
Text* lives = nullptr;
Text* pointsText = nullptr;
int points = 0;

void gameHUDInit(Menu*& self, int height, int width)
{
	self = new Menu(height, width, { 0, 0, 0 });

	// background
	background = new SpaceBackground(height, width);
	// lives
	lives = new Text(Vector2(0, 20), "Lives: 3", { 1, 1, 0 });
	// points
	pointsText = new Text(Vector2(0, 40), "points: 0", { 1, 1, 0 });

	self->addComponent(background);
	self->addComponent(lives);
	self->addComponent(pointsText);
}

void HUDSetLives(int hp)
{
	if (hp < 0)
	{
		hp = 0;
	}

	lives->setText("lives: " + std::to_string(hp));
}

void HUDSetPoints(int p)
{
	points += p;
	pointsText->setText("Score: " + std::to_string(points));
}