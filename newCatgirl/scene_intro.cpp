#include <iostream>
#include "scene_intro.h"
using namespace std;

string EN_getNextString(int chId)
{
	string ret;
	switch (chId)
	{
		case 1:
			ret = "Found one you wanna take home?";
			break;
		case 2:
			ret = "Yeah.";
			break;
		case 3:
			ret = "You own any other catgirls?";
			break;
		case 4:
			ret = "She'll be my first.";
			break;
		case 5:
			ret = "Ooh, a new owner?";
			break;
		case 6:
			ret = "You've read up on how to keep them, right?";
			break;
		case 7:
			ret = "Yep. I've got everything at home ready.";
			break;
		case 8:
			ret = "Alright!";
			break;
		case 9:
			ret = "You're one of the more prepared owners, I see?";
			break;
		case 10:
			ret = "I guess you could say.";
			break;
		case 11:
			ret = "Well in that case,";
			break;
		case 12:
			ret = "If you need anything, don't hesitate to call...";
			break;
		case 13:
			ret = "...and we'll answer any questions you have!";
			break;
		case 14:
			ret = "Best of luck to you and your new catgirl!";
			break;
	}

	cout << "intro handoff contents: " << ret << endl;
	return ret;
}
string EN_getNextChara(int chId)
{
	string ret;
	switch (chId)
	{
	case 1:
		ret = "Shelter Worker";
		break;
	case 2:
		ret = "You";
		break;
	case 3:
		ret = "Shelter Worker";
		break;
	case 4:
		ret = "You";
		break;
	case 5:
		ret = "Shelter Worker";
		break;
	case 6:
		ret = "Shelter Worker";
		break;
	case 7:
		ret = "You";
		break;
	case 8:
		ret = "Shelter Worker";
		break;
	case 9:
		ret = "Shelter Worker";
		break;
	case 10:
		ret = "You";
		break;
	case 11:
		ret = "Shelter Worker";
		break;
	case 12:
		ret = "Shelter Worker";
		break;
	case 13:
		ret = "Shelter Worker";
		break;
	case 14:
		ret = "Shelter Worker";
		break;
	}

	cout << "intro handoff chara: " << ret << endl;
	return ret;
}

string JP_getNextString(int chId)
{
	string ret;
	switch (chId)
	{
	case 1:
		ret = "”Þ—‹‚ß‚é?";
		break;
	case 2:
		ret = "”Þ—‚Ì–¼‘O‚Í?";
		break;
	}

	return ret;
}

bool isIntroFinished(int chId)
{
	if (chId == 2) return true;
	else return false;
}