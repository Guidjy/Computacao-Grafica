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

#include "gl_canvas2d.h"
#include "mouseStates.h"
#include "Key.h"
#include "Vehicle.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

// screen width and height. Values change on resize
int screenWidth = 1000;
int screenHeight = 1000;

// key presses
int keyPress1;
int keyPress2;
// mouse positions and state
int mouseX;
int mouseY;
int mouseState;

// UI components

// entities
Vehicle* car = NULL;



// Called continuously. Objects to be drawn should be controlled by global variables.
// All of the method calls for drawing objects should be done here.
// Should be kept as simple as possible.
void render()
{
	car->render();


	// limits frame rate
	Sleep(10);
}

// called on key press
void keyboard(int key)
{
	printf("\nTecla: %d" , key);
	if( key < 200 )
	{
		keyPress2 = keyPress1;
		keyPress1 = key;
	}

	switch(key)
	{
		case 27:
			exit(0);
			break;
	}

	car->handleKeyPress(key);
}

// called on key release
void keyboardUp(int key)
{
	printf("\nLiberou: %d" , key);

	car->handleKeyRelease(key);
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
	car = new Vehicle(25, 40, 1, {(float)screenWidth / 2, (float)screenHeight / 2});

	CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
	CV::run();
}
