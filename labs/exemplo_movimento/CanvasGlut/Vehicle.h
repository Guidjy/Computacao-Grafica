#pragma once
#include "Vector2.h"
#include "Key.h"


class Vehicle
{
private:
	Vector2 pos;  // center of the vehicle
	Vector2 direction;
	Vector2 velocity;

	float acceleration;
	float friction;  // how fast the vehicle slows down
	float maxSpeed;

	float height;
	float width;
	float currentAngle;
	// 0 = top-left, 1 = top-right, 2 = bottom-right, 3 = bottom-left
	Vector2 corners[4];

	void rotate();

	void update();

public:
	Vehicle(float _height, float _width, float _acceleration = 1, Vector2 _pos = { 0, 0 }, Vector2 _direction = { 0, 0 },
		float _friction = 0.9f, float _maxSpeed = 7);

	void handleKeyPress(int key);

	void handleKeyRelease(int key);

	void render();

};

