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
#include "Menu.h"
#include "mainMenu.h"
#include "mouseStates.h"
#include "buttonEvents.h"
#include "Bmp.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

// screen width and height. Values change on resize
int screenWidth = 1280;
int screenHeight = 720;

int opcao;
// mouse positions and state
int mouseX;
int mouseY;
int mouseState;

// Menus
Menu* mainMenu = NULL;

// Called continuously. Objects to be drawn should be controlled by global variables.
// All of the method calls for drawing objects should be done here.
// Should be kept as simple as possible.
void render()
{
	mainMenu->render(mouseX, mouseY);

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
		mainMenu->onClick(mouseX, mouseY, mouseState);
		break;

	case RELEASE:
		mainMenu->onRelease();
		break;
	}

}

int main(void)
{
	CV::init(&screenWidth, &screenHeight, "Pimentel Paint");

	mainMenuInit(mainMenu, screenHeight, screenWidth);

	CV::run();
}
