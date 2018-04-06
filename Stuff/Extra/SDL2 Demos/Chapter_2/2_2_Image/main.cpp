#include <SDL2/SDL.h>

SDL_Surface* Image = NULL;
SDL_Surface* Backbuffer = NULL;

//This is a handle to a window in SDL 2
SDL_Window* Window = NULL;

int main(int argc, char* args[])
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        //This is a nice alternative to printf in SDL 2
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SDL", "SDL failed to initialize!", NULL);
        SDL_Quit();
        return 0;
    }

    //In SDL 2, SDL_SetVideoMode has been removed, we now create windows using SDL_CreateWindow to create windows
    Window = SDL_CreateWindow("SDL!!!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    //SDL_GetWindowSurface gets the backbuffer of the window we created with SDL_CreateWindow
    Backbuffer = SDL_GetWindowSurface(Window);

    //Load the image
    Image = SDL_LoadBMP("graphics/image.bmp" );

    if(Image == NULL)
    {
        //This is a nice alternative to printf in SDL 2
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SDL", "Image failed to load!", NULL);

        //SDL_DestroyWindow destroys a window we created with SDL_CreateWindow
        SDL_DestroyWindow(Window);
        SDL_Quit();
        return 0;
    }

    //Draw the image
    SDL_BlitSurface(Image, NULL, Backbuffer, NULL );

    //In SDL 2, SDL_UpdateWindowSurface replaces SDL_Flip
    SDL_UpdateWindowSurface(Window);

    //Wait
    SDL_Delay(3000);

    //Finish Up

    //SDL_DestroyWindow destroys a window we created with SDL_CreateWindow
    SDL_DestroyWindow(Window);
    SDL_FreeSurface(Image);
    SDL_Quit();

    return 1;
}
