#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Terrain.h"
#include <array>
#include <GL/glut.h>


class Vehicle
{
private:
	const float width = 3;
	const float lenght = 5;
	float currentHorizontalAngle; 
	float transformMatrix[16];  // Stores position and rotation for OpenGL transformations

	Vector3 pos;
	Vector2 velocity;
	Vector2 direction;  // direction in the (x, z) plane

	const float acceleration = 750.0f;
	const float friction = 0.9f;
	const float MAX_VELOCITY = 10.0f;

	GLfloat matDiffuse[4] = { 0.2f, 0.4f, 0.8f, 1.0f };
	GLfloat matSpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat matShininess[4] = { 10.0f };

	Terrain* terrainReference;

	void handleKeyboardInput();

	void rotate();  // rotates the vehicle based on its velocity vector

	void move();

public:
	Vehicle(Terrain* _terrainReference);

	void update();

	void render();
};

