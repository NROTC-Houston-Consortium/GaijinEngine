#ifndef __GAIJINENGINERENDERER_H__
#define __GAIJINENGINERENDERER_H__

#include <windows.h>
#include <SDL/SDL.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */


#define DLL_EXPORT __declspec(dllexport)


#ifdef __cplusplus
extern "C"
{
#endif

namespace surfaceRenderer
{
    bool DLL_EXPORT freeSurface(SDL_Surface* surface);
    bool DLL_EXPORT loadSprite(SDL_Surface* surface, char* imageName);





}


#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__

