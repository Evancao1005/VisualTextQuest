// Main.h
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 22/04/2016



#ifndef MAIN_H
#define MAIN_H

#include <string>

using namespace std;

void startGame();
void gameLoop();
void fight(int, int);
void createCharacter();
void loadGame();
void saveGame();
void saveMap(int);
void generateMaze();
void drawMap();
void playerWalk(int&, int&);
int countLinesInFile(string file);

#endif


