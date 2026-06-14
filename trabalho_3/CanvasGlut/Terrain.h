#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <array>
#include <math.h>

class Terrain
{
private:
	std::array<std::array<Vector3, 10>, 10> controlPoints = std::array<std::array<Vector3, 10>, 10>();

	float pitch = 0.0f;  // horizontal rotation
	float yaw = 0.0f;	 // vertical rotation

	const float SENSITIVITY = 0.005f;
	int deltaY;  // control point y-axis variation
	const int MIN_DELTA_Y = 10;
	const int MAX_DELTA_Y = 70;

	// B(t) B-Spline base functions
	float b0(float t) { return 1.0f / 6.0f * pow(1 - t, 3); }
	float b1(float t) { return 1.0f / 6.0f * (3 * pow(t, 3) - 6 * pow(t, 2) + 4); }
	float b2(float t) { return 1.0f / 6.0f * (-3 * pow(t, 3) + 3 * pow(t, 2) + 3 * t + 1); }
	float b3(float t) { return 1.0f / 6.0f * pow(t, 3); }

	void generateTerrain();

	Vector3 applyRotation(Vector3 p);

public:
	bool canRotate = false;

	Terrain(int _deltaY=20);

	// Returns an interpolated point in the B-Spline surface.
	Vector3 calculateSplinePoint(int patchX, int patchZ, float s, float t);

	// Returns a point in the surface given global (x, z) coordinates
	Vector3 getSurfacePoint(float x, float z);

	// increases terrain hill size if true is passed, otherwise decreases
	void changeHillSize(bool grow);

	void update();

	void render();
};



// cada patch  da superfície é gerada por um bloco de 4x4 pontos de controle.