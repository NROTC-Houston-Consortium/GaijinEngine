#include"initGaijinEngine.h"
#include<iostream>
#include<ctime>
#include<string>
#include<SDL/SDL.h>


namespace initFunc
{
    bool DLL_EXPORT initSDL()
    {
        bool initSucc = true;
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            initDebug("SDL failed to initialize! SDL_Error:");
            initDebug(SDL_GetError());
            initDebug(initDateTime());
            initSucc = false;
        }
        else
        {
            printf("SDL was successful to initialize!");
            initDebug(initDateTime());
        }
        return initSucc;
    }

    void DLL_EXPORT initDebug(char* str)
    {
        printf(str);
    }

    char* DLL_EXPORT initDateTime()
    {
        time_t now = time(0);
        char* dt = ctime(&now);
        return dt;
    }

    void DLL_EXPORT initSDLQuit()
    {
        SDL_Quit();
    }

    SDL_Surface* DLL_EXPORT initCreateWindow(int width, int height, int colorMap)
    {
        return SDL_SetVideoMode(width, height, colorMap, SDL_SWSURFACE);
    }

    void DLL_EXPORT initSetCaption(char* windowName, char* minimizedName)
    {
        SDL_WM_SetCaption(windowName, minimizedName);
    }

}
