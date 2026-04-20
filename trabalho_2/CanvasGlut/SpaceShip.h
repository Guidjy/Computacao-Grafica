#pragma once
#include "Laser.h"
#include "Vector2.h"
#include "Key.h"
#include <vector>
#include <array>


class SpaceShip
{
protected:
	Vector2 pos;  // center of the spaceship
	std::array<Vector2, 3> vertices;

	Vector2 direction;
	Vector2 velocity;

	float acceleration;
	float friction;  // how fast the spaceship slows down
	float maxSpeed;

	float width;
	float height;
	std::array<float, 3> color;

	bool isShooting;
	int cooldown;

	virtual void update();

	virtual void shoot() = 0;

public:
	SpaceShip(float _height, float _width, float _acceleration = 1, Vector2 _pos = { 0, 0 }, Vector2 _direction = { 0, 0 },
		float _friction = 0.9f, float _maxSpeed = 7);

	std::vector<Laser> shots;

	// checks if a point is inside of the spaceship
	bool checkCollision(Vector2 p);

	virtual void render();

};

