#pragma once
#include "SpaceShip.h"

#define COOLDOWN 75;

class Enemy : public SpaceShip
{
private:
	void shoot() override;

	void update() override;

public:
	Enemy(float _height, float _width, float _acceleration = 1, Vector2 _pos = { 0, 0 }, Vector2 _direction = { 0, 0 },
		float _friction = 0.9f, float _maxSpeed = 7);

	void render() override;
};

