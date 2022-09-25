#include <iostream>
#include "scene_intro.h"
using namespace std;

string EN_getNextString(int chId)
{
	string ret;
	switch (chId)
	{
		case 1:
			ret = "Welcome to the Catgirl Adoption Center!";
			break;
		case 2:
			ret = "What can I get you today?";
			break;
		case 3:
			ret = "I want a catgirl.";
			break;
		case 4:
			ret = "The adoption center worker looks at her computer screen...";
			break;
		case 5:
			ret = "Oh dear...";
			break;
		case 6:
			ret = "You sigh, but don't say anything else. She continues...";
			break;
		case 7:
			ret = "Our kitten selection is very small right now.";
			break;
		case 8:
			ret = "We only have one little catgirl.";
			break;
		case 9:
			ret = "The worker points towards a small kitten with pink-colored eyes.";
			break;
		case 10:
			ret = "Do you like this one?";
			break;
		case 11:
			ret = "Yeah. Perfect.";
			break;
		case 12:
			ret = "She hands you the adoption papers, which read \"Name: Chloe.\"";
			break;
		case 13:
			ret = "Please sign here and initial these two spots as well,";
			break;
		case 14:
			ret = "If you have any questions or concerns about her, please don't hesitate to call us!";
			break;
		case 15:
			ret = "You smile and thank her before leaving the building.";
			break;
	}

	//cout << "intro handoff contents: " << ret << endl;
	return ret;
}
string EN_getNextChara(int chId)
{
	string ret;
	switch (chId)
	{
	case 1:
		ret = "Catgirl Adoption Center Worker";
		break;
	case 2:
		ret = "Catgirl Adoption Center Worker";
		break;
	case 3:
		ret = "You";
		break;
	case 4:
		ret = " ";
		break;
	case 5:
		ret = "Catgirl Adoption Center Worker";
		break;
	case 6:
		ret = " ";
		break;
	case 7:
		ret = "Catgirl Adoption Center Worker";
		break;
	case 8:
		ret = "Catgirl Adoption Center Worker";
		break;
	case 9:
		ret = " ";
		break;
	case 10:
		ret = "Catgirl Adoption Center Worker";
		break;
	case 11:
		ret = "You";
		break;
	case 12:
		ret = " ";
		break;
	case 13:
		ret = "Catgirl Adoption Center Worker";
		break;
	case 14:
		ret = "Catgirl Adoption Center Worker";
		break;
	case 15:
		ret = " ";
		break;
	}

	//cout << "intro handoff chara: " << ret << endl;
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