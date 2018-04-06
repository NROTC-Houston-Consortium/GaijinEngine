#include <SDL2/SDL.h>
#include <stdio.h>

int Cross1X = -100;
int Cross1Y = -100;
int Cross2X = -100;
int Cross2Y = -100;

SDL_Surface* Cross1 = NULL;
SDL_Surface* Cross2 = NULL;
SDL_Surface* Background = NULL;
SDL_Surface* Backbuffer = NULL;

//This is a handle to a window in SDL 2
SDL_Window* Window = NULL;

bool LoadFiles();
void FreeFiles();

SDL_Surface* LoadImage(char* fileName);
void DrawImage(SDL_Surface* image, SDL_Surface* destSurface, int x, int y);
bool ProgramIsRunning();

int main(int argc, char* args[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        //This is a nice alternative to printf in SDL 2
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SDL", "SDL failed to initialize!", NULL);
        SDL_Quit();
        return 0;
    }

    //In SDL 2, SDL_SetVideoMode has been removed, we now create windows using SDL_CreateWindow to create windows
    Window = SDL_CreateWindow("What a drag...",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    //SDL_GetWindowSurface gets the backbuffer of the window we created with SDL_CreateWindow
    Backbuffer = SDL_GetWindowSurface(Window);

    if(!LoadFiles())
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SDL", "Failed to load files!", NULL);

        //SDL_DestroyWindow destroys a window we created with SDL_CreateWindow
        SDL_DestroyWindow(Window);
        FreeFiles();
        SDL_Quit();

        return 0;
    }

    while(ProgramIsRunning())
    {
        int mouseX;
        int mouseY;

        SDL_GetMouseState(&mouseX, &mouseY);

        char buffer[64];
        sprintf(buffer, "Mouse X: %d, Mouse Y: %d", mouseX, mouseY);

        //In SDL 2, use SDL_SetWindowTitle instead of SDL_WM_Caption
        SDL_SetWindowTitle(Window, buffer);

        //Process Buttons;
        if(SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(1))
        {
            Cross1X = mouseX;
            Cross1Y = mouseY;
        }

        if(SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(3))
        {
            Cross2X = mouseX;
            Cross2Y = mouseY;
        }

        DrawImage(Background, Backbuffer, 0, 0);
        DrawImage(Cross1, Backbuffer, Cross1X - 50, Cross1Y - 50);
        DrawImage(Cross2, Backbuffer, Cross2X - 50, Cross2Y - 50);

        SDL_Delay(20);

        //In SDL 2, SDL_UpdateWindowSurface replaces SDL_Flip
        SDL_UpdateWindowSurface(Window);
    }

    FreeFiles();

    //SDL_DestroyWindow destroys a window we created with SDL_CreateWindow
    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 1;
}

SDL_Surface* LoadImage(char* fileName)
{
    SDL_Surface* imageLoaded = NULL;
    SDL_Surface* processedImage = NULL;

    imageLoaded = SDL_LoadBMP(fileName);

    if(imageLoaded != NULL)
    {
        //SDL_DisplayFormat is gone in SDL 2, we can use SDL_ConvertSurface instead
        processedImage = SDL_ConvertSurface(imageLoaded, Backbuffer->format, 0);
        SDL_FreeSurface(imageLoaded);

        if(processedImage != NULL)
        {
            Uint32 colorKey = SDL_MapRGB(processedImage->format, 0xFF, 0, 0xFF);

            //SDL_SRCCOLORKEY is gone in SDL 2, use SDL_TRUE instead
            SDL_SetColorKey(processedImage, SDL_TRUE, colorKey);
        }

    }

    return processedImage;
}

void DrawImage(SDL_Surface* image, SDL_Surface* destSurface, int x, int y)
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;

    SDL_BlitSurface( image, NULL, destSurface, &destRect);
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

bool LoadFiles()
{
    Cross1 = LoadImage("graphics/cross_1.bmp");

    if(Cross1 == NULL)
        return false;

    Cross2 = LoadImage("graphics/cross_2.bmp");

    if(Cross2 == NULL)
        return false;

    Background = LoadImage("graphics/Background.bmp");

    if(Background == NULL)
        return false;

    return true;

}

void FreeFiles()
{
    if(Cross1 != NULL)
    {
        SDL_FreeSurface(Cross1);
        Cross1 = NULL;
    }

    if(Cross2 != NULL)
    {
        SDL_FreeSurface(Cross2);
        Cross2 = NULL;
    }

    if(Background != NULL)
    {
        SDL_FreeSurface(Background);
        Background = NULL;
    }
}
