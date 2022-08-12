// initial savegame manager

#include <stdio.h>
#include <Windows.h>
#include <shlwapi.h>
#include "init_sgm.h"

#pragma comment(lib,"shlwapi.lib") 

bool scanForSavegame()
{
	return PathFileExistsA("./catgirl.sav");
}