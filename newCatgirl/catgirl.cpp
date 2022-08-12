// THIS GAME IS SEVERELY UNOPTIMIZED!
// 
// i do not care to learn cpp well
// enough to make this "optimized"
// 
// i know how to make it not use half your cpu, so
// if it ain't broke, dont fix it

/*

#include "catgirl.h"
#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "init_sgm.h"
#include <SDL_mixer.h>
#include <iostream>

// important SDL variables
SDL_Window* win = NULL;
SDL_Surface* sfc = NULL;
SDL_Renderer* ren = NULL;
SDL_Event e;

// media such as GUI
SDL_Surface* frames = NULL;
SDL_Texture* frameTex = NULL;
TTF_Font* mainFont = NULL;
TTF_Font* mainFontSm = NULL;

// lots of gui elements
SDL_Surface* titleTextSfc = NULL;
SDL_Texture* titleTextTx = NULL;
SDL_Surface* statsHapTextSfc = NULL;
SDL_Texture* statsHapTextTx = NULL;
SDL_Surface* statsHunTextSfc = NULL;
SDL_Texture* statsHunTextTx = NULL;
SDL_Surface* statsLoveTextSfc = NULL;
SDL_Texture* statsLoveTextTx = NULL;

// music/sfx
Mix_Music* m01 = NULL; // 
Mix_Chunk* s00 = NULL; // text sfx

// variables for scenes and chats and stuff (optimize later)
int scene = 0;                      // selects what the screen mainly shows
int subscene = 0;                   // helps with smaller elements
int chatId = 0;                     // probably used to define which chat is happening
std::string chatChara = NULL;       // the character name of the chat
std::string chatContents = NULL;    // the message the character is saying
std::string displayedChat = NULL;   // the displayed chat on the screen. assign scrolling letters to this variable.
bool chatWait = false;              // defines whether or not to wait for user input

// game variables
bool end = false;
int hap = 100, hun = 25, love = 1;
char gameTitle[] = "cat.girl v1.0";
char currName = NULL;
char* loaded_name = NULL;


static void catgirl_cleanup()
{
    SDL_DestroyTexture(frameTex);
    SDL_FreeSurface(frames);
    SDL_FreeSurface(sfc);
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);

    // ttf cleanup
    SDL_DestroyTexture(titleTextTx);
    SDL_FreeSurface(titleTextSfc);
    SDL_DestroyTexture(statsHapTextTx);
    SDL_FreeSurface(statsHapTextSfc);
    SDL_DestroyTexture(statsHunTextTx);
    SDL_FreeSurface(statsHunTextSfc);
    SDL_DestroyTexture(statsLoveTextTx);
    SDL_FreeSurface(statsLoveTextSfc);

    TTF_CloseFont(mainFont);
    TTF_Quit();

    Mix_FreeMusic(m01);
    Mix_FreeChunk(s00);
    Mix_Quit();
}


static void prepIntro()
{
    chatChara = "???";
    chatContents = "???";
    displayedChat = "";
}

static void drawTextBox()
{
    SDL_Rect cb0 = { 10,370,100,620 };
    SDL_Rect cb1 = { 15,375,90,610 };
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderFillRect(ren, &cb0);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderFillRect(ren, &cb1);

    // draw the chara name
    SDL_Color white = { 255, 255, 255 };
    SDL_Surface* cnsfc = TTF_RenderText_Solid(mainFont, const_cast<char*>(chatChara.c_str()), white);
    SDL_Texture* cntxt = SDL_CreateTextureFromSurface(ren, cnsfc);
    SDL_Rect ctrect = { 20, 380, 0, 0 };
    SDL_QueryTexture(cntxt, NULL, NULL, 0, 0);
    SDL_RenderCopy(ren, cntxt, NULL, &ctrect);
    // cleanup, free memory
    SDL_DestroyTexture(cntxt);
    SDL_FreeSurface(cnsfc);
    
    // draw the tb contents
    SDL_Surface* ctsfc = TTF_RenderText_Solid(mainFont, const_cast<char*>(chatContents.c_str()), white);
    SDL_Texture* cttxt = SDL_CreateTextureFromSurface(ren, ctsfc);
    SDL_Rect ccrect = { 20, 410, 0, 0 };
    SDL_QueryTexture(cttxt, NULL, NULL, 0, 0);
    SDL_RenderCopy(ren, cttxt, NULL, &ccrect);
    // cleanup, free memory
    SDL_DestroyTexture(cttxt);
    SDL_FreeSurface(ctsfc);
}

static void loadMedia()
{
	frames = SDL_LoadBMP("resource/img/gui_frames.bmp");
    if (frames == NULL) {
        end = true;
        printf("Failed to load gui_frames.bmp\n");
    }
    else
    {
        frameTex = SDL_CreateTextureFromSurface(ren, frames);
        printf("gui_frames -> tex: OK\n");
    }
    mainFont = TTF_OpenFont("resource/font/rainyhearts.ttf", 32);
    mainFontSm = TTF_OpenFont("resource/font/rainyhearts.ttf", 24);
    if (mainFont == NULL)
        printf("Failed to load main font!\n");
    else
        printf("Main font loaded OK.\n");

    m01 = Mix_LoadMUS("resource/wav/01.wav");
    if (m01 == NULL) printf("Failed to get m01.\n");
    s00 = Mix_LoadWAV("resource/wav/aa.wav");
    if (s00 == NULL) printf("Failed to get s00.\n");
}

static void prepBaseTexts()
{
    // top text (catgirl name maybe?)
    SDL_Color white = { 255, 255, 255 };
    titleTextSfc = TTF_RenderText_Solid(mainFont, &currName, white);
    titleTextTx = SDL_CreateTextureFromSurface(ren, titleTextSfc);
    // stats texts
    statsHapTextSfc = TTF_RenderText_Solid(mainFontSm, "HAPPINESS", white);
    statsHapTextTx = SDL_CreateTextureFromSurface(ren, statsHapTextSfc);
    statsHunTextSfc = TTF_RenderText_Solid(mainFontSm, "HUNGER", white);
    statsHunTextTx = SDL_CreateTextureFromSurface(ren, statsHunTextSfc);
    statsLoveTextSfc = TTF_RenderText_Solid(mainFontSm, "LOVE", white);
    statsLoveTextTx = SDL_CreateTextureFromSurface(ren, statsLoveTextSfc);
}

static void drawGUIbase()
{
    SDL_RenderCopy(ren, frameTex, NULL, NULL);

    // draw stats bars
    SDL_Rect statsBar = { 445, 90, 150, 20 }; // happiness
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderFillRect(ren, &statsBar);
    statsBar = { 445, 150, 150, 20 }; // hunger
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderFillRect(ren, &statsBar);
    statsBar = { 445, 210, 150, 20 }; // love
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderFillRect(ren, &statsBar);

    // draw stats bars fills
    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
    int sbHap = round(hap * 1.5);
    int sbHun = round(hun * 1.5);
    int sbLove = round(love * 1.5);
    SDL_Rect sbFill = { 445, 90, sbHap, 20 };
    SDL_RenderFillRect(ren, &sbFill);
    sbFill = { 445, 150, sbHun, 20 };
    SDL_RenderFillRect(ren, &sbFill);
    sbFill = { 445, 210, sbLove, 20 };
    SDL_RenderFillRect(ren, &sbFill);
}

static void drawBaseText()
{
    // positions n stuff
    int texW = 0, texH = 0;
    SDL_QueryTexture(titleTextTx, NULL, NULL, &texW, &texH);
    SDL_Rect ttrect = { 15, 13, texW, texH };

    // render the stats seperately cause its easier
    SDL_QueryTexture(statsHapTextTx, NULL, NULL, &texW, &texH);
    SDL_Rect strect = { 445, 70, texW, texH };
    SDL_RenderCopy(ren, statsHapTextTx, NULL, &strect);
    SDL_QueryTexture(statsHunTextTx, NULL, NULL, &texW, &texH);
    strect = { 445, 130, texW, texH };
    SDL_RenderCopy(ren, statsHunTextTx, NULL, &strect);
    SDL_QueryTexture(statsLoveTextTx, NULL, NULL, &texW, &texH);
    strect = { 445, 190, texW, texH };
    SDL_RenderCopy(ren, statsLoveTextTx, NULL, &strect);

    // render text
    SDL_RenderCopy(ren, titleTextTx, NULL, &ttrect);
}

int catgirl_start(SDL_Window* window, SDL_Surface* screenSurface)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }

    bool first = true; // used for music fading
	win = window;
	sfc = screenSurface;

	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Init();
    loadMedia();
    prepBaseTexts();


    // scan for the savegame, if its there, skip the begin phase
    if (!scanForSavegame())
    {
        // Confirm game start, probably remove this later..
        SDL_Color white = { 255, 255, 255 };
        SDL_Surface* sgText = TTF_RenderText_Solid(mainFontSm, "No savegame found. Press Enter to begin game, or exit to quit.", white);
        SDL_Texture* sgTextTx = SDL_CreateTextureFromSurface(ren, sgText);
        int texW = 0, texH = 0;
        SDL_QueryTexture(sgTextTx, NULL, NULL, &texW, &texH);
        SDL_Rect sgrect = { 0, 0, texW, texH };
        SDL_RenderCopy(ren, sgTextTx, NULL, &sgrect);
        SDL_DestroyTexture(sgTextTx);
        SDL_FreeSurface(sgText);
        SDL_RenderPresent(ren);

        while (scene == 0)
        {
            // check keyboard
            while (SDL_PollEvent(&e) != 0)
            {
                // User requests quit
                if (e.type == SDL_QUIT)
                {
                    scene = 1;
                    end = true;
                }
                else if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_RETURN:
                        // Switch to beginning scene
                        scene = 2;
                        SDL_Rect fs = { 0, 0, 640, 480 };
                        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                        SDL_RenderFillRect(ren, &fs);
                        SDL_RenderPresent(ren);
                        //prepIntro();
                        SDL_Delay(750);
                        break;
                    }
                }
            }
        }
    }
    else scene = 1;


    // ACTUAL game code
	while (!end)
	{
        // Handle events on queue
        // Keep first or else it wont work
        while (SDL_PollEvent(&e) != 0)
        {
            // User requests quit
            if (e.type == SDL_QUIT)
            {
                end = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    end = true;
                    break;
                }
            }
        }

        Uint64 start = SDL_GetPerformanceCounter();

        switch (scene)
        {
            case 0:
                printf("Savegame fail!!\n");
                break;
            case 1:
                drawGUIbase();
                drawBaseText();
                break;
            case 2:
                if (Mix_PlayingMusic() == 0)
                {
                    // play music if no other music is playing.
                    Mix_PlayMusic(m01, -1);
                    if (first)
                    {
                        Mix_VolumeMusic(0);
                        for (int i = 0; i < 100; i++)
                        {
                            Mix_VolumeMusic(i);
                            SDL_Delay(16.666f);
                        }
                        first = false;
                    }
                }
                chatChara = "TestCb";
                chatContents = "This is a test.";
                break;
            default:
                printf("SCENE INVALID!\n");
                end = true;
        }

        SDL_RenderPresent(ren); // very important lol

        Uint64 end = SDL_GetPerformanceCounter();

        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        if (16.666f - elapsedMS < 0.0f) elapsedMS = 0.0f; // skip the delay if it is negative (IMPORTANT!)

        // Cap to 60 FPS
        //printf("%f", 16.666f - elapsedMS);
        SDL_Delay(floor(16.666f - elapsedMS));
	}

    catgirl_cleanup();

	return 0;
}

*/