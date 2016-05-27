// Main.cpp
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 22/04/2016
// Tim 3/5/16 - some cleanup and refactoring with extra things we covered in lectures (factory, singleton, friend, operator<< override, etc)



#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <vector>

#include "Main.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Vocation.h"
#include "Event.h"
#include "EnemyFactory.h"
#include "Game.h"

Game game;
Player* player = game.getPlayer();
vector<Vocation*> vocations = game.getVocations();
vector<Event*> events = game.getEvents();
Room* mazeRoom = game.getRoom();

int* pplayerX = game.getPlayerX();
int* pplayerY = game.getPlayerY();

void main() {

	//Initializes random seed
	srand(static_cast<unsigned>(time(NULL)));

	startGame();

	system("pause");
}

//Game set up
void startGame() {

	fstream myfile;
	string vocation, description;
	int health, strength, magic, healthModifier;
	char comma, continueChoice;
	bool loaded = false;



	//Iterates through the vocations text file and stores each vocation in a vector as an object
	myfile.open("vocations.txt");

	string line;
	while (getline(myfile, line)) {
		stringstream ss(line);
		getline(ss, vocation, ',');
		ss >> health >> comma >> strength >> comma >> magic;
		vocations.push_back(new Vocation(vocation, health, strength, magic));
	}
	myfile.close();

	//Iterates through the events text file and stores each event in a vector as an object
	myfile.open("events.txt");
	while (getline(myfile, line)) {
		stringstream ss(line);
		getline(ss, description, ',');
		ss >> healthModifier;
		events.push_back(new Event(description, healthModifier));
	}
	myfile.close();


	//Generate the maze
	generateMaze();
	*pplayerX = rand() % 10;
	*pplayerY = rand() % 10;
	mazeRoom->setPlayer(*pplayerX, *pplayerY);

	cout << "Welcome to CPlusPlusQuest!" << endl;

	continueChoice = 'x';

	//Checks if there are any existing saves present before prompting to load one or create a new character
	if (countLinesInFile("saves.txt") > 0) {

		cout << "Existing save(s) found!" << endl;

		while (continueChoice != 'y' && continueChoice != 'n') {
			cout << "Would you like to load an existing character? (y/n) ";
			cin >> continueChoice;
		}

		//Ignores any extra input (ensures extra input is not accidently read in by future 'cin' or 'getline' commands
		cin.ignore();

		if (continueChoice == 'y') {
			loadGame();
			loaded = true;

		}
		else {
			createCharacter();
		}
	}
	//No saves present, create a new character
	else {
		cout << "No existing save(s) found." << endl;
		createCharacter();
	}

	cout << player->getName() << " the " << *player->getVocation() << " is ready to begin their quest!" << endl;

	continueChoice = 'x';

	while (continueChoice != 'y' && continueChoice != 'n') {
		cout << "Would you like to begin? (y/n) ";
		cin >> continueChoice;
	}

	//Ignores any extra input (ensures extra input is not accidently read in by future 'cin' or 'getline' commands
	cin.ignore();


	//Starts main game loop
	if (continueChoice == 'y') {
		gameLoop();
	}

	cout << "Thanks for playing!" << endl;

	// cleanup
	for (Vocation* v : vocations) delete v;
	for (Event* e : events) delete e;
	delete player;
}

//The main game loop
void gameLoop() {

	char continueChoice = 'x';

	do {
		//drawMap();
		//playerWalk(*pplayerX, *pplayerY);
		//drawMap();

		insideARoom(*pplayerX, *pplayerY, 0);
		

		

		//Checks if player is still alive
		if (player->getHealth() > 0) {
			cout << player->getName() << " has " << player->getHealth() << " health remaining." << endl;
			continueChoice = 'x';
			while (continueChoice != 'y' && continueChoice != 'n') {
				cout << "Would you like to continue? (y/n) ";
				cin >> continueChoice;
			}
		}
		//Player is dead
		else {
			player->setHealth(0);
			cout << player->getName() << " has no health remaining." << endl;
		}

		vector<Event*> roomEvents = mazeRoom->getRoomFromArray(*pplayerX, *pplayerY).getEventList();

		for (int i = 0; i < mazeRoom->getRoomFromArray(*pplayerX, *pplayerY).getEventList().size(); i++)
		{
			cout << roomEvents[i]->getDescription() << endl;
			player->setHealth(player->getHealth() + roomEvents[i]->getHealthModifier());
		}

		mazeRoom->clearRoom(*pplayerX, *pplayerY);
		
	} while (player->getHealth() > 0 && continueChoice != 'n');

	continueChoice = 'x';

	//Only allow saving if player is still alive (prevents being able to load a dead character next time)
	if (player->getHealth() > 0) {
		while (continueChoice != 'y' && continueChoice != 'n') {
			cout << "Would you like to save your game? (y/n) ";
			cin >> continueChoice;
		}
	}

	if (continueChoice == 'y') {
		saveGame();
	}
}

