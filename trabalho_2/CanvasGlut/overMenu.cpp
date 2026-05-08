#include "overMenu.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

SpaceBackground* overBackground = nullptr;
Rect* leaderBoard = nullptr;
Text* title;
Text* first;
Text* second;
Text* third;

void overMenuInit(Menu*& self, int height, int width)
{
	self = new Menu(height, width, { 0, 0, 0 });

	// background
	overBackground = new SpaceBackground(height, width);
	// leaderboard
	float lw = 250;
	leaderBoard = new Rect(Vector2(125, 100), 500, lw, { 1, 1, 0 }, true);
	// scores
	title = new Text(Vector2(150, 120), "Highscore: ");
	first = new Text(Vector2(150, 150), "1) ");
	second = new Text(Vector2(150, 180), "2) ");
	third = new Text(Vector2(150, 210), "3) ");

	self->addComponent(overBackground);
	self->addComponent(leaderBoard);
	self->addComponent(title);
	self->addComponent(first);
	self->addComponent(second);
	self->addComponent(third);
}

void getLeaderboard(int score)
{
    std::string filename = "leaderboard.txt";
    std::vector<int> top3;
    bool fileExisted = false;

    // reads 3 integers from the leaderboard file
    std::ifstream inFile(filename);
    if (inFile.is_open())
    {
        fileExisted = true;
        int currentScore;
        while (inFile >> currentScore)
        {
            top3.push_back(currentScore);
        }
        inFile.close();
    }

    // pads to 3 zeros if the file was empty or missing
    while (top3.size() < 3) top3.push_back(0);
    if (top3.size() > 3) top3.resize(3);

    std::vector<int> originalScores = top3;

    // adds new score, sort descending, and keep top 3
    top3.push_back(score);
    std::sort(top3.begin(), top3.end(), std::greater<int>());
    top3.resize(3);

    // writes back to file (one score per line) if changes occurred
    if (!fileExisted || top3 != originalScores)
    {
        std::ofstream outFile(filename);
        if (outFile.is_open())
        {
            outFile << top3[0] << "\n" << top3[1] << "\n" << top3[2] << "\n";
            outFile.close();
            std::cout << "Leaderboard updated: "
                << top3[0] << ", " << top3[1] << ", " << top3[2] << "\n";
        }
    }

    // updates GUI
    title->setText(title->getText() + std::to_string(score));
    first->setText(first->getText() + std::to_string(top3[0]));
    second->setText(second->getText() + std::to_string(top3[1]));
    third->setText(third->getText() + std::to_string(top3[2]));
}