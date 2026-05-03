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

void LaserManager::removeOutOfBoundsLasers()
{
	for (auto it = lasers.begin(); it != lasers.end(); )
	{
		if ((*it)->getShouldBeDeleted())
		{
			Laser* l = *it;
			// removes from list and increment iterator
			it = lasers.erase(it);
			// safely deletes laser afterwards
			delete l;
		}
		else
		{
			it++;
		}
	}
}

void LaserManager::update(int screenWidth, int screenHeight)
{ 
	for (Laser* l : lasers)
	{
		l->update(screenWidth, screenHeight);
	}
}

void LaserManager::render(int screenWidth, int screenHeight)
{
	update(screenWidth, screenHeight);

	for (Laser* l : lasers)
	{
		l->render();
	}

	removeOutOfBoundsLasers();
}