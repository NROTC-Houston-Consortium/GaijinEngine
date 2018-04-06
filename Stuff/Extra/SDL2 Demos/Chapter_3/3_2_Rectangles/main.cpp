#include <SDL2/SDL.h>
#include <cstdlib>

SDL_Surface* Backbuffer = NULL;

//This is a handle to a window in SDL 2
SDL_Window* Window = NULL;

void DrawRect(SDL_Surface* surface, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b);
void FillRect(SDL_Surface* surface, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b);
bool ProgramIsRunning();

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
    Window = SDL_CreateWindow("Rectangle, rectangles, and more rectangles!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    //SDL_GetWindowSurface gets the backbuffer of the window we created with SDL_CreateWindow
    Backbuffer = SDL_GetWindowSurface(Window);

    while(ProgramIsRunning())
    {
        DrawRect(Backbuffer, rand()%800, rand()%600, rand()%200, rand()%200, rand()%255, rand()%255, rand()%255);
        FillRect(Backbuffer, rand()%800, rand()%600, rand()%200, rand()%200, rand()%255, rand()%255, rand()%255);

        SDL_Delay(20);

        //In SDL 2, SDL_UpdateWindowSurface replaces SDL_Flip
        SDL_UpdateWindowSurface(Window);
    }

    //SDL_DestroyWindow destroys a window we created with SDL_CreateWindow
    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 0;
}

void DrawRect(SDL_Surface* surface, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b)
{
    FillRect(surface, x, y, width, 1, r, g, b);
    FillRect(surface, x, y+height-1, width, 1, r, g, b);
    FillRect(surface, x, y, 1, height, r, g, b);
    FillRect(surface, x+width-1, y, 1, height, r, g, b);
}

void FillRect(SDL_Surface* surface, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b)
{
    Uint32 color;

    color = SDL_MapRGB(surface->format, r, g, b);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_FillRect(surface, &rect, color);
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
