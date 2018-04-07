#ifndef __GAIJINENGINEAUDIO_H__
#define __GAIJINENGINEAUDIO_H__

#include <windows.h>
#include<SDL/SDL.h>
#include<SDL/SDL_mixer.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#define DLL_EXPORT __declspec(dllexport)



#ifdef __cplusplus
extern "C"
{
#endif
namespace Audio
{
    void DLL_EXPORT audioDebug(char* name);
    bool DLL_EXPORT initAudio(int freq, Uint16 format,int channels, int chunkSize);
    void DLL_EXPORT close();
    void DLL_EXPORT loadSound(char* fileName);
    bool DLL_EXPORT freeSound(Mix_Chunk* mixChunk);
    int DLL_EXPORT playSound(Mix_Chunk* sound, int loop);
    void DLL_EXPORT delaySound(int time);
    void DLL_EXPORT pauseSound(int channel);
    void DLL_EXPORT resumeSound(int channel);
    void DLL_EXPORT haltSound(int channel);





}



#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__

