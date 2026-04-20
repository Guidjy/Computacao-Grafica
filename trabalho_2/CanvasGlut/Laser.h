#pragma once
#include "Vector2.h"

class Laser
{
private:

	Vector2 direction;
	
	const float velocity = 400;

	const float length = 20;

public:
	Vector2 pos; // tip of the laser

	Laser(Vector2 _direction, Vector2 _pos, bool _isFriendly);

	bool isFriendly;

	void update();

	void render();
};

