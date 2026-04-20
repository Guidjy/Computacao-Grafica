#include "SpaceShip.h"
#include "gl_canvas2d.h"
#include "Frames.h"
#include <cmath>  // for converting a vector into an angle


SpaceShip::SpaceShip(float _height, float _width, float _acceleration, Vector2 _pos, Vector2 _direction, float _friction, float _maxSpeed)
{
	height = _height;
	width = _width;
	color = {0, 0, 0};

	pos = _pos;
	direction = _direction;

	velocity = Vector2(0, 0);
	acceleration = _acceleration;
	friction = _friction;
	maxSpeed = _maxSpeed;

	isShooting = false;	
	cooldown = 0;
}

void SpaceShip::update()
{
	double dt = Frames::getDeltaTime();

	// accelerates
	velocity = velocity + direction * acceleration * dt;
	// friction makes the spaceship gradually slide to a stop if direction is (0, 0)
	velocity = velocity * pow(friction, dt);

	// caps velocity
	if (velocity.x > maxSpeed) velocity.x = maxSpeed;
	if (velocity.x < -maxSpeed) velocity.x = -maxSpeed;
	if (velocity.y > maxSpeed) velocity.y = maxSpeed;
	if (velocity.y < -maxSpeed) velocity.y = -maxSpeed;

	// moves the spaceship
	pos = pos + velocity * dt;

	// updates shots
	for (int i = 0; i < shots.size(); i++) shots[i].update();

	// shoots
	if (cooldown > 0) cooldown--;
	if (isShooting && cooldown <= 0)
	{
		shoot();
		cooldown = COOLDOWN;
	}
}

void SpaceShip::render()
{
	update();

	for (int i = 0; i < shots.size(); i++)
	{
		shots[i].render();
	}

	CV::color(color[0], color[1], color[2]);
}