// TextAdventure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <tuple>
#include "stdafx.h"

#include <stdexcept>
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <fstream>
#include <cwchar>
#include <windows.h>
using namespace std;


bool iteratorSearch(vector <string> wordSearch, string wordInput)
{
	if (find(wordSearch.begin(), wordSearch.end(), wordInput) != wordSearch.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

string optionInput(string movement, string message)
{
	cout << message;
	cin >> movement;
	transform(movement.begin(), movement.end(), movement.begin(), ::tolower);
	return movement;

}

class Character
{
public:
	string name;
	string character_class;
	int HP = 10;
	int DMG = 1;
	int XP = 0;
	int levelUp = 100;
	int level = 1;

	void stat_output() // call this with character.stat_output();
	{
		cout << name << endl;
		cout << "Your damage stat is: " << DMG << endl;
		cout << "Your health points are: " << HP << endl;
		cout << "You have gained " << XP << " XP points" << endl;
		cout << "Amount of XP until next level up: " << levelUp << endl;
	}

	void class_pick(string class_option)
	{
		vector<string> vector_Def = { "defense", "def" };
		vector<string> vector_Atk = { "attack", "atk" };

		if (iteratorSearch(vector_Atk, class_option) == true)
		{
			DMG += 1;
		}

		else if (iteratorSearch(vector_Def, class_option) == true)
		{
			HP += 2;
		}
	}

	void class_xp_add(int xp)
	{
		xp += 20;
	}


};


string enterName()
{
	string ask_name;
	cout << "What's your name? " << endl;
	cin >> ask_name;
	return ask_name;
}

string enterClass()
{
	string message;
	string ask_class;
	int check_response = 0;
	while (check_response == 0)
	{
		ask_class = optionInput(ask_class, "What class are you? ");

		vector<string> class_Defense = { "defense", "def" };
		vector<string> class_Attack = { "attack", "atk" };

		if (iteratorSearch(class_Defense, ask_class) == true)
		{
			message = "Ahh, so you're of the defensive class then...";
			check_response = 1;
		}
		else if (iteratorSearch(class_Attack, ask_class) == true)
		{
			message = "Ahh, so you're of the attacking class then...";
			check_response = 1;
		}
		else
		{
			message = "Sorry I didn't understand that. ";
		}
		cout << message << endl;

	}
	return ask_class;
}


string updateXY(int x, int y) //takes in the x/y coordinates and returns them together as a string
{
	string stringX = to_string(x);
	string stringY = to_string(y);
	string xy = stringX + stringY;
	return xy;
}

string wordWrite(string fileLocation, int randomNumber)
{
	ifstream inFile;
	inFile.open(fileLocation);

	if (!inFile) {
		cout << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	string line;
	int linecount = 0;
	while (getline(inFile, line))
	{
		++linecount;
		if (linecount == randomNumber)
		{
			inFile.close();
			return line;
		}

	}
	inFile.close();
}
string nameGen()
{
	
		int randomNumberPrefix = rand() % 8;
		int randomNumberMiddle = rand() % 4;
		int randomNumberSuffix = rand() % 4;
		string fileLocationPrefix = "C:\\Users\\CharlieJ\\Desktop\\monster PREFIX.txt";
		string fileLocationMiddle = "C:\\Users\\CharlieJ\\Desktop\\monster MIDDLE.txt";
		string fileLocationSuffix = "C:\\Users\\CharlieJ\\Desktop\\monster SUFFIX.txt";
		

		string prefixReturn = wordWrite(fileLocationPrefix, randomNumberPrefix);
		string middleReturn = wordWrite(fileLocationMiddle, randomNumberMiddle);
		string suffixReturn = wordWrite(fileLocationSuffix, randomNumberSuffix);

		string monName = prefixReturn + middleReturn + suffixReturn;
		return monName;
	}




pair<int, vector <int>> fight(int monHP, int monDMG, int HP, int DMG, string monName, vector <int> potionList)
{
	while (monHP > 0)
	{
		string chooseFight = "";
		cout << "Your current HP is: " << HP << endl;
		cout << "Would you like to Fight, Run or use a Potion? ";
		cin >> chooseFight;
		transform(chooseFight.begin(), chooseFight.end(), chooseFight.begin(), ::tolower);
		vector<string> fightList = { "fight" };
		if (iteratorSearch(fightList, chooseFight) == true)
		{
			monHP = monHP - DMG;
			
			cout << "Your HP has dropped from " << HP << " to " << HP - monDMG << endl;
			HP = HP - monDMG;
			
		}
		vector<string> runList = { "run" };
		if (iteratorSearch(runList, chooseFight) == true)
		{
			return make_pair(HP, potionList);
		}
		vector<string> itemList = { "potion", "heal", "item" };
		if (iteratorSearch(itemList, chooseFight) == true)
		{
			if (potionList.size() == 0)
			{
				cout << "You have no potions left! " << endl;
			}
			else
			{
				HP = HP + 10;
				cout << "You used a potion and gained 10 HP!" << endl;
				for (int i = 0; i < potionList.size();i++)
				{
					if (potionList[i] == 10)
					{
						potionList.erase(potionList.begin() + i);
						i = potionList.size();
					}
				}
			}
		}
		if (HP < 0)
		{
			HP = 0;
			cout << "You died..." << endl;
			return make_pair(0, potionList);
		}
	}
	return make_pair(HP, potionList);
}

pair<int, vector <int>> encounter(int x, int y, vector <string> visitedList, int hp, int DMG, int xp, int level, int monHP, int monDMG, vector <int> potionList)
{
	string monName = "randomnamegen";
	int randRoom = rand() % 100;
	int baseRand = 50;
	if (iteratorSearch(visitedList, updateXY(x, y)) == true)
	{
		cout << "You have already visited this room..." << endl;
	}
	else if (randRoom > baseRand)
	{
		//insert random name generator function and weapon generator
		cout << "You have encountered a " << nameGen() << " ! " << endl;
		//run fight function - return HP lost
		//calculate xp here
		auto resultFight = fight(monHP, monDMG, hp, DMG, monName, potionList);
		hp = resultFight.first;
		potionList = resultFight.second;
		if (hp < 1)
		{
			return make_pair(0, potionList);
		}
		
	}
	else if (randRoom < baseRand)
	{
		potionList.push_back(10);
		cout << "You have found a potion!" << endl;
	}
	return make_pair(hp, potionList );
}



pair<int, int> keywordsMovement(int x, int y, string movement)
{
	string message;
	vector<string> up = { "up" };
	vector<string> down = { "down" };
	vector<string> left = { "left" };
	vector<string> right = { "right" };

	if (iteratorSearch(up, movement) == true)
	{
		message = "You have moved up. ";
		y = y + 1;
	}
	else if (iteratorSearch(down, movement) == true)
	{
		message = "You have moved down. ";
		y = y - 1;
	}
	else if (iteratorSearch(left, movement) == true)
	{
		message = "You have moved left. ";
		x = x - 1;
	}
	else if (iteratorSearch(right, movement) == true)
	{
		message = "You have moved right. ";
		x = x + 1;
	}
	else
	{
		message = "I didn't get that...";
	}


	cout << message << endl;
	return make_pair(x, y);
}


int main()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 30;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	srand(time(NULL));

	int x = 0;
	int y = 0;
	string movement, name, character_class, movementMessage;
	vector <string> visitedList = {"00"};

	name = enterName();
	character_class = enterClass();
	movementMessage = "Up, Down, Left or Right?: ";

	Character character;
	character.name = name;
	character.class_pick(character_class);
	character.stat_output();

	//while (!(x == 2)&&(y == 2))
	while (x < 1)
	{
		movement = optionInput(movement, movementMessage);
		if (movement == "quit")
		{
			return 0;
		}
		auto result_keywords = keywordsMovement(x, y, movement);
		x = result_keywords.first;
		y = result_keywords.second;
		cout << x << " " << y << endl;
		//run encounter function here
		double monHP = rand() % 5 + 1;
		double monDMG = rand() % 5 + 1;
		int baseXP = 0;
		vector <int> potionList{10,10,10};
		auto result_encounter = encounter(x, y, visitedList, character.HP, character.DMG, character.XP, character.level, monHP, monDMG, potionList);
		cout << character.HP << " " << character.XP << endl;
		character.HP = result_encounter.first;
		if (character.HP < 1)
		{
			cout << "You died..." << endl;
			return 0;
		}
		else
		{
			character.XP = character.level * monDMG + rand() % 100;
			cout << character.XP << endl;
		}
		visitedList.push_back(updateXY(x, y));
	}

}

