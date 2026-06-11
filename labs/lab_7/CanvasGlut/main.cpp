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
#include <format>
#include <string>

#include "gl_canvas2d.h"
#include "lab.h"
#include "mouseStates.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

// screen width and height. Values change on resize
int screenWidth = 500;
int screenHeight = 500;

int opcao;
// mouse positions and state
int mouseX;
int mouseY;
int mouseState;

// lab
Camera* cam = new Camera();
std::vector<Vector3> cube = model_cube(1.0f, 0.0f);
float offset = 0.0f;

// Called continuously. Objects to be drawn should be controlled by global variables.
// All of the method calls for drawing objects should be done here.
// Should be kept as simple as possible.
void render()
{
	CV::color(0, 0, 0);
	CV::rectFill(0, 0, screenWidth, screenHeight);

	CV::translate(screenWidth / 2, screenHeight / 2);
	
	offset += 0.01f;
	cube = model_cube(1.0f, offset);
	render_cube(cube);

	// limits frame rate
	Sleep(10);
}

// called on key press
void keyboard(int key)
{
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
	printf("\nLiberou: %d" , key);

	switch (key)
	{
	case 119:  // w
		cam->eye.z += 1.0f;
		break;
	case 97:
		cam->eye.x -= 1.0f;
		break;
	case 115:
		cam->eye.z -= 1.0f;
		break;
	case 100:
		cam->eye.z += 1.0f;
		break;
	}
}

// called on mouse click, movement or drag
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
	// stores mouse coordinates to be displayed inside render()
	mouseX = x;
	mouseY = y;
	mouseState = state;

	//printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

	switch (state)
	{
	case CLICK:
		break;

	case RELEASE:
		break;
	}

}

int main(void)
{
	cam->eye = Vector3(0, -2, -3);
	cam->target = Vector3(0, 0, 0);
	cam->up = Vector3(0, 1, 0);
	cam->d = 100.0f;

	CV::init(&screenWidth, &screenHeight, "Visualizaçõ 3d");
	CV::run();
}
