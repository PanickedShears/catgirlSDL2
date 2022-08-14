#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "catgirl.h"

const int SPLASH_SCREEN_DELAY = 500;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Surface* screenSurface = NULL;
SDL_Window* window = NULL;

SDL_Surface* logoImg = NULL;

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	logoImg = SDL_LoadBMP("resource/img/logo.bmp");
	if (logoImg == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "resource/img/logo", SDL_GetError());
		success = false;
	}

	return success;
}

int main(int argc, char* args[])
{
	printf("main reached\n");
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("boot fail!\nSDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("cat.girl", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("boot fail!\nWindow could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			loadMedia();
			screenSurface = SDL_GetWindowSurface(window);

			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
			SDL_BlitSurface(logoImg, NULL, screenSurface, NULL);

			//Update the surface
			SDL_UpdateWindowSurface(window);

			SDL_Delay(SPLASH_SCREEN_DELAY);

			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
			SDL_UpdateWindowSurface(window);

			//TTF_Init(); dont need cause initialized in catgirl.cpp

			// starts the rest of the game
			printf("start main game...\n");
			catgirl_start(window, screenSurface);
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}