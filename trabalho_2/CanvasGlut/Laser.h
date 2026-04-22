#pragma once
#include "Vector2.h"

class Laser
{
private:

	Vector2 direction;
	
	const float velocity = 400;

	const float length = 20;

	bool shouldBeDeleted;

public:
	Vector2 pos; // tip of the laser

	bool isFriendly;

	Laser(Vector2 _direction, Vector2 _pos, bool _isFriendly);

	bool getShouldBeDeleted() { return shouldBeDeleted; }

	bool isOutOfBounds(int screenWidth, int screenHeight);

	void update();

	void render();
};

