#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

SDL_Surface* Background = NULL;
SDL_Surface* Backbuffer = NULL;

//This is a handle to a window in SDL 2
SDL_Window* Window = NULL;

Mix_Chunk *cNote = NULL;
Mix_Chunk *csNote = NULL;
Mix_Chunk *dNote = NULL;
Mix_Chunk *dsNote = NULL;
Mix_Chunk *eNote = NULL;
Mix_Chunk *fNote = NULL;
Mix_Chunk *fsNote = NULL;
Mix_Chunk *gNote = NULL;
Mix_Chunk *gsNote = NULL;
Mix_Chunk *aNote = NULL;
Mix_Chunk *asNote = NULL;
Mix_Chunk *bNote = NULL;
Mix_Chunk *highCNote = NULL;

int noteChannel[13];

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
    Window = SDL_CreateWindow("Try pressing: AAGGHHG FFDDSSA",
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

    for(int i = 0; i < 13; i++)
    {
        noteChannel[i] = -1;
    }

    while(ProgramIsRunning())
    {
        DrawImage(Background,Backbuffer, 0, 0);

        SDL_Delay(20);

        //In SDL 2, SDL_UpdateWindowSurface replaces SDL_Flip
        SDL_UpdateWindowSurface(Window);
    }

    FreeFiles();

    //SDL_DestroyWindow destroys a window we created with SDL_CreateWindow
    SDL_DestroyWindow(Window);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
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

                case SDLK_a:
                    noteChannel[0] = Mix_PlayChannel(-1, cNote, 0);
                    break;

                case SDLK_w:
                    noteChannel[1] = Mix_PlayChannel(-1, csNote, 0);
                    break;

                case SDLK_s:
                    noteChannel[2] = Mix_PlayChannel(-1, dNote, 0);
                    break;

                case SDLK_e:
                    noteChannel[3] = Mix_PlayChannel(-1, dsNote, 0);
                    break;

                case SDLK_d:
                    noteChannel[4] = Mix_PlayChannel(-1, eNote, 0);
                    break;

                case SDLK_f:
                    noteChannel[5] = Mix_PlayChannel(-1, fNote, 0);
                    break;

                case SDLK_t:
                    noteChannel[6] = Mix_PlayChannel(-1, fsNote, 0);
                    break;

                case SDLK_g:
                    noteChannel[7] = Mix_PlayChannel(-1, gNote, 0);
                    break;

                case SDLK_y:
                    noteChannel[8] = Mix_PlayChannel(-1, gsNote, 0);
                    break;

                case SDLK_h:
                    noteChannel[9] = Mix_PlayChannel(-1, aNote, 0);
                    break;

                case SDLK_u:
                    noteChannel[10] = Mix_PlayChannel(-1, asNote, 0);
                    break;

                case SDLK_j:
                    noteChannel[11] = Mix_PlayChannel(-1, bNote, 0);
                    break;

                case SDLK_k:
                    noteChannel[12] = Mix_PlayChannel(-1, highCNote, 0);
                    break;

                default:
                    break;
            }
        }

        if(event.type == SDL_KEYUP )
        {
            switch(event.key.keysym.sym )
            {
                case SDLK_ESCAPE:
                    running = false;
                    break;

                case SDLK_a:
                    Mix_HaltChannel(noteChannel[0]);
                    break;

                case SDLK_w:
                    Mix_HaltChannel(noteChannel[1]);
                    break;

                case SDLK_s:
                    Mix_HaltChannel(noteChannel[2]);
                    break;

                case SDLK_e:
                    Mix_HaltChannel(noteChannel[3]);
                    break;

                case SDLK_d:
                    Mix_HaltChannel(noteChannel[4]);
                    break;

                case SDLK_f:
                    Mix_HaltChannel(noteChannel[5]);
                    break;

                case SDLK_t:
                    Mix_HaltChannel(noteChannel[6]);
                    break;

                case SDLK_g:
                    Mix_HaltChannel(noteChannel[7]);
                    break;

                case SDLK_y:
                    Mix_HaltChannel(noteChannel[8]);
                    break;

                case SDLK_h:
                    Mix_HaltChannel(noteChannel[9]);
                    break;

                case SDLK_u:
                    Mix_HaltChannel(noteChannel[10]);
                    break;

                case SDLK_j:
                    Mix_HaltChannel(noteChannel[11]);
                    break;

                case SDLK_k:
                    Mix_HaltChannel(noteChannel[12]);
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
    Background = LoadImage("graphics/background.bmp");

    cNote = Mix_LoadWAV("notes/c.wav" );
    csNote = Mix_LoadWAV("notes/cs.wav" );
    dNote = Mix_LoadWAV("notes/d.wav" );
    dsNote = Mix_LoadWAV("notes/ds.wav" );
    eNote = Mix_LoadWAV("notes/e.wav" );
    fNote = Mix_LoadWAV("notes/f.wav" );
    fsNote = Mix_LoadWAV("notes/fs.wav" );
    gNote = Mix_LoadWAV("notes/g.wav" );
    gsNote = Mix_LoadWAV("notes/gs.wav" );
    aNote = Mix_LoadWAV("notes/a.wav" );
    asNote = Mix_LoadWAV("notes/as.wav" );
    bNote = Mix_LoadWAV("notes/b.wav" );
    highCNote = Mix_LoadWAV("notes/highC.wav" );

    if(Background == NULL || cNote == NULL || csNote == NULL || dNote == NULL || dsNote == NULL || eNote == NULL || fNote == NULL || fsNote == NULL || gNote == NULL || gsNote == NULL || aNote == NULL || asNote == NULL || bNote == NULL || highCNote == NULL)
    {
        return false;
    }

    return true;
}

void FreeFiles()
{
    if(cNote != NULL)
    {
        Mix_FreeChunk(cNote);
        cNote = NULL;
    }

    if(csNote != NULL)
    {
        Mix_FreeChunk(csNote);
        csNote = NULL;
    }

    if(dNote != NULL)
    {
        Mix_FreeChunk(dNote);
        dNote = NULL;
    }

    if(dsNote != NULL)
    {
        Mix_FreeChunk(dsNote);
        dsNote = NULL;
    }

    if(eNote != NULL)
    {
        Mix_FreeChunk(eNote);
        eNote = NULL;
    }

    if(fNote != NULL)
    {
        Mix_FreeChunk(fNote);
        fNote = NULL;
    }

    if(fsNote != NULL)
    {
        Mix_FreeChunk(fsNote);
        fsNote = NULL;
    }

    if(gNote != NULL)
    {
        Mix_FreeChunk(gNote);
        gNote = NULL;
    }

    if(gsNote != NULL)
    {
        Mix_FreeChunk(gsNote);
        gsNote = NULL;
    }

    if(aNote != NULL)
    {
        Mix_FreeChunk(aNote);
        aNote = NULL;
    }

    if(asNote != NULL)
    {
        Mix_FreeChunk(asNote);
        asNote = NULL;
    }

    if(bNote != NULL)
    {
        Mix_FreeChunk(bNote);
        bNote = NULL;
    }

    if(highCNote != NULL)
    {
        Mix_FreeChunk(highCNote);
        highCNote = NULL;
    }

    if(Background != NULL)
    {
        SDL_FreeSurface(Background);
        Background = NULL;
    }
}
