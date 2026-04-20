#include "Enemy.h"
#include "gl_canvas2d.h"

Enemy::Enemy(float _height, float _width, float _acceleration, Vector2 _pos, Vector2 _direction, float _friction, float _maxSpeed)
	: SpaceShip(_height, _width, _acceleration, _pos, _direction, _friction, _maxSpeed)
{
	color = { 1, 0, 0 };
	isShooting = true;
	cooldown = COOLDOWN;
}

void Enemy::shoot()
{
	// shoots in one directions: south
	float hh = height / 2;
	Laser l = Laser(Vector2(0, 1), Vector2(pos.x, pos.y + hh), false);

	shots.push_back(l);

	cooldown = COOLDOWN;
}

void Enemy::update()
{
	SpaceShip::update();
}

void Enemy::render()
{
	SpaceShip::render();

	float hw = width / 2;
	float hh = height / 2;
	vertices = { pos + Vector2(0, hh), pos + Vector2(hw, -hh), pos + Vector2(-hw, -hh) };
	CV::triangleFill(vertices);
}