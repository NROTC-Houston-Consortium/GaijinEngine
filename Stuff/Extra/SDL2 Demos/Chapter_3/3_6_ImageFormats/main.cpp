#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface* PngLogo = NULL;
SDL_Surface* JpegLogo = NULL;
SDL_Surface* PcxLogo = NULL;
SDL_Surface* TgaLogo = NULL;
SDL_Surface* Backbuffer = NULL;

//This is a handle to a window in SDL 2
SDL_Window* Window;

SDL_Surface* LoadImage(char* fileName);
void DrawImage(SDL_Surface* image, SDL_Surface* destSurface, int x, int y);
bool LoadFiles();
void FreeFiles();
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
    Window = SDL_CreateWindow("I bet you can't tell the difference ;)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

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
        DrawImage(PngLogo, Backbuffer, 0,0);
        DrawImage(JpegLogo, Backbuffer, 400,0);
        DrawImage(PcxLogo, Backbuffer, 0,300);
        DrawImage(TgaLogo, Backbuffer, 400,300);

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

void DrawImage(SDL_Surface* image, SDL_Surface* destSurface, int x, int y)
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;

    SDL_BlitSurface(image, NULL, destSurface, &destRect);
}

bool LoadFiles()
{
    PngLogo = LoadImage("graphics/png_logo.png");
    JpegLogo = LoadImage("graphics/jpeg_logo.jpg");
    PcxLogo = LoadImage("graphics/pcx_logo.pcx");
    TgaLogo = LoadImage("graphics/tga_logo.tga");

    if(PngLogo == NULL || JpegLogo == NULL || PcxLogo == NULL || TgaLogo == NULL)
        return false;

    return true;
}

void FreeFiles()
{
    SDL_FreeSurface(PngLogo);
    SDL_FreeSurface(JpegLogo);
    SDL_FreeSurface(PcxLogo);
    SDL_FreeSurface(TgaLogo);
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
