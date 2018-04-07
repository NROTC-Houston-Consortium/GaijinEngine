#include<SDL/SDL.h>
#include<SDL/SDL_mixer.h>
#include<iostream>
#include<ctime>
#include "GaijinEngineAudio.h"


namespace Audio
{

    bool DLL_EXPORT initAudio(int freq, Uint16 format, int channels, int chunkSize)
    {
        if(Mix_OpenAudio(freq, MIX_DEFAULT_FORMAT, channels, chunkSize) < 0)
        {
            audioDebug("Mixer failed to initialize! ");
            return false;
        }


        return true;
    }

    void DLL_EXPORT audioDebug(char* name)
    {
        printf(name);
    }

    void DLL_EXPORT audioClose()
    {
        Mix_CloseAudio();

    }

    void DLL_EXPORT loadSound(char* fileName)
    {
        Mix_Chunk* sound = NULL;
        sound = Mix_LoadWAV(fileName);
    }

    bool DLL_EXPORT freeSound(Mix_Chunk* mixChunk)
    {
        Mix_FreeChunk(mixChunk);
        if(mixChunk == NULL)
            return true;
        else
            return false;
    }

    int DLL_EXPORT playSound(Mix_Chunk* sound, int loop)
    {
        int channel = Mix_PlayChannel(-1,sound,loop);

    }

    void DLL_EXPORT delaySound(int time)
    {
        SDL_Delay(time);
    }

    void DLL_EXPORT pauseSound(int channel)
    {
        Mix_Pause(channel);
    }

    void DLL_EXPORT resumeSound(int channel)
    {
        Mix_Resume(channel);
    }

    void DLL_EXPORT haltSound(int channel)
    {
        Mix_HaltChannel(channel);
    }










}
