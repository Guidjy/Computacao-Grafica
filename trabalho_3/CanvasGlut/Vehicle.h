#pragma once
#include "Vector2.h"
#include "Vector3.h"


class Vehicle
{
private:
	const float width = 6;
	const float lenght = 9;

	Vector3 pos;
	
	Vector2 velocity;
	const float acceleration = 5.0f;
	const float friction = 0.9f;
	Vector2 direction;  // direction in the (x, z) plane

	const float MAX_SPEED = 30.0f;

	void handleKeyboardInput();

public:
	Vehicle();

	void update();

	void render();
};

