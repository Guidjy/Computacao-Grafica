#include "LaserManager.h"

LaserManager* LaserManager::instane = NULL;

LaserManager::LaserManager()
{
	lasers = std::list<Laser*>();
}

void LaserManager::spawnLaser(Vector2 direction, Vector2 pos, bool isFriendly)
{
	Laser* l = new Laser(direction, pos, isFriendly);
	addLaser(l);
}

void LaserManager::spawnLaser(Laser laser)
{
	Laser* l = new Laser(laser);
	addLaser(l);
}

void LaserManager::update()
{ 
	for (Laser* l : lasers)
	{
		l->update();
	}
}

void LaserManager::render()
{
	update();

	for (Laser* l : lasers)
	{
		l->render();
	}
}