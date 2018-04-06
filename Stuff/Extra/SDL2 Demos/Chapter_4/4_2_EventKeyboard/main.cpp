#include <SDL2/SDL.h>

SDL_Surface* Background = NULL;
SDL_Surface* SpriteImage = NULL;
SDL_Surface* Backbuffer = NULL;

//This is a handle to a window in SDL 2
SDL_Window* Window = NULL;

int SpriteX = 350;
int SpriteY = 250;

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
    Window = SDL_CreateWindow("Use the arrow keys to move the sprite around and ESC to exit.",
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
        DrawImage(Background,Backbuffer, 0, 0);
        DrawImage(SpriteImage, Backbuffer, SpriteX, SpriteY);

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

        if( event.type == SDL_KEYDOWN )
        {
            switch( event.key.keysym.sym )
            {
                case SDLK_ESCAPE:
                    running = false;
                    break;

                case SDLK_LEFT:
                    SpriteX-=50;
                    break;

                case SDLK_RIGHT:
                    SpriteX+=50;
                    break;

                case SDLK_UP:
                    SpriteY-=50;
                    break;

                case SDLK_DOWN:
                    SpriteY+=50;
                    break;

                default:
                    break;
            }
        }
    }

    return running;
}

bool LoadFiles()
{
    SpriteImage = LoadImage("graphics/spaceship.bmp");

    if(SpriteImage == NULL)
        return false;

    Background = LoadImage("graphics/background.bmp");

    if(Background == NULL)
        return false;

    return true;

}

void FreeFiles()
{
    if(SpriteImage != NULL)
    {
        SDL_FreeSurface(SpriteImage);
        SpriteImage = NULL;
    }

    if(Background != NULL)
    {
        SDL_FreeSurface(Background);
        Background = NULL;
    }
}
