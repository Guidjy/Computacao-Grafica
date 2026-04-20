#include "Player.h"
#include "Key.h"
#include "gl_canvas2d.h"
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
	Laser l1 = Laser(Vector2(-1, -1), Vector2(pos.x, pos.y - hh));
	Laser l2 = Laser(Vector2(0, -1), Vector2(pos.x, pos.y - hh));
	Laser l3 = Laser(Vector2(1, -1), Vector2(pos.x, pos.y - hh));

	shots.push_back(l1);
	shots.push_back(l2);
	shots.push_back(l3);
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
	Vector2 vertices[3] = {pos + Vector2(0, -hh), pos + Vector2(hw, hh), pos + Vector2(-hw, hh)};
	CV::triangleFill(vertices);
}