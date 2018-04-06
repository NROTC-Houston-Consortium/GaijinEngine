#include <SDL2/SDL.h>

int main(int argc, char* args[])
{
    //This is new in SDL2, and it is the handle to a window
    SDL_Window* window = NULL;

    if(SDL_Init( SDL_INIT_EVERYTHING) < 0)
    {
        //This is a nice alternative to printf in SDL 2
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SDL", "SDL failed to initialize!", NULL);
        SDL_Quit();
        return 0;
    }

    //SDL_SetVideoMode is gone in SDL 2 to make way for multiple window support.  Now, we use SDL_CreateWindow to make
    //our windows.
    window = SDL_CreateWindow("SDL!!!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    SDL_Delay(3000);

    //In SDL 2, we have to actually destroy the windows we created by calling SDL_DestroyWindow
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}
