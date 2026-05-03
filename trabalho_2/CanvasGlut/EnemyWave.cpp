#include "EnemyWave.h"
#include <stdlib.h>
#include <string>

#define ENEMY_HEIGHT 40;
#define ENEMY_WIDTH 40;
#define SPAWN_COOLDOWN 240;

EnemyWave::EnemyWave(Dificulties _dificulty)
{
	dificulty = _dificulty;
	enemies = std::list<Enemy*>();
	enemyCount = 0;
	spawnCooldown = SPAWN_COOLDOWN;
}

// the message consits of a single number which represents the id of an enemy yhat has died
void EnemyWave::listen(std::string message)
{
	int deadEnemyyId = std::stoi(message);
	
	for (Enemy* enemy : enemies)
	{
		if (enemy->getId() == deadEnemyyId)
		{
			enemy->isDead = true;
			break;
		}
	}
}

void EnemyWave::spawnWave(int screenWidth)
{
	enemyCount = 5;

	switch (dificulty)
	{
	case EASY:
		enemyCount += rand() % 5;
		break;
	case HARD:
		enemyCount += rand() % 10;
		break;
	default:
		break;
	}

	int ew = ENEMY_WIDTH;
	int eh = ENEMY_HEIGHT;
	for (int i = 0; i < enemyCount; i++)
	{
		float xPos = rand() % (screenWidth - ew) + ew/2;
		float yPos = eh * i - eh * enemyCount;
		Enemy* enemy = new Enemy(ew, eh, 10.0f, Vector2(xPos, yPos), Vector2(0, 1), 0.05f, 1600.0f);
		enemy->attach(this);

		enemies.push_back(enemy);
	}

	spawnCooldown = SPAWN_COOLDOWN;
}

void EnemyWave::removeDeadEnemies()
{
	for (auto it = enemies.begin(); it != enemies.end(); )
	{
		if ((*it)->isDead)
		{
			Enemy* deadEnemy = *it;
			// removes from list and increment iterator
			it = enemies.erase(it);
			// safely deletes enemy afterwards
			delete deadEnemy;

			enemyCount--;
		}
		else
		{
			it++;
		}
	}
}

void EnemyWave::render(int screenWidth, int screenHeight)
{
	for (Enemy* enemy : enemies)
	{
		enemy->render(screenWidth, screenHeight);
	}

	if (spawnCooldown > 0 && isOver())
	{
		spawnCooldown--;
	}

	removeDeadEnemies();
}