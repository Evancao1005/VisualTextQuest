

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>


using namespace std;

#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Vocation.h"
#include "Event.h"
#include "EnemyFactory.h"
#include "Game.h"


/*

Game game;
Player* player = game.getPlayer();
vector<Vocation*> vocations = game.getVocations();
vector<Event*> events = game.getEvents();
Room* mazeRoom = game.getRoom();

void drawMap() {
	system("cls");
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			bool condition1 = (i % 2 == 0);
			bool condition2 = (j % 2 == 0);

			if (i*j != 0 && (i != 20 && j != 20)) {
				if (condition1 && condition2) {
					cout << "\u25A0";
				}
				else if (condition1 && !condition2)
				{
					if (mazeRoom->getRoomFromArray(i / 2 -1, (j - 1) / 2).getDoorS())
					{
						cout << "  ";
					}
					else {
						cout << "\u25A0";
					}
				}
				else if (!condition1 && condition2)
				{
					if (mazeRoom->getRoomFromArray((i - 1) / 2, j / 2 - 1).getDoorE())
					{
						cout << "  ";
					}
					else {
						cout << "\u25A0";
					}
				}
				else
				{
					if (mazeRoom->getRoomFromArray((i - 1) / 2, (j - 1) / 2).getPlayer()) {
						cout << " P";

						if (i == 1 && j == 19)
						{
							cout << ((j - 1) / 2);
						}

					}
					else {
						cout << "\u25A1";
					}

				}
			}
			else
			{
				cout << "\u25A0";
			}

		}
		cout << endl;
	}
}

*/

/*
int main2() {

	fstream myfile;
	string vocation, description;
	int health, strength, magic, healthModifier;
	char comma, continueChoice;
	string line;


	myfile.open("events.txt");
	while (getline(myfile, line)) {
		stringstream ss(line);
		getline(ss, description, ',');
		ss >> healthModifier;
		events.push_back(new Event(description, healthModifier));
	}
	myfile.close();

	srand(static_cast<unsigned>(time(NULL)));

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Room cacheRoom(i, j, events);
			mazeRoom->setRoomToArray(i, j, cacheRoom);
		}
	}

	mazeRoom->getRoomFromArray(0,9);
	mazeRoom->getRoomFromArray(1,0);
	

	int playerX = rand() % 10;
	int playerY = rand() % 10;
	mazeRoom->setPlayer(playerX, playerY);

	string input;



	/*
	while (true)
	{

		cin >> input;
		if (input == "W") {
			if (mazeRoom->getRoomFromArray(playerX, playerY).getDoorN()) {
				mazeRoom->setPlayer(playerX, playerY);
				playerX -= 1;
				mazeRoom->setPlayer(playerX, playerY);
			}
			else {
				cout << "There is no door in that direction";
				system("Pause");
			}
		}
		else if (input == "S") {
			if (mazeRoom->getRoomFromArray(playerX, playerY).getDoorS()) {
				mazeRoom->setPlayer(playerX, playerY);
				playerX += 1;
				mazeRoom->setPlayer(playerX, playerY);
			}
			else {
				cout << "There is no door in that direction";
				system("Pause");
			}
		}
		else if (input == "D") {
			if (mazeRoom->getRoomFromArray(playerX, playerY).getDoorE()) {
				mazeRoom->setPlayer(playerX, playerY);
				playerY += 1;
				mazeRoom->setPlayer(playerX, playerY);
			}
			else {
				cout << "There is no door in that direction";
				system("Pause");
			}
		}
		else if (input == "A") {
			if (mazeRoom->getRoomFromArray(playerX, playerY).getDoorW()) {
				mazeRoom->setPlayer(playerX, playerY);
				playerY -= 1;
				mazeRoom->setPlayer(playerX, playerY);
			}
			else {
				cout << "There is no door in that direction";
				system("Pause");
			}
		}	
	}
	


	system("Pause");
	return 0;
}

*/