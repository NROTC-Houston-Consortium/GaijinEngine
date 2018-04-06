//Include the SDL 2 header file
#include <SDL2/SDL.h>
#include <cstdlib>

//Setup variables
SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

bool InitSDL();
void CleanUp();
void DrawScreen();

int main(int args, char* argvs[])
{
    bool isRunning = true;

    if(!InitSDL())
    {
        CleanUp();
        return false;
    }

    //The game loop
    while(isRunning)
    {
        //Check if the user pressed the exit button
        SDL_Event event;

        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        //Draw The Screen
        DrawScreen();
    }

    //Clean Everything up :)
    CleanUp();

    return 1;
}

bool InitSDL()
{
    //Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return false;
    }

    //Create the window
    Window = SDL_CreateWindow("SDL 2 Primitives!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    //Error Checking
    if(Window == NULL)
    {
        return false;
    }

    //This creates our rendering device, which we use now to handle graphics for us.
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(Renderer == NULL)
    {
        return false;
    }

    return true;
}

void CleanUp()
{
    //We have to clean up the renderer when we're done with it
    SDL_DestroyRenderer(Renderer);

    //Clean up the window
    SDL_DestroyWindow(Window);

    //And quit :)
    SDL_Quit();
}

void DrawScreen()
{
    //Clear the screen
    SDL_SetRenderDrawColor(Renderer, 255, 255, 250, 255);
    SDL_RenderClear(Renderer);

    //Draw 10 rectangles accross the screen
    SDL_SetRenderDrawColor(Renderer, 100, 200, 87, 255);

    for(int i = 0; i < 10; i++)
    {
        SDL_Rect rect;

        rect.x = 80*i + 10;
        rect.y = 10;
        rect.w = 7*i;
        rect.h = 7*i;

        SDL_RenderDrawRect(Renderer, &rect);
    }

    //Fill 10 Rectangles accross the Screen
    SDL_SetRenderDrawColor(Renderer, 255, 80, 50, 255);

    for(int i = 0; i < 10; i++)
    {
        SDL_Rect rect;

        rect.x = 80*i + 10;
        rect.y = 90;
        rect.w = 7*i;
        rect.h = 7*i;

        SDL_RenderFillRect(Renderer, &rect);
    }

    //Draw 10 lines across the screen
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);

    for(int i = 0; i < 10; i++)
    {
        int x1 = i*80 + 10;
        int y1 = 170;
        int x2 = i*87 + 10;
        int y2 = 240;

        SDL_RenderDrawLine(Renderer, x1, y1, x2, y2);
    }

    for(int i = 0; i < 8000; i++)
    {
        int x = i/10;
        int y = 250 + rand()%20;

        SDL_SetRenderDrawColor(Renderer, i%255, (x*x)%255, y%255, 255);

        SDL_RenderDrawPoint(Renderer, x, y);
    }

    //Draw the screen.  This replaces SDL_Flip in SDL 1.2 and SDL_UpdateWindowSurface
    //in SDL 2 if we weren't working with a rendering context
    SDL_RenderPresent(Renderer);
}
