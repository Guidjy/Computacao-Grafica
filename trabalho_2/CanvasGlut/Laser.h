#pragma once
#include "Vector2.h"

class Laser
{
private:
	Vector2 pos; // tip of the laser

	Vector2 direction;
	
	const float velocity = 400;

	const float length = 20;

public:
	Laser(Vector2 _direction, Vector2 _pos);

	void update();

	void render();
};

