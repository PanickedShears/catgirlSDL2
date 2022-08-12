#include <iostream>
#include "scene_intro.h"
using namespace std;

string EN_getNextString(int chId)
{
	string ret;
	switch (chId)
	{
		case 1:
			ret = "You'd like her?";
			break;
		case 2:
			ret = "What will you name her?";
			break;
	}

	return ret;
}

string JP_getNextString(int chId)
{
	string ret;
	switch (chId)
	{
	case 1:
		ret = "彼女求める?";
		break;
	case 2:
		ret = "彼女の名前は?";
		break;
	}

	return ret;
}

bool isIntroFinished(int chId)
{
	if (chId == 2) return true;
	else return false;
}