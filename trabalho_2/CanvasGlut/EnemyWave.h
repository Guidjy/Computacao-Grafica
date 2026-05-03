#pragma once
#include "Enemy.h"
#include "Dificulties.h"
#include <list>


class EnemyWave : public IObserver
{
private:
	Dificulties dificulty;

	int spawnCooldown;

	int enemyCount;

public:
	std::list<Enemy*> enemies;

	EnemyWave(Dificulties _dificulty);

	void removeDeadEnemies();

	void spawnWave(int screenWidth);

	bool canSpawnWave() { return spawnCooldown <= 0; }

	bool isOver() { return enemyCount <= 0; }

	void render(int screenWidth, int screenHeight);

	void listen(std::string message) override;
};

