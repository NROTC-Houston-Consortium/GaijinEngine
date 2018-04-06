#include <SDL2/SDL.h>

SDL_Surface* Background = NULL;
SDL_Surface* SpriteImage = NULL;
SDL_Surface* Backbuffer = NULL;

//This is a handle to a window in SDL 2
SDL_Window* Window = NULL;

SDL_Rect SpritePos;

bool LoadFiles();
void FreeFiles();
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
    Window = SDL_CreateWindow("Moving Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    //SDL_GetWindowSurface gets the backbuffer of the window we created with SDL_CreateWindow
    Backbuffer = SDL_GetWindowSurface(Window);

    if(!LoadFiles())
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SDL!!!", "Failed to load files!", NULL);

        //SDL_DestroyWindow destroys a window we created with SDL_CreateWindow
        SDL_DestroyWindow(Window);
        FreeFiles();
        SDL_Quit();

        return 0;
    }

    SpritePos.x = 0;
    SpritePos.y = 250;

    while(ProgramIsRunning())
    {
        SpritePos.x+=5;

        if(SpritePos.x > 800)
            SpritePos.x = -200;

        SDL_BlitSurface(Background, NULL, Backbuffer, NULL);
        SDL_BlitSurface(SpriteImage, NULL, Backbuffer, &SpritePos);

        SDL_Delay(20);

        //In SDL 2, SDL_UpdateWindowSurface replaces SDL_Flip
        SDL_UpdateWindowSurface(Window);
    }

    FreeFiles();

    //SDL_DestroyWindow destroys a window we created with SDL_CreateWindow
    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 0;
}

bool LoadFiles()
{
    Background = SDL_LoadBMP("graphics/background.bmp");
    if(Background == NULL)
        return false;

    SpriteImage = SDL_LoadBMP("graphics/spaceship.bmp");

    if(SpriteImage == NULL)
        return false;

    return true;
}

void FreeFiles()
{
    SDL_FreeSurface(Background);
    SDL_FreeSurface(SpriteImage);
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
