/*
Quesitos Obrigatórios implementados:
- Botões:
	1) desenhar retângulo
	2) Inserir imagem
	3) rotacionar imagem
- Checkbox:
	1) Deixar imagem em tons de cinza
- Slider:
	1) Aumentar tamanho da imagem
- Componentes:
	1) Retângulos: possível desenhar e mover com o mouse
	2) Imagem: possível carregar e mover com o mouse

Bônus:
1) Tons de cinza
2) rotação em 90 graus
3) redimensionamento
4) sistema de gerenciamento de GUI (Menu.h, mainMenu.cpp)
	- O sistema de gerenciamento de GUI conciste em uma calsse Menu que contém uma lista de componentes (retângulos, círculos, 
	  sliders, imagens...), a qual ele usa para gerenciar os componentes. Atravez dessa classe, é possível renderizar e gerenciar
	  eventos de click e teclado de todos os componentes com apenas uma chamada de função (ver main(), mouse() e render())
*/



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

int option;
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
		option = key;
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
}

// called on mouse click, movement or drag
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
	// stores mouse coordinates to be displayed inside render()
	mouseX = x;
	mouseY = y;
	mouseState = state;

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
	CV::init(&screenWidth, &screenHeight, "Pimentel's Paint");

	mainMenuInit(mainMenu, screenHeight, screenWidth);

	CV::run();
}
