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
#include "Frames.h"
#include "mouseStates.h"
#include "buttonEvents.h"
#include "Menu.h"
#include "mainMenu.h"
#include "Player.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

// screen width and height. Values change on resize
int screenWidth = 500;
int screenHeight = 700;

int opcao;
// mouse positions and state
int mouseX;
int mouseY;
int mouseState;

// menus
Menu* mainMenu = NULL;

// fps control
Frames* frames = NULL;
int currentFPS = 0;

// entities
Player* player = NULL;


// Called continuously. Objects to be drawn should be controlled by global variables.
// All of the method calls for drawing objects should be done here.
// Should be kept as simple as possible.
void render()
{
	frames->calculateDeltaTime();

	mainMenu->render(mouseX, mouseY);

	player->render();

	frames->update();
	if (frames->shouldDisplayCurrentFPS)
	{
		frames->displayCurrentFPS(screenWidth, screenHeight);
	}
}

// called on key press
void keyboard(int key)
{
	//printf("\nTecla: %d", key);
	player->handleKeyPress(key);
}

// called on key release
void keyboardUp(int key)
{
	player->handleKeyRelease(key);
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
	frames = new Frames();

	mainMenuInit(mainMenu, screenHeight, screenWidth);

	player = new Player(60, 60, 2000.0f, Vector2(100, 100), Vector2(0, 0), 0.05f, 1600.0f);

	CV::init(&screenWidth, &screenHeight, "Pimentel's Dogfight");
	CV::run();
}
