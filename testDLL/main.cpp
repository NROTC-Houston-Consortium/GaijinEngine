#include<iostream>
#include<SDL/SDL.h>
#include<SDL/SDL_mixer.h>
#include "initGaijinEngine.h"
#include "GaijinEngineAudio.h"

SDL_Surface* backBuffer;

int main(int argc, char* argv [])
{
    if(!initFunc::initSDL())
    {
        return 0;
    }

    if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        printf("Not working!");
        Mix_CloseAudio();
                return 0;
    }

    backBuffer = initFunc::initCreateWindow(800, 600, 32);
    initFunc::initSetCaption("Test", "Test");
int j=0;



    Mix_Chunk* sound = NULL;
    sound = Mix_LoadWAV("ahem_x.wav");
    int channel = Mix_PlayChannel(-1, sound, -1);

    do
    {

        j++;
        SDL_Delay(100);
    }while(j<100);

    //std::cout<< "Hello"<<std::endl;
    Mix_FreeChunk(sound);
    Mix_CloseAudio();
    initFunc::initSDLQuit();
    return 0;
}
