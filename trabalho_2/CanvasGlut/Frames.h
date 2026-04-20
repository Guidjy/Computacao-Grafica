#pragma once
#include <ctime>


class Frames
{
private:
	static Frames* instance;

	int targetFPS;

	double targetFrameDuration; // measured in seconds

	clock_t currentFrameTime;

	clock_t lastFrameTime;

	double deltaTime;

	int frameCount;

	double timeAccumulator; // adds up deltaTime until it reaches 1 second 

	int currentFPS;

	void calculateCurrentFPS();

	Frames(int _targetFPS = 60, bool _shouldDisplayCurrentFPS = true);

public:
	static Frames* getInstance()
	{
		if (instance == NULL) instance = new Frames();
		return instance;
	}

	bool shouldDisplayCurrentFPS;

	void calculateDeltaTime();

	void render(int screenWidth, int screenHeight);

	double getDeltaTime() { return deltaTime; }

	int getCurrentFPS() { return currentFPS; }

	void displayCurrentFPS(int screenWidth, int screenHeight);
};