// Fight! Fight! Fight!
// create some enemies and them together with the player into a vector of Character*
// thanks to polymorphism nothing in this function is hard coded for any subtype of Character.
void fight(int x, int y) {
	vector<Character*> participants;
	
	//Adds player to participants vector
	participants.push_back(player);

	if (mazeRoom->getRoomFromArray(x, y).getEnemyList().size() == 0) { return; }
	for (int i = 0; i < mazeRoom->getRoomFromArray(x, y).getEnemyList().size(); i++)
	{
		participants.push_back(mazeRoom->getRoomFromArray(x, y).getEnemyList().at(i));
	}

	cout << "A fight has started!" << endl;

	//Fight continues until player is defeated or there are no enemies left
	vector<Character*> stillAlive = participants;
	while (player->getHealth() > 0 && stillAlive.size() > 1) {

		//Iterates through the participants vector and calls each character's attack function
		for (Character* attacker : stillAlive) {
			//Ensures that any defeated participants do not get to attack
			if (attacker->getHealth() > 0) {
				cout << "It is " << attacker->getName() << "'s turn to attack!" << endl;
				system("pause");
				attacker->attack(stillAlive);
			}
		}
		// remove dead participants
		// (by extracting the ones that are alive into a new vector and then copying it back to the original)
		vector<Character*> tmp;
		for (Character* c : stillAlive) {
			if (c->getHealth() > 0) {
				tmp.push_back(c);
			}
		}
		stillAlive = tmp;
	}

	cout << "The fight is over!" << endl;

	
	

	//Iterates through the participants vector and deletes all participants (but not the player!)
	for (Character* p : participants) {
		if (p != player) {
			delete p;
		}
	}
}


//Creates a new character
void createCharacter() {

	string nameInput;
	unsigned inputChoice = 0;

	cout << "Creating a new character!" << endl;

	while (nameInput == "") {
		cout << "Please enter a name for your character: ";
		getline(cin, nameInput);
	}

	while (inputChoice < 1 || inputChoice > vocations.size()) {

		cout << "Please select a vocation by entering a number below: " << endl;

		//Iterates through the vocations vector and outputs each vocation
		inputChoice = 1;
		for (Vocation* v : vocations) {
			cout << inputChoice++ << ": " << *v << endl;
		}

		cin >> inputChoice;
	}

	//Creates a new character object based on nameInput and inputChoice (see above)
	player = new Player(nameInput, vocations[inputChoice - 1]);
}



//Reads in existing character stats from file
void loadGame() {

	fstream myfile;
	string name, vocationType, index;
	int health, strength, magic;
	int inputChoice = 0;
	char comma;


	while (inputChoice < 1 || inputChoice > countLinesInFile("saves.txt")) {

		cout << "Please select a character by entering a number below: " << endl;

		//Iterates through the saves text file and outputs each character
		myfile.open("saves.txt");

		string line;
		while (getline(myfile, line)) {
			stringstream ss(line);
			getline(ss, index, ',');
			getline(ss, name, ',');
			getline(ss, vocationType, ',');
			cout << index << ": " << name << " the " << vocationType << endl;
		}
		myfile.close();

		cin >> inputChoice;
	}

	//Goes to specific character (line) in text file based on inputChoice
	myfile.open("saves.txt");
	for (int i = 0; i < inputChoice - 1; i++) {
		getline(myfile, name);
	}

	//Reads in stats for character based on inputChoice (see above)
	getline(myfile, index, ',');
	getline(myfile, name, ',');
	getline(myfile, vocationType, ',');
	myfile >> health >> comma >> strength >> comma >> magic;
	myfile.close();
	Vocation* vocation = NULL;
	for (Vocation* v : vocations) {
		if (v->getName() == vocationType) {
			vocation = v;
		}
	}

	loadMap(stoi(index));

	//Creates a new character object using stats read in from file
	player = new Player(name, vocation);
	player->setHealth(health);
	player->setStrength(strength);
	player->setMagic(magic);
	cout << "Load successful!" << endl;

}

