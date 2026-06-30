#pragma once
#include <list>
#include <GL/glut.h>
#include "Vector3.h"

// screen settings
extern int screenWidth;
extern int screenHeight;

// mouse state
extern int mouseX;
extern int mouseY;
extern int oldMouseX;
extern int oldMouseY;
extern int mouseState;
extern int oldMouseState;

// keyboard state
extern std::list<int> pressedKeys;

// terrain settings
extern const int TERRAIN_WIDTH;

// lighting
extern GLfloat lightPosition[4];
extern GLfloat lightDifuse[4];
extern GLfloat lightSpecular[4];

extern int polygonMode;
extern int cullingMode;
extern int faceMode;

extern float radToDeg;

// world transformations
extern float scenePitch;  // horizontal rotation
extern float sceneYaw;	  // vertical rotation
extern const float ROTATION_SENSITIVITY;

// car variables
extern Vector3 carPosition;
extern Vector3 carForward;

void updateMousePosition();

Vector3 normalVector(Vector3 p0, Vector3 p1, Vector3 p2);