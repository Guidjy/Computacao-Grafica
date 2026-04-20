#pragma once
#include <ctime>


class Frames
{
private:
	int targetFPS;

	double targetFrameDuration; // measured in seconds

	clock_t currentFrameTime;

	clock_t lastFrameTime;

	double deltaTime;

	int frameCount;

	double timeAccumulator; // adds up deltaTime until it reaches 1 second 

	int currentFPS;

	void calculateDeltaTime();

	void calculateCurrentFPS();

public:
	bool shouldDisplayCurrentFPS;

	Frames(int _targetFPS=60, bool _shouldDisplayCurrentFPS=true);

	void update();

	double getDeltaTime() { return deltaTime; }

	int getCurrentFPS() { return currentFPS; }

	void displayCurrentFPS(int screenWidth, int screenHeight);
};