//Writes character stats to file

void saveGame() {

	fstream myfile;
	int index = countLinesInFile("saves.txt") + 1;
	//Opens file in 'append' mode (meaning it will always write to the end of the file)
	myfile.open("saves.txt", ios::app);
	myfile << index << "," << player->getName() << "," << (*player->getVocation()) << "," << player->getHealth() << "," << player->getStrength() << "," << player->getMagic() << "\n";
	myfile.close();
	saveMap(index);
	cout << "Save successful!" << endl;
}


void saveMap(int index) {
	fstream myfile;
	stringstream stream;
	string cache;
	stream << index;
	stream >> cache;
	myfile.open(cache + ".map", ios::out);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			myfile << mazeRoom->getRoomFromArray(i, j).getDoorN() << ","
				<< mazeRoom->getRoomFromArray(i, j).getDoorS() << ","
				<< mazeRoom->getRoomFromArray(i, j).getDoorW() << ","
				<< mazeRoom->getRoomFromArray(i, j).getDoorE() << ","
				<< mazeRoom->getRoomFromArray(i, j).getVisited() << ","
				<< mazeRoom->getRoomFromArray(i, j).getPlayer() << "\n";
		}
	}
}

void loadMap(int index) {
	stringstream stream;
	string cache;
	stream << index;
	stream >> cache;

	string N, S, W, E, p, v, line;
	fstream myfile; 

	myfile.open(cache + ".map");


	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			getline(myfile, line);
			stringstream ss(line);
			getline(ss, N, ',');
			getline(ss, S, ',');
			getline(ss, W, ',');
			getline(ss, E, ',');
			getline(ss, v, ',');
			getline(ss, p, '\n');
			mazeRoom->setDoorN(i, j, N);
			mazeRoom->setDoorS(i, j, S);
			mazeRoom->setDoorW(i, j, W);
			mazeRoom->setDoorE(i, j, E);
			mazeRoom->loadPlayerFromFile(i, j, p);
			mazeRoom->loadVisitedFromFile(i, j, v);
			if (stoi(p)==1) {
				*pplayerX = i;
				*pplayerY = j;
			}


		}
	}
}


//Utility function that returns the number of lines in a given file
int countLinesInFile(string file) {

	fstream myfile;
	int numLines = 0;
	string line;

	myfile.open(file);
	while (getline(myfile, line)) {
		numLines++;
	}
	myfile.close();

	return numLines;
}

void generateMaze() {
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Room cacheRoom(i, j, events);
			mazeRoom->setRoomToArray(i, j, cacheRoom);
		}
	}


}

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
					if (mazeRoom->getRoomFromArray(i / 2 - 1, (j - 1) / 2).getDoorS())
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
					else if (mazeRoom->getRoomFromArray((i - 1) / 2, (j - 1) / 2).getVisited()) {
						cout << "\u25A1";
					}else {
						cout << "* ";
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






/*
void playerWalk(int& playerX, int& playerY) {
string input;
while(true){
cin >> input;
if (input == "W") {
if (mazeRoom->getRoomFromArray(playerX, playerY).getDoorN()) {
mazeRoom->setPlayer(playerX, playerY);
playerX -= 1;
mazeRoom->setPlayer(playerX, playerY);
break;
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
break;
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
break;
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
break;
}
else {
cout << "There is no door in that direction";
system("Pause");
}
}
else if (input == "gg") {
for (int i = 0; i < 10; i++)
{
for (int j = 0; j < 10; j++)
{
mazeRoom->setVisited(i,j);
}
}
cout << "Cheat Enabled";
system("Pause");
break;
}
}

}

*/



void drawNavMap(int roomX, int roomY, int playerX, int playerY) {
	drawMap();
	cout << endl;
	bool N = mazeRoom->getRoomFromArray(roomX, roomY).getDoorN();
	bool S = mazeRoom->getRoomFromArray(roomX, roomY).getDoorS();
	bool W = mazeRoom->getRoomFromArray(roomX, roomY).getDoorW();
	bool E = mazeRoom->getRoomFromArray(roomX, roomY).getDoorE();


	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (i == playerX && j == playerY) {
				cout << " P";
			}
			else {
				if ((i*j == 0) || (i*j % 6 == 0))
				{
					if ((j == 3 && i == 0) && N) {
						cout << "  ";
					}
					else if ((j == 3 && i == 6) && S) {
						cout << "  ";
					}
					else if ((i == 3 && j == 0) && W) {
						cout << "  ";
					}
					else if ((i == 3 && (j == 6)) && E) {
						cout << "  ";
					}
					else {
						cout << "\u25A0";
					}
				}
				else {
					cout << "  ";
				}
			}
		}
		cout << endl;
	}



}




