/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         08/2025
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.1
//
//  Instruções:
//	  Para alterar a animacao, digite numeros entre 1 e 3
//    Programa cheio de numeros magicos. Nao use isso nunca.
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> // mouse wheel callback

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>

#include "GlobalSettings.h"
#include "mouseStates.h"
#include "Camera.h"
#include "Terrain.h"
#include "Vehicle.h"
#include "Frames.h"
#include "Keys.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int opcao;

// camera
Camera* cam = Camera::getInstance();

// fps control
Frames* frames = nullptr;

// t3
Terrain* terrain = nullptr;
Vehicle* car = nullptr;

// Called continuously. Objects to be drawn should be controlled by global variables.
// All of the method calls for drawing objects should be done here.
// Should be kept as simple as possible.
void display()
{
	frames->calculateDeltaTime();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cam->update();

	// renderHUD();

	glutSolidTeapot(1.2);

	glPushMatrix();
		glRotatef(scenePitch * radToDeg, 1.0f, 0.0f, 0.0f);
		glRotatef(sceneYaw * radToDeg, 0.0f, 1.0f, 0.0f);

		terrain->update();
		car->update();
	glPopMatrix();

	updateMousePosition();

	glutSwapBuffers();

	frames->render();
}

// called on key press
void keyboard(unsigned char key, int, int)
{
	int k = (int)key;

	auto iterator = std::find(pressedKeys.begin(), pressedKeys.end(), k);
	if (iterator == pressedKeys.end())
	{
		pressedKeys.push_back(k);
	}

	printf("\nTecla: %d", k);
	if (k < 200)
	{
		opcao = k;
	}

	switch (k)
	{
	case 27:
		exit(0);
	case C:
		terrain->shouldCull = !terrain->shouldCull;
		if (terrain->shouldCull)
		{
			glEnable(GL_CULL_FACE);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
		break;
	case V:
		terrain->isSmooth = !terrain->isSmooth;
		break;
	case Z:
		terrain->changeHillSize(true);
		break;
	case X:
		terrain->changeHillSize(false);
		break;
		break;
	}
}

// called on key release
void keyboardUp(unsigned char key, int, int)
{
	int k = (int)key;

	auto iterator = std::find(pressedKeys.begin(), pressedKeys.end(), k);
	if (iterator != pressedKeys.end())
	{
		pressedKeys.remove(k);
	}

	printf("\nLiberou: %d", k);
}

// called on mouse click, movement or drag
void mouse(int button, int state, int x, int y)
{
	// stores mouse coordinates to be displayed inside render()
	oldMouseX = mouseX;
	oldMouseY = mouseY;
	mouseX = x;
	mouseY = y;
	mouseState = state;

	oldMouseState = mouseState;
	switch (state)
	{
	case CLICK:
		mouseState = CLICK;
		cam->canLookAround = false;
		terrain->canRotate = true;
		break;
	case HOVER:
		mouseState = HOVER;
		break;
	case RELEASE:
		mouseState = HOVER;
		cam->canLookAround = false;
		terrain->canRotate = false;
		break;
	}
}

void mouseDrag(int x, int y)
{
	if (mouseState == CLICK)
	{
		int deltaX = x - oldMouseX;
		int deltaY = y - oldMouseY;

		sceneYaw += deltaX * ROTATION_SENSITIVITY;
		scenePitch += deltaY * ROTATION_SENSITIVITY;
	}

	oldMouseX = mouseX;
	oldMouseY = mouseY;
	mouseX = x;
	mouseY = y;
}

void reshape(int w, int h)
{
	// updates viewport size
    screenHeight = h;
    screenWidth = w;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
    
	// updates aspect ration
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 1000.0); 

    // goes back to editing the modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	// specifies number of buffers being used and their params
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowPosition(50, 50);

	glutInitWindowSize(screenWidth, screenHeight);

	glutCreateWindow("Trabalho Prático - Computação Gráfica UFSM");

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// callbacks
	glutDisplayFunc(display);       
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);  
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseDrag);
	glutReshapeFunc(reshape);

	// backface culling
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glFrontFace(faceMode);
	glCullFace(cullingMode);
	// glEnable(GL_CULL_FACE);

	// enables lighting
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);

	// creates light source
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	// game
	srand(time(0));

	frames = Frames::getInstance();
	terrain = new Terrain();
	car = new Vehicle(terrain);

	glutMainLoop();

	return 0;
}
