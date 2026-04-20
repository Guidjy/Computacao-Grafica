#include "Menu.h"
#include "gl_canvas2d.h"
#include <vector>


Menu::Menu(float _height, float _width, std::array<float, 3> _backgroundColor)
{
	components = std::vector<Shape*>();
	height = _height;
	width = _width;
	backgroundColor = _backgroundColor;
}

void Menu::addComponent(Shape* component) 
{ 
	components.push_back(component); 
}

void Menu::onClick(int mouseX, int mouseY, int mouseState)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (components[i]->checkClick(mouseX, mouseY, mouseState))
		{
			components[i]->onClick();
		}
	}
}

void Menu::onRelease()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->onRelease();
	}
}

void Menu::render(int mouseX, int mouseY)
{
	CV::color(backgroundColor[0], backgroundColor[1], backgroundColor[2]);
	CV::rectFill(0, 0, width, height);

	for (int i = 0; i < components.size(); i++)
	{
		components[i]->render(mouseX, mouseY);
	}
}