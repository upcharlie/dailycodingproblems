// textapps.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <fstream>
#include <cwchar>
#include <windows.h>

using namespace std;


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
	int randomNumberNoun = rand() % 4554;
	int randomNumberAdj = rand() % 1446;
	string fileLocationNouns = "C:\\Users\\CharlieJ\\Desktop\\nouns.txt";
	string fileLocationAdjectives = "C:\\Users\\CharlieJ\\Desktop\\adjectives.txt";

	string nounReturn = wordWrite(fileLocationNouns, randomNumberNoun);
	string adjReturn = wordWrite(fileLocationAdjectives, randomNumberAdj);

	cout << "May your " << nounReturn << "'s be " << adjReturn << " today!" << endl;
	string end;
	cin >> end;

	
    return 0;
}

