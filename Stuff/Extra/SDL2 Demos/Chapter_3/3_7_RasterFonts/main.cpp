#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cstring>

SDL_Surface* Background = NULL;
SDL_Surface* FontImage = NULL;
SDL_Surface* Backbuffer = NULL;

//This is a handle to a window in SDL 2
SDL_Window* Window;

const int charSize = 16;

SDL_Surface* LoadImage(char* fileName);
bool LoadFiles();
void FreeFiles();
void DrawImage(SDL_Surface* image, SDL_Surface* destSurface, int x, int y);
void DrawImageFrame(SDL_Surface* image, SDL_Surface* destSurface, int x, int y, int width, int height, int frame);
void DrawRasterText(SDL_Surface* surface, SDL_Surface* destSurface, char string[], int x, int y, int charSize);
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
    Window = SDL_CreateWindow("I can talk!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

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
        DrawImage(Background,Backbuffer, 0, 0);
        DrawRasterText(FontImage, Backbuffer, "All Systems Go!" , 100, 100, charSize);
        DrawRasterText(FontImage, Backbuffer, "Drawing Fonts is Fun!", 100, 116, charSize);

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

SDL_Surface* LoadImage(char* fileName)
{
    SDL_Surface* imageLoaded = NULL;
    SDL_Surface* processedImage = NULL;

    imageLoaded = IMG_Load(fileName);

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

bool LoadFiles()
{
    Background = LoadImage("graphics/background.bmp");

    if(Background == NULL)
        return false;

    FontImage = LoadImage("graphics/blocky_font.bmp");

    if(FontImage == NULL)
        return false;

    return true;
}

void FreeFiles()
{
    SDL_FreeSurface(FontImage);
    SDL_FreeSurface(Background);
}

void DrawImage(SDL_Surface* image, SDL_Surface* destSurface, int x, int y)
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;

    SDL_BlitSurface(image, NULL, destSurface, &destRect);
}

void DrawImageFrame(SDL_Surface* image, SDL_Surface* destSurface, int x, int y, int width, int height, int frame)
{
    //Draws a specific frame from an image
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;

    int columns = image->w/width;

    SDL_Rect sourceRect;
    sourceRect.y = (frame/columns)*height;
    sourceRect.x = (frame%columns)*width;
    sourceRect.w = width;
    sourceRect.h = height;

    SDL_BlitSurface(image, &sourceRect, destSurface, &destRect);
}

void DrawRasterText(SDL_Surface* surface, SDL_Surface* destSurface, char string[], int x, int y, int charSize)
{
    for(int i = 0; i < strlen(string); i++)
        DrawImageFrame(surface, destSurface, x+i*charSize, y, charSize, charSize, string[i]-32);
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
