#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Terrain.h"
#include <array>


class Vehicle
{
private:
	const float width = 3;
	const float lenght = 5;
	std::array<Vector3, 3> wheels;
	float currentHorizontalAngle; 

	Vector3 pos;
	Vector2 velocity;
	Vector2 direction;  // direction in the (x, z) plane

	const float acceleration = 750.0f;
	const float friction = 0.9f;
	const float MAX_VELOCITY = 10.0f;

	Terrain* terrainReference;

	void handleKeyboardInput();

	// rotates the vehicle based on its velocity vector
	void rotate();

	void move();

public:
	Vehicle(Terrain* _terrainReference);

	void update();

	void render();
};

