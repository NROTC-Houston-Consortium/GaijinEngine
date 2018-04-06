#include <SDL2/SDL.h>
#include <cstdlib>

SDL_Surface* Backbuffer = NULL;

//This is a handle to a window in SDL 2
SDL_Window* Window = NULL;

bool ProgramIsRunning();
void DrawPixel(SDL_Surface *surface, int x, int y, Uint8 r, Uint8 g, Uint8 b);

int main(int argc, char* args[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        //This is a nice alternative to printf in SDL 2
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SDL!!!", "SDL failed to initialize!", NULL);
        SDL_Quit();
        return 0;
    }

    //In SDL 2, SDL_SetVideoMode has been removed, we now create windows using SDL_CreateWindow to create windows
    Window = SDL_CreateWindow("Why can't I hold all these pixels?", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    //SDL_GetWindowSurface gets the backbuffer of the window we created with SDL_CreateWindow
    Backbuffer = SDL_GetWindowSurface(Window);

    while(ProgramIsRunning())
    {

        for(int i = 0; i < 100*8*600; i++)
        {
            DrawPixel(Backbuffer, rand()%800, rand()%600, rand()%255, rand()%255, rand()%255);
        }

        SDL_Delay(16);

        //In SDL 2, SDL_UpdateWindowSurface replaces SDL_Flip
        SDL_UpdateWindowSurface(Window);
    }

    //SDL_DestroyWindow destroys a window we created with SDL_CreateWindow
    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 0;
}

bool ProgramIsRunning()
{
    SDL_Event event;

    bool running = true;

    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            running = false;
    }

    return running;
}

void DrawPixel(SDL_Surface *surface, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    if(SDL_MUSTLOCK(surface))
    {
        if(SDL_LockSurface(surface) < 0)
            return;
    }

    if(x >= surface->w || x < 0 || y >= surface->h || y < 0)
        return;

    Uint32 *buffer;
    Uint32 color;

    color = SDL_MapRGB(surface->format, r, g, b);

    buffer = (Uint32*)surface->pixels  + y*surface->pitch/4 + x;
    (*buffer) = color;

    if(SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);
}
