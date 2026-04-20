#include "SpaceShip.h"
#include "gl_canvas2d.h"
#include "Frames.h"
#include <cmath>  // for converting a vector into an angle


SpaceShip::SpaceShip(float _height, float _width, float _acceleration, Vector2 _pos, Vector2 _direction, float _friction, float _maxSpeed)
{
	height = _height;
	width = _width;

	pos = _pos;
	direction = _direction;

	velocity = Vector2(0, 0);
	acceleration = _acceleration;
	friction = _friction;
	maxSpeed = _maxSpeed;
}

void SpaceShip::update()
{
	double dt = Frames::getDeltaTime();

	// accelerates
	velocity = velocity + direction * acceleration * dt;
	// friction: makes the object gradually slide to a stop if direction is (0, 0)
	velocity = velocity * friction * dt;

	// caps velocity
	if (velocity.x > maxSpeed) velocity.x = maxSpeed;
	if (velocity.x < -maxSpeed) velocity.x = -maxSpeed;
	if (velocity.y > maxSpeed) velocity.y = maxSpeed;
	if (velocity.y < -maxSpeed) velocity.y = -maxSpeed;

	// moves the object
	pos = pos + velocity * dt;
}

void SpaceShip::render()
{
	update();

	CV::color(color[0], color[1], color[2]);
}