int insideARoom(int &roomX, int &roomY, int comingFrom) {
	
	//0: in the room, 1: North, 2:South, 3: West, 4:East
	int playerX, playerY;

	mazeRoom->setPlayer(roomX, roomY);

	if (comingFrom == 1) {
		playerX = 0; playerY = 3;
	}else if (comingFrom == 2) {
		playerX = 6; playerY = 3;
	}
	else if (comingFrom == 3) {
		playerX = 3; playerY = 0;
	}
	else if(comingFrom == 4) {
		playerX = 3; playerY = 6;
	}
	else {
		playerX = 1; playerY = 1;
	}

	while (true) {
		drawNavMap(roomX, roomY, playerX, playerY);
		playerWalk(playerX, playerY);


		//accessing door
		if (playerX == 3) {
			if (playerY <= 0) {
				//access the west door
				if (mazeRoom->getRoomFromArray(roomX, roomY).getDoorW())
				{
					mazeRoom->setPlayer(roomX, roomY);
					roomY -= 1;
					return insideARoom(roomX, roomY, 4);
				}
				else {
					cout << "There is no door here!" << endl;
					//playerY += 1;
				}
			}
			else if (playerY >= 6) {
				//access the east door
				if (mazeRoom->getRoomFromArray(roomX, roomY).getDoorE())
				{
					mazeRoom->setPlayer(roomX, roomY);
					roomY += 1;
					return insideARoom(roomX, roomY, 3);

				}
				else {
					cout << "There is no door here!" << endl;
					//playerY -= 1;
				}
			}
		}
		else if (playerY == 3) {
			if (playerX <= 0) {
				//access the north door
				if (mazeRoom->getRoomFromArray(roomX, roomY).getDoorN())
				{
					mazeRoom->setPlayer(roomX, roomY);
					roomX -= 1;
					return insideARoom(roomX, roomY, 2);

				}
				else {
					cout << "There is no door here!" << endl;
					//playerX += 1;
				}
			}
			else if (playerX >= 6) {
				//access the south door
				if (mazeRoom->getRoomFromArray(roomX, roomY).getDoorS())
				{
					mazeRoom->setPlayer(roomX, roomY);
					roomX += 1;
					return insideARoom(roomX, roomY, 1);

				}
				else {
					cout << "There is no door here!" << endl;
					//playerX -= 1;
				}
			}
		}

		//accessing wall
		if (playerX == 0) { playerX += 1; }
		if (playerX == 6) { playerX -= 1; }
		if (playerY == 0) { playerY += 1; }
		if (playerY == 6) { playerY -= 1; }


	}

	fight(roomX, roomY);

	return 0;
}

void playerWalk(int& playerX, int& playerY) {
	string input;
	while (true) {
		cin >> input;
		if (input == "W") {
				playerX -= 1;
				break;
		}
		else if (input == "S") {
				playerX += 1;
				break;
		}
		else if (input == "D") {
				playerY += 1;
				break;
		}
		else if (input == "A") {
				playerY -= 1;
				break;
		}
		else if (input == "gg") {
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					mazeRoom->setVisited(i, j);
				}
			}
			cout << "Cheat Enabled";
			system("Pause");
			break;
		}
	}


}