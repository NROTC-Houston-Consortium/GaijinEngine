#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Mix_Music *Music = NULL;

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
    Window = SDL_CreateWindow("La La La La La La Da Da Da Da Da Da",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    //SDL_GetWindowSurface gets the backbuffer of the window we created with SDL_CreateWindow
    Backbuffer = SDL_GetWindowSurface(Window);

    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1 )
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SDL", "Failed to open audio device!", NULL);

        //SDL_DestroyWindow destroys a window we created with SDL_CreateWindow
        SDL_DestroyWindow(Window);
        SDL_Quit();
        return 0;
    }

    if(!LoadFiles())
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SDL", "Failed to load files!", NULL);

        //SDL_DestroyWindow destroys a window we created with SDL_CreateWindow
        SDL_DestroyWindow(Window);
        FreeFiles();
        Mix_CloseAudio();
        SDL_Quit();
        return 0;
    }

    while(ProgramIsRunning())
    {
        DrawImage(Background,Backbuffer, 0, 0);

        SDL_Delay(20);

        //In SDL 2, SDL_UpdateWindowSurface replaces SDL_Flip
        SDL_UpdateWindowSurface(Window);
    }

    FreeFiles();

    Mix_CloseAudio();
    SDL_Quit();

    return 1;
}

bool LoadFiles()
{
    Background = LoadImage("graphics/background.bmp");

    if(Background == NULL)
        return false;

    Music = Mix_LoadMUS("audio/happy_song.ogg");

    if(Music == NULL)
        return false;

    return true;
}

void FreeFiles()
{
    if(Background != NULL)
    {
        SDL_FreeSurface(Background);
        Background = NULL;
    }

    if(Music != NULL)
    {
        Mix_FreeMusic(Music);
        Music = NULL;
    }
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

    SDL_BlitSurface(image, NULL, destSurface, &destRect);
}

bool ProgramIsRunning()
{
    SDL_Event event;

    bool running = true;

    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            running = false;

        if(event.type == SDL_KEYDOWN )
        {
            switch(event.key.keysym.sym )
            {
                case SDLK_ESCAPE:
                    running = false;
                    break;

                case SDLK_BACKSPACE:
                    Mix_HaltMusic();
                    break;

                case SDLK_SPACE:
                    if(!Mix_PlayingMusic())
                    {
                        Mix_PlayMusic(Music, -1);
                    }
                    else
                    {
                        if(Mix_PausedMusic())
                        {
                            Mix_ResumeMusic();
                        }
                        else
                        {
                            Mix_PauseMusic();
                        }
                    }
                    break;

                default:
                    break;
            }
        }
    }

    return running;
}
