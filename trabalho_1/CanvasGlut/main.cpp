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
#include "Button.h"
#include "Rect.h"
#include "Circle.h"
#include "Slider.h"
#include "mouseStates.h"
#include "buttonEvents.h"
#include "Bmp.h"
#include "CheckBox.h"
#include "Menu.h"
#include "Shape.h"

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

// UI components
Rect* rect1 = NULL;
Circle* circle1 = NULL;
Button* btn1 = NULL;
Bmp* img1 = NULL;
Slider* slider1 = NULL;
CheckBox* checkBox1 = NULL;

Menu* menu1 = NULL;



// Called continuously. Objects to be drawn should be controlled by global variables.
// All of the method calls for drawing objects should be done here.
// Should be kept as simple as possible.
void render()
{
	menu1->render(mouseX, mouseY);

	CV::translate(0, 200);
	img1->render();

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
		menu1->onClick(mouseX, mouseY, mouseState);
		break;

	case RELEASE:
		menu1->onRelease();
		break;
	}

}

int main(void)
{
	rect1 = new Rect(Vector2(20, 20), 50, 200, { 0.5, 0, 0.5 });
	circle1 = new Circle(Vector2(400, 40), 20, 20, { 0.8, 0.1, 0.3 }, true);
	btn1 = new Button(Vector2(20, 150), 40, 120, "click me", { 0.8, 0.8, 0.8 }, true);
	btn1->setOnClickCallback(defaultEvent);
	checkBox1 = new CheckBox(Vector2(200, 150), 30, { 0.8, 0, 0.2 }, true);
	//checkBox1->setOnClickCallback(defaultEvent);
	slider1 = new Slider(Vector2(20, 100), 30, 150, { 0.0, 0.2, 0.8 });

	menu1 = new Menu();
	menu1->addComponent(rect1);
	menu1->addComponent(circle1);
	menu1->addComponent(btn1);
	menu1->addComponent(checkBox1);
	menu1->addComponent(slider1);

	//img1 = new Bmp(".\\images\\img1_256x256.bmp");
	//img1 = new Bmp(".\\images\\img2_200x200.bmp");
	//img1 = new Bmp(".\\images\\img3_256 cores.bmp");
	img1 = new Bmp(".\\images\\img4.bmp");
	//img1->convertBGRtoRGB();

	CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
	CV::run();
}
