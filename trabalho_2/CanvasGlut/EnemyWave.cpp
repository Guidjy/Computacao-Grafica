#include "EnemyWave.h"
#include <stdlib.h>
#include <string>


EnemyWave::EnemyWave(Dificulties _dificulty)
{
	dificulty = _dificulty;
	enemies = std::list<Enemy*>();
	enemyCount = 0;
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

	for (int i = 0; i < enemyCount; i++)
	{
		float xPos = rand() % (screenWidth - 40) + 20;
		Enemy* enemy = new Enemy(40, 40, 2000.0f, Vector2(xPos, 100), Vector2(0, 0), 0.05f, 1600.0f);
		enemy->attach(this);

		enemies.push_back(enemy);
	}
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

	removeDeadEnemies();
}