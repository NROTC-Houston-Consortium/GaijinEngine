//Include the SDL 2 header file
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <cstdlib>

//Setup variables
const int CLIENT_WIDTH = 800;
const int CLIENT_HEIGHT = 600;

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

//These are like surfaces, but they work with the
//renderer and are more flexible in some regards
SDL_Texture* Background = NULL;

//These variables help manipulate the graphics

SDL_Rect MonsterSourceRect;
SDL_Rect MonsterDestRect;

const int MONSTER_MAX_WIDTH = 600;
const int MONSTER_MAX_HEIGHT = 531;
const int MONSTER_MIN_WIDTH = 150;
const int MONSTER_MIN_HEIGHT = 133;
const int TOTAL_MONSTER_FRAMES = 20;
const int MONSTER_WALK_FRONT_START = 0;
const int MONSTER_WALK_BACK_START = 10;
const int MONSTER_WALK_FRONT_END = 10;
const int MONSTER_WALK_BACK_END = 20;

int MonsterFrameDelay = 3;
int MonsterFrame;
int MonsterFrameDelayCounter = 0;
int MonsterAnimBegin = MONSTER_WALK_FRONT_START;
int MonsterAnimEnd = MONSTER_WALK_FRONT_END;
bool MonsterWalkingForward = true;
int MonsterDistance = 200;

//This array will hold the monster's frames.  Since the monster sprite is
//large, it is more convenient to keep as separate images rather than a giant
//spritesheet.

SDL_Texture* MonsterSprite[20];

bool InitSDL();
void CleanUp();
void UpdateGame();
void DrawScreen();

//This is a helper function for loading textures
SDL_Texture* LoadTexture(char* filename);

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

        //Update the Game
        UpdateGame();

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
    Window = SDL_CreateWindow("No 3D rendering here.  Really!  Check the code ;)",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              CLIENT_WIDTH, CLIENT_HEIGHT, SDL_WINDOW_SHOWN);

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

    //Load Files
    Background = LoadTexture("graphics/background.bmp");

    for(int i = 0; i < 10; i++)
    {
        char buffer[128];

        if(i < 9)
            sprintf(buffer, "graphics/monster/monster-front-0%d.png", i+1);
        else
            sprintf(buffer, "graphics/monster/monster-front-%d.png", i+1);

        MonsterSprite[i] = LoadTexture(buffer);

        if(MonsterSprite[i] == NULL)
            return false;
    }

    for(int i = 0; i < 10; i++)
    {
        char buffer[128];

        if(i < 9)
            sprintf(buffer, "graphics/monster/monster-back-0%d.png", i+1);
        else
            sprintf(buffer, "graphics/monster/monster-back-%d.png", i+1);

        MonsterSprite[MONSTER_WALK_BACK_START + i] = LoadTexture(buffer);

        if(MonsterSprite[MONSTER_WALK_BACK_START + i] == NULL)
            return false;
    }

    if(Background == NULL)
        return false;

    MonsterSourceRect.w = 150;
    MonsterSourceRect.h = 120;
    MonsterSourceRect.x = 0;
    MonsterSourceRect.y = 0;

    return true;
}

void CleanUp()
{
    SDL_DestroyTexture(Background);

    for(int i = 0; i < TOTAL_MONSTER_FRAMES; i++)
    {
        SDL_DestroyTexture(MonsterSprite[i]);
    }

    //We have to clean up the renderer when we're done with it
    SDL_DestroyRenderer(Renderer);

    //Clean up the window
    SDL_DestroyWindow(Window);

    //And quit :)
    SDL_Quit();
}

void UpdateGame()
{
    MonsterFrameDelayCounter++;

    if(MonsterFrameDelayCounter > MonsterFrameDelay)
    {
        MonsterFrame++;
        MonsterFrameDelayCounter = 0;
    }

    if(MonsterFrame >= MonsterAnimEnd)
    {
        MonsterFrame = MonsterAnimBegin;
    }

    if(MonsterWalkingForward)
    {
        MonsterDistance--;
    }
    else
    {
        MonsterDistance++;
    }

    if(MonsterDistance < 10)
    {
        MonsterWalkingForward = false;
        MonsterAnimBegin = MONSTER_WALK_BACK_START;
        MonsterAnimEnd = MONSTER_WALK_BACK_END;
    }

    if(MonsterDistance > 200)
    {
        MonsterWalkingForward = true;
        MonsterAnimBegin = MONSTER_WALK_FRONT_START;
        MonsterAnimEnd = MONSTER_WALK_FRONT_END;
    }

    float StretchFactor = float(200-MonsterDistance)/200;
    StretchFactor*=StretchFactor;

    MonsterDestRect.w = MONSTER_MIN_WIDTH + StretchFactor*(MONSTER_MAX_WIDTH - MONSTER_MIN_WIDTH);
    MonsterDestRect.h = MONSTER_MIN_HEIGHT + StretchFactor*(MONSTER_MAX_HEIGHT - MONSTER_MIN_HEIGHT);
    MonsterDestRect.x = CLIENT_WIDTH/2 - MonsterDestRect.w/2;
    MonsterDestRect.y = 50+CLIENT_HEIGHT/2 - MonsterDestRect.h/2;
}

void DrawScreen()
{
    //Clear the screen
    SDL_SetRenderDrawColor(Renderer, 255, 255, 250, 255);
    SDL_RenderClear(Renderer);

    //Draw the background on the entire screen
    SDL_RenderCopy(Renderer, Background, NULL, NULL);

    //Draw the monster
    SDL_RenderCopy(Renderer, MonsterSprite[MonsterFrame], NULL, &MonsterDestRect);

    //Draw the screen.  This replaces SDL_Flip in SDL 1.2 and SDL_UpdateWindowSurface
    //in SDL 2 if we weren't working with a rendering context
    SDL_RenderPresent(Renderer);
}

SDL_Texture* LoadTexture(char* filename)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = NULL;

    surface = IMG_Load(filename);

    if(surface != NULL)
    {
        //Let's color key the surface
        Uint32 colorKey = SDL_MapRGB(surface->format, 255, 0, 255);
        SDL_SetColorKey(surface, SDL_TRUE, colorKey);

        texture = SDL_CreateTextureFromSurface(Renderer, surface);
        SDL_FreeSurface(surface);
    }

    if(texture == NULL)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!  Failed to load:", filename, Window);
    }

    return texture;
}
