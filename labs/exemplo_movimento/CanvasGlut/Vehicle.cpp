#include "Vehicle.h"
#include "gl_canvas2d.h"
#include <cmath>  // for converting a vector into an angle


Vehicle::Vehicle(float _height, float _width, float _acceleration, Vector2 _pos, Vector2 _direction, float _friction, float _maxSpeed)
{
	height = _height;
	width = _width;

	pos = _pos;
	direction = _direction;
	currentAngle = 0;

	velocity = Vector2(0, 0);
	acceleration = _acceleration;
	friction = _friction;
	maxSpeed = _maxSpeed;
}

void Vehicle::handleKeyPress(int key)
{
	switch (key)
	{
	case W:
		direction.y = -1;
		break;
	case A:
		direction.x = -1;
		break;
	case S:
		direction.y = 1;
		break;
	case D:
		direction.x = 1;
		break;
	default:
		break;
	}
}

void Vehicle::handleKeyRelease(int key)
{
	switch (key)
	{
	case W:
		direction.y = 0;
		break;
	case A:
		direction.x = 0;
		break;
	case S:
		direction.y = 0;
		break;
	case D:
		direction.x = 0;
		break;
	default:
		break;
	}
}

void Vehicle::rotate()
{
	// rotates vehicle based on the velocity vector if it's moving
	if (abs(velocity.x) > 0.01 || abs(velocity.y) > 0.01)
	{
		currentAngle = atan2(velocity.y, velocity.x);
	}

	// standard 2D rotation matrix for rotating a point around the origin (peep the loop below)
	// > x' = x * cos(theta) - y * sin(theta)
	// > y' = x * sin(theta) + y * cos(theta)

	float cosA = cos(currentAngle);
	float sinA = sin(currentAngle);

	// rect half-height and half-width
	float hh = height / 2;
	float hw = width / 2;

	// defines the 4 corners of the rect at the origin so that the rotation can be applied
	corners[0] = Vector2(-hw, -hh);  // top-left
	corners[1] = Vector2(hw, -hh);   // top-right
	corners[2] = Vector2(hw, hh);	 // bottom-right
	corners[3] = Vector2(-hw, hh);	 // bottom-left

	// rotates the corners around the origin and moves them to their actual position
	for (int i = 0; i < 4; i++)
	{
		float rotatedX = corners[i].x * cosA - corners[i].y * sinA;
		float rotatedY = corners[i].x * sinA + corners[i].y * cosA;

		corners[i] = Vector2(pos.x + rotatedX, pos.y + rotatedY);
	}
}

void Vehicle::update()
{
	// accelerates
	velocity = velocity + direction * acceleration;
	// friction: makes the vehicle gradually slide to a stop if direction is (0, 0)
	velocity = velocity * friction;

	// caps velocity
	if (velocity.x > maxSpeed) velocity.x = maxSpeed;
	if (velocity.x < -maxSpeed) velocity.x = -maxSpeed;
	if (velocity.y > maxSpeed) velocity.y = maxSpeed;
	if (velocity.y < -maxSpeed) velocity.y = -maxSpeed;

	// moves the vehicle
	pos = pos + velocity;

	rotate();
}

void Vehicle::render()
{
	Vector2 p1 = Vector2(pos.x - width / 2, pos.y - height / 2);
	Vector2 p2 = Vector2(pos.x + width / 2, pos.y + height / 2);

	update();
	
	CV::color(0, 0, 0);
	CV::line(corners[0], corners[1]);
	CV::line(corners[2], corners[3]);
	CV::line(corners[3], corners[0]);
	CV::color(1, 0, 0);
	CV::line(corners[1], corners[2]);
}