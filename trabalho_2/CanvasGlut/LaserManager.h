#pragma once
#include <list>
#include "Vector2.h"
#include "Laser.h"

class LaserManager
{
private:
	static LaserManager* instane;

	LaserManager();

	std::list<Laser*> lasers;

public:
	static LaserManager* getInstance()
	{
		if (instane == NULL) instane = new LaserManager();
		return instane;
	}

	std::list<Laser*> getLasers() { return lasers; }

	void spawnLaser(Vector2 direction, Vector2 pos, bool isFriendly);

	void spawnLaser(Laser laser);

	void addLaser(Laser* laser) { lasers.push_back(laser); }

	void removeLaser(Laser* laser) { lasers.remove(laser); }

	void update();

	void render();
};

