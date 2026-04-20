#include "Player.h"
#include "Key.h"
#include "gl_canvas2d.h"
#include "Frames.h"
#include <vector>


Player::Player(float _height, float _width, float _acceleration, Vector2 _pos, Vector2 _direction, float _friction, float _maxSpeed)
	: SpaceShip(_height, _width, _acceleration, _pos, _direction, _friction, _maxSpeed)
{
	color = { 0, 0, 1 };
}

void Player::shoot()
{
	// shoots in three directions: northwest, north and northeast
	float hh = height / 2;
	Laser l1 = Laser(Vector2(-1, -1), Vector2(pos.x, pos.y - hh), true);
	Laser l2 = Laser(Vector2(0, -1), Vector2(pos.x, pos.y - hh), true);
	Laser l3 = Laser(Vector2(1, -1), Vector2(pos.x, pos.y - hh), true);

	shots.push_back(l1);
	shots.push_back(l2);
	shots.push_back(l3);

	cooldown = COOLDOWN;
}

void Player::update()
{
	SpaceShip::update();

	double dt = Frames::getInstance()->getDeltaTime();

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
}

void Player::handleKeyPress(int key)
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
	case SPACE:
		isShooting = true;
		break;
	default:
		break;
	}
}

void Player::handleKeyRelease(int key)
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
	case SPACE:
		isShooting = false;
		break;
	default:
		break;
	}
}

void Player::render()
{
	SpaceShip::render();

	float hw = width / 2;
	float hh = height / 2;
	vertices = {pos + Vector2(0, -hh), pos + Vector2(hw, hh), pos + Vector2(-hw, hh)};
	CV::triangleFill(vertices);
}