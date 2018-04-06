//Include the SDL 2 header file
#include <SDL2/SDL.h>
#include <cstdlib>
#include <math.h>

#define PI 3.14159265

const int CLIENT_WIDTH = 800;
const int CLIENT_HEIGHT = 600;

//Setup variables
SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

//These are like surfaces, but they work with the
//renderer and are more flexible in some regards
SDL_Texture* Background = NULL;
SDL_Texture* Sprite = NULL;

//These variables help manipulate the graphics
double SpaceshipX = CLIENT_WIDTH/2;
double SpaceshipY = CLIENT_HEIGHT/2;
double SpaceshipVelocity = 0;
double SpaceshipAngle = 0;
SDL_Rect SpaceshipDestRect;

const int SpaceshipPrevPositionsNum = 24;
int SpaceshipPrevPositionsX[SpaceshipPrevPositionsNum];
int SpaceshipPrevPositionsY[SpaceshipPrevPositionsNum];

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

    SpaceshipDestRect.w = 50;
    SpaceshipDestRect.h = 45;

    for(int i = 0; i < SpaceshipPrevPositionsNum; i++)
    {
        SpaceshipPrevPositionsX[i] = 0;
        SpaceshipPrevPositionsY[i] = 0;
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
    Window = SDL_CreateWindow("Use the Arrow keys to maneuver the spacecraft",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              CLIENT_WIDTH,
                              CLIENT_HEIGHT,
                              SDL_WINDOW_SHOWN);

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
    Sprite = LoadTexture("graphics/spaceship.bmp");

    if(Background == NULL || Sprite == NULL)
        return false;

    return true;
}

void CleanUp()
{
    SDL_DestroyTexture(Background);
    SDL_DestroyTexture(Sprite);

    //We have to clean up the renderer when we're done with it
    SDL_DestroyRenderer(Renderer);

    //Clean up the window
    SDL_DestroyWindow(Window);

    //And quit :)
    SDL_Quit();
}

void UpdateGame()
{
    SpaceshipPrevPositionsX[0] = SpaceshipDestRect.x + SpaceshipDestRect.w/2;
    SpaceshipPrevPositionsY[0] = SpaceshipDestRect.y + SpaceshipDestRect.h/2;

    for(int i = SpaceshipPrevPositionsNum - 1; i > 0; i--)
    {
        SpaceshipPrevPositionsX[i] = SpaceshipPrevPositionsX[i-1];
        SpaceshipPrevPositionsY[i] = SpaceshipPrevPositionsY[i-1];
    }

    Uint8* keys = (Uint8*)SDL_GetKeyboardState(NULL);

    if(keys[SDL_SCANCODE_RIGHT])
        SpaceshipAngle+=6;

    if(keys[SDL_SCANCODE_LEFT])
        SpaceshipAngle-=6;

    if(keys[SDL_SCANCODE_UP])
        SpaceshipVelocity+=0.1;

    if(keys[SDL_SCANCODE_DOWN])
        SpaceshipVelocity-=0.1;

    if(SpaceshipVelocity > 0)
        SpaceshipVelocity-=0.03;

    if(SpaceshipVelocity < 0)
        SpaceshipVelocity+=0.03;

    if(SpaceshipVelocity > 10)
        SpaceshipVelocity = 10;

    if(SpaceshipVelocity < -3)
        SpaceshipVelocity = -3;

    if(SpaceshipAngle > 360)
    {
        SpaceshipAngle-= 360;
    }

    SpaceshipX+=SpaceshipVelocity*sin(SpaceshipAngle*PI/180);
    SpaceshipY+=SpaceshipVelocity*cos(SpaceshipAngle*PI/180) * -1;

    if(SpaceshipX > CLIENT_WIDTH + SpaceshipDestRect.w/2)
        SpaceshipX = 0 - SpaceshipDestRect.w/2;

    if(SpaceshipX + SpaceshipDestRect.w/2 < 0)
        SpaceshipX = CLIENT_WIDTH + SpaceshipDestRect.w/2;

    if(SpaceshipY > CLIENT_HEIGHT + SpaceshipDestRect.h/2)
        SpaceshipY = 0 - SpaceshipDestRect.h/2;

    if(SpaceshipY + SpaceshipDestRect.h/2 < 0)
        SpaceshipY = CLIENT_HEIGHT + SpaceshipDestRect.h/2;

    SpaceshipDestRect.x = SpaceshipX - SpaceshipDestRect.w/2;
    SpaceshipDestRect.y = SpaceshipY - SpaceshipDestRect.h/2;
}

void DrawScreen()
{
    //Clear the screen
    SDL_SetRenderDrawColor(Renderer, 255, 255, 250, 255);
    SDL_RenderClear(Renderer);

    //Draw the background on the entire screen
    SDL_RenderCopy(Renderer, Background, NULL, NULL);

    //Draw the trail
    for(int i = 0; i < SpaceshipPrevPositionsNum; i++)
    {
        SDL_SetRenderDrawColor(Renderer, 255-255*(float(i)/SpaceshipPrevPositionsNum), 0, 0, 255);

        int x = SpaceshipPrevPositionsX[i];
        int y = SpaceshipPrevPositionsY[i];

        for(int l = 1; l < SpaceshipPrevPositionsNum - i; l++)
            SDL_RenderDrawPoint(Renderer, x + (rand()%l)-l/2, y+(rand()%l)-l/2);
    }

    //Draw the sprite
    SDL_RenderCopyEx(Renderer, Sprite, NULL, &SpaceshipDestRect, SpaceshipAngle, NULL, SDL_FLIP_NONE);

    //Draw the screen.  This replaces SDL_Flip in SDL 1.2 and SDL_UpdateWindowSurface
    //in SDL 2 if we weren't working with a rendering context
    SDL_RenderPresent(Renderer);
}

SDL_Texture* LoadTexture(char* filename)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = NULL;

    surface = SDL_LoadBMP(filename);

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
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Failed to load texure!", Window);
    }

    return texture;
}
