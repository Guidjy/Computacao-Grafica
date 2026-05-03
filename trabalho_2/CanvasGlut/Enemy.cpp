#include "Enemy.h"
#include "gl_canvas2d.h"
#include "LaserManager.h"

int Enemy::instanceCount = 0;

Enemy::Enemy(float _height, float _width, float _acceleration, Vector2 _pos, Vector2 _direction, float _friction, float _maxSpeed)
	: SpaceShip(_height, _width, _acceleration, _pos, _direction, _friction, _maxSpeed)
{
	color = { 1, 0, 0 };
	isShooting = true;
	shootCooldown = SHOOT_COOLDOWN;
	isDead = false;

	id = instanceCount;
	instanceCount++;
}

void Enemy::shoot()
{
	// shoots in one directions: south
	float hh = height / 2;
	Laser l = Laser(Vector2(0, 1), Vector2(pos.x, pos.y + hh), false);

	LaserManager::getInstance()->spawnLaser(l);

	shootCooldown = SHOOT_COOLDOWN;
}

void Enemy::update(int screenWidth, int screenHeight)
{
	SpaceShip::update(screenWidth, screenHeight);

	// checks collision with lasers
	for (Laser* l : LaserManager::getInstance()->getLasers())
	{
		if (checkCollision(l->pos) && l->isFriendly)
		{
			// sends the id of the recently destroyed enemy to EnemyWave
			currentMessage = std::to_string(id);
			notify();
			break;
		}
	}


}

void Enemy::render(int screenWidth, int screenHeight)
{
	SpaceShip::render(screenWidth, screenHeight);

	float hw = width / 2;
	float hh = height / 2;
	vertices = { pos + Vector2(0, hh), pos + Vector2(hw, -hh), pos + Vector2(-hw, -hh) };
	CV::triangleFill(vertices);
}