#pragma once
#include "SpaceShip.h"
#include "Vector2.h"

class Player : SpaceShip
{
private:
	void shoot() override;

public:
	Player(float _height, float _width, float _acceleration = 1, Vector2 _pos = { 0, 0 }, Vector2 _direction = { 0, 0 },
		float _friction = 0.9f, float _maxSpeed = 7);

	void handleKeyPress(int key);

	void handleKeyRelease(int key);

	void render() override;
};

