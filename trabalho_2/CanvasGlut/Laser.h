#pragma once
#include "Vector2.h"
#include <array>

class Laser
{
private:
	Vector2 direction;
	
	const float velocity = 400;

	float length;

	bool shouldBeDeleted;

	bool isCurved;

	std::array<Vector2, 3> curvedShotControlPoints;

	float t;

public:
	Vector2 pos; // tip of the laser

	bool isFriendly;

	Laser(Vector2 _direction, Vector2 _pos, bool _isFriendly);

	bool getShouldBeDeleted() { return shouldBeDeleted; }

	bool getIsCurved() { return isCurved; }

	bool isOutOfBounds(int screenWidth, int screenHeight);

	void update(int screenWidth, int screenHeight);

	void render();
};

