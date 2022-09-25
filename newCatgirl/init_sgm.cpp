// initial savegame manager

#include <stdio.h>
#include <Windows.h>
#include <shlwapi.h>
#include "init_sgm.h"
#include <iostream>
#include <sstream>
using namespace std;

#pragma comment(lib,"shlwapi.lib") 

bool scanForSavegame()
{
	return PathFileExistsA("./catgirl.sav");
}

bool saveGame(int hap, int hun, int love, int storyChapter, int storyExt)
{
	FILE* sav = NULL;
	stringstream saveOutput;

	saveOutput << "[catgirl]" << endl;
	saveOutput << "name = Chloe" << endl;
	saveOutput << "hap = " << hap << endl;
	saveOutput << "hun = " << hun << endl;
	saveOutput << "love= " << love << endl;
	saveOutput << "items = 0" << endl;
	saveOutput << "[story]" << endl;
	saveOutput << "chapter = " << storyChapter << endl;
	saveOutput << "ext = " << storyExt << endl;


	fopen_s(&sav, "./catgirl.sav", "w");

	if (!sav) {
		printf("Failed to save game!\n");
		return false;
	}
	else 
	{
		fprintf(sav, "%s", saveOutput.str().c_str());
		return true;
	}
}