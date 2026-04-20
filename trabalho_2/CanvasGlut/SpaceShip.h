#pragma once
#include "Laser.h"
#include "Vector2.h"
#include "Key.h"
#include <vector>


#define COOLDOWN 15;


class SpaceShip
{
protected:
	Vector2 pos;  // center of the spaceship
	Vector2 direction;
	Vector2 velocity;

	float acceleration;
	float friction;  // how fast the spaceship slows down
	float maxSpeed;

	float width;
	float height;
	std::array<float, 3> color;

	std::vector<Laser> shots;
	bool isShooting;
	int cooldown;

	void update();

	virtual void shoot() = 0;

public:
	SpaceShip(float _height, float _width, float _acceleration = 1, Vector2 _pos = { 0, 0 }, Vector2 _direction = { 0, 0 },
		float _friction = 0.9f, float _maxSpeed = 7);

	virtual void render();

};

