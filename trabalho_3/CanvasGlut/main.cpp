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

#include "gl_canvas2d.h"
#include "GlobalSettings.h"
#include "mouseStates.h"
#include "Camera.h"
#include "Cube.h"
#include "Terrain.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int opcao;

// camera
Camera* cam = Camera::getInstance();
std::vector<Vector3> cube = modelCube(1.0f, 0.0f);
float offset = 0.0f;

// t3
Terrain* terrain = nullptr;

// Called continuously. Objects to be drawn should be controlled by global variables.
// All of the method calls for drawing objects should be done here.
// Should be kept as simple as possible.
void render()
{
	CV::color(0, 0, 0);
	CV::rectFill(0, 0, screenWidth, screenHeight);

	CV::translate(screenWidth / 2, screenHeight / 2);

	offset += 0.01f;
	cube = modelCube(1.0f, offset);
	renderCube(cube);

	terrain->update();

	cam->update();

	// limits frame rate
	Sleep(10);

	oldMouseX = mouseX;
	oldMouseY = mouseY;
}

// called on key press
void keyboard(int key)
{
	auto iterator = std::find(pressedKeys.begin(), pressedKeys.end(), key);
	if (iterator == pressedKeys.end())
	{
		pressedKeys.push_back(key);
	}

	printf("\nTecla: %d" , key);
	if( key < 200 )
	{
		opcao = key;
	}

	switch(key)
	{
		case 27:
			exit(0);
		break;
	}
}

// called on key release
void keyboardUp(int key)
{
	auto iterator = std::find(pressedKeys.begin(), pressedKeys.end(), key);
	if (iterator != pressedKeys.end())
	{
		pressedKeys.remove(key);
	}

	printf("\nLiberou: %d" , key);
}

// called on mouse click, movement or drag
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
	// stores mouse coordinates to be displayed inside render()
	oldMouseX = mouseX;
	oldMouseY = mouseY;
	mouseX = x;
	mouseY = y;
	mouseState = state;

	printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

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
		cam->canLookAround = true;	
		terrain->canRotate = false;
		break;
	}

}

int main(void)
{
	terrain = new Terrain();

	CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
	CV::run();
}
