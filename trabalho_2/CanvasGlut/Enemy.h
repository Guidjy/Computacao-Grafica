#pragma once
#include "SpaceShip.h"
#include "ISubject.h"
#include <list>
#include <string>

#define SHOOT_COOLDOWN 75;

class Enemy : public SpaceShip, public ISubject
{
private:
	static int instanceCount;

	int id;

	float initialX;

	bool isSpecial;

	float t;

	void shoot() override;

	void update(int screenWidth, int screenHeight) override;

	std::list<IObserver*> observers;

	std::string currentMessage;

public:
	bool isDead;

	Enemy(float _height, float _width, float _acceleration = 1, Vector2 _pos = { 0, 0 }, Vector2 _direction = { 0, 0 },
		float _friction = 0.9f, float _maxSpeed = 5);

	int getId() { return id; }

	void render(int screenWidth, int screenHeight) override;

	void attach(IObserver* observer) override { observers.push_back(observer); }

	void detach(IObserver* observer) override { observers.remove(observer); }

	void notify() override { for (IObserver* observer : observers) observer->listen(currentMessage); }
};

