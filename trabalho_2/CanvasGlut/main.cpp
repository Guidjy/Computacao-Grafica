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
#include "gameHUD.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyWave.h"
#include "LaserManager.h"
#include "Dificulties.h"

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
Menu* gameHUD = NULL;

// fps control
Frames* frames = NULL;
int currentFPS = 0;

// entities
Player* player = NULL;
EnemyWave* enemyWave = NULL;
LaserManager* laserManager = NULL;

// settings
Dificulties difficulty = HARD;


// Called continuously. Objects to be drawn should be controlled by global variables.
// All of the method calls for drawing objects should be done here.
// Should be kept as simple as possible.
void render()
{
	frames->calculateDeltaTime();

	gameHUD->render(mouseX, mouseY);

	player->render(screenWidth, screenHeight);
	enemyWave->render(screenWidth, screenHeight);
	laserManager->render(screenWidth, screenHeight);

	if (enemyWave->isOver() && enemyWave->canSpawnWave())
	{
		enemyWave->spawnWave(screenWidth);
	}

	if (!player->isAlive())
	{
		std::cout << "GAME OVER!\n";
	}

	frames->render(screenWidth, screenHeight);
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
	srand(time(0));

	frames = Frames::getInstance();
	laserManager = LaserManager::getInstance();

	gameHUDInit(gameHUD, screenHeight, screenWidth);

	player = new Player(60, 60, 500.0f, Vector2(screenWidth / 2, screenHeight - 100), Vector2(0, 0), 0.05f, 1600.0f);
	enemyWave = new EnemyWave(difficulty);

	CV::init(&screenWidth, &screenHeight, "Pimentel's Dogfight");
	CV::run();
}
