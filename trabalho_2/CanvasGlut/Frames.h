#pragma once
#include <ctime>


class Frames
{
private:
	int targetFPS;

	double targetFrameDuration; // measured in seconds

	clock_t currentFrameTime;

	clock_t lastFrameTime;

	static double deltaTime;

	int frameCount;

	double timeAccumulator; // adds up deltaTime until it reaches 1 second 

	int currentFPS;

	void calculateCurrentFPS();

public:
	bool shouldDisplayCurrentFPS;

	Frames(int _targetFPS=60, bool _shouldDisplayCurrentFPS=true);

	void calculateDeltaTime();

	void update();

	static double getDeltaTime() { return deltaTime; }

	int getCurrentFPS() { return currentFPS; }

	void displayCurrentFPS(int screenWidth, int screenHeight);
};