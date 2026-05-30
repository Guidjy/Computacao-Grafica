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
#include <iostream>

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
float radius = 200;
Vector2 origin = Vector2(screenWidth / 2, screenHeight / 2);
Vector2 xAxis = Vector2(1, 0);
Vector2 mouseVector = Vector2(mouseX, mouseY);



// Called continuously. Objects to be drawn should be controlled by global variables.
// All of the method calls for drawing objects should be done here.
// Should be kept as simple as possible.
void render()
{
	CV::translate(origin);
	CV::color(0, 0, 0);

	// mouse
	mouseVector.x = mouseX - origin.x;
	mouseVector.y = mouseY - origin.y;
	mouseVector = mouseVector.normalize() * radius;
	CV::line(Vector2(0, 0), mouseVector);

	// x axis
	CV::line(0, 0, radius, 0);

	// dot product
	float dotProduct = mouseVector.dotProduct(xAxis);
	CV::color(0, 0, 0);
	CV::text(20, 20, std::to_string(dotProduct).c_str());
	// std::cout << dotProduct << "\n";

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
		break;

	case RELEASE:
		break;
	}

}

int main(void)
{

	CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
	CV::run();
}
