#pragma once
#include "SpaceShip.h"
#include "Vector2.h"

#define SHOOT_COOLDOWN 15;
#define HITABLE_COOLDOWN 120;

class Player : public SpaceShip
{
private:
	int hp;

	bool isHitable;

	int hitableCooldown;

	void shoot() override;

	void keepInBounds();

	void update(int screenWidth, int screenHeight) override;

public:
	Player(float _height, float _width, float _acceleration = 1, Vector2 _pos = { 0, 0 }, Vector2 _direction = { 0, 0 },
		float _friction = 0.9f, float _maxSpeed = 7);

	int getHp() { return hp; }

	bool isAlive() { return hp > 0; }

	void handleKeyPress(int key);

	void handleKeyRelease(int key);

	void onHit();

	void render(int screenWidth, int screenHeight) override;
};

