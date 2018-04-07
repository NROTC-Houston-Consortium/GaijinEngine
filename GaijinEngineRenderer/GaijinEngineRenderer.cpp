#include<SDL/SDL.h>
#include"GaijinEngineRenderer.h"
#include<iostream>

namespace surfaceRenderer
{
    bool DLL_EXPORT freeSurface(SDL_Surface* surface)
    {
        SDL_FreeSurface(surface);
        if(surface == NULL)
            return true;
        return false;
    }

    bool DLL_EXPORT loadSprite(SDL_Surface* surface, char* stringName)
    {
        surface = SDL_load
    }



}
