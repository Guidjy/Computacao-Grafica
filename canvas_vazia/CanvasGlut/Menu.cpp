#include "Menu.h"
#include <vector>


Menu::Menu()
{
	components = std::vector<Shape*>();
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
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->render(mouseX, mouseY);
	}
}