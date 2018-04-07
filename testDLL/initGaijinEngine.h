#ifndef __INITGAIJINENGINE_H__
#define __INITGAIJINENGINE_H__
#include <windows.h>
#include<SDL/SDL.h>
#include<string>
#include<iostream>

/*  To use this exported function of dll, include this header
 *  in your project.
 */


#define DLL_EXPORT __declspec(dllexport)


#ifdef __cplusplus
extern "C"
{
#endif
namespace initFunc
{
    bool DLL_EXPORT initSDL();
    void DLL_EXPORT initDebug(char* str);
    char* DLL_EXPORT initDateTime();
    void DLL_EXPORT initSDLQuit();
    SDL_Surface* DLL_EXPORT initCreateWindow(int width, int height, int colorMap);
    void DLL_EXPORT initSetCaption(char* windowName, char* minimizedName);

}

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
