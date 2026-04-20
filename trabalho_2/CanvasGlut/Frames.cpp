#include "Frames.h"
#include "gl_canvas2d.h"
#include <windows.h>
#include <string>

Frames* Frames::instance = NULL;

Frames::Frames(int _targetFPS, bool _shouldDisplayCurrentFPS)
{
	targetFPS = _targetFPS;
	targetFrameDuration = 1.0f / targetFPS;

	currentFrameTime = clock();
	lastFrameTime = currentFrameTime;
	deltaTime = 0.0f;

	frameCount = 0;
	timeAccumulator = 0.0;
	currentFPS = 0;
	shouldDisplayCurrentFPS = _shouldDisplayCurrentFPS;
}

void Frames::calculateDeltaTime()
{
	currentFrameTime = clock();
	deltaTime = (double)(currentFrameTime - lastFrameTime) / CLOCKS_PER_SEC;
	lastFrameTime = currentFrameTime;
}

void Frames::calculateCurrentFPS()
{
	frameCount++;
	timeAccumulator += deltaTime;

	if (timeAccumulator >= 1.0)
	{
		currentFPS = frameCount;
		frameCount = 0;
		timeAccumulator -= 1.0;
	}
}

void Frames::render(int screenWidth, int screenHeight)
{
	calculateCurrentFPS();

	if (shouldDisplayCurrentFPS)
	{
		displayCurrentFPS(screenWidth, screenHeight);
	}

	clock_t endRenderTime = clock();
	double timeTakenToRender = (double)(endRenderTime - currentFrameTime) / CLOCKS_PER_SEC;

	double timeToSleep = targetFrameDuration - timeTakenToRender;
	if (timeToSleep > 0.0f)
	{
		Sleep(timeToSleep * 1000.0f);
	}
}

void Frames::displayCurrentFPS(int screenWidth, int screenHeight)
{
	CV::color(1, 1, 1);
	std::string FPS = "FPS: " + std::to_string(currentFPS);
	CV::text(Vector2(screenWidth - 75, 20), FPS.c_str());
}