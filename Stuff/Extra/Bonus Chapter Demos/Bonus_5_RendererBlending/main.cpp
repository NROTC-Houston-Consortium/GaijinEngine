//Include the SDL 2 header file
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>

//Constant Variables
const int CLIENT_WIDTH = 800;
const int CLIENT_HEIGHT = 600;
const int NUM_PARTICLES = 256;

//Setup variables
SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

//These are like surfaces, but they work with the
//renderer and are more flexible in some regards
SDL_Texture* Background = NULL;
SDL_Texture* ParticleTexture = NULL;

int Blendmode = 0;

typedef struct Particle
{
    int x;
    int y;
    int xVel;
    int yVel;
    int xAccel;
    int yAccel;
    int life;
    int r;
    int g;
    int b;
    int scale;
};

Particle ParticleList[NUM_PARTICLES];

bool InitSDL();
void CleanUp();
void UpdateGame();
void DrawScreen();

void InitParticles();
void ResetParticle(Particle* p);

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

    InitParticles();

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

            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    Blendmode++;

                    if(Blendmode > 3)
                        Blendmode = 0;

                    if(Blendmode==0)
                    {
                        SDL_SetTextureBlendMode(ParticleTexture, SDL_BLENDMODE_NONE);
                        SDL_SetWindowTitle(Window, "Curren Blendmode: SDL_BLENDMODE_NONE");
                    }
                    else if(Blendmode == 1)
                    {
                        SDL_SetTextureBlendMode(ParticleTexture, SDL_BLENDMODE_BLEND);
                        SDL_SetWindowTitle(Window, "Curren Blendmode: SDL_BLENDMODE_BLEND");
                    }
                    else if(Blendmode == 2)
                    {
                        SDL_SetTextureBlendMode(ParticleTexture, SDL_BLENDMODE_ADD);
                        SDL_SetWindowTitle(Window, "Curren Blendmode: SDL_BLENDMODE_ADD");
                    }
                    else
                    {
                        SDL_SetTextureBlendMode(ParticleTexture, SDL_BLENDMODE_MOD);
                        SDL_SetWindowTitle(Window, "Curren Blendmode: SDL_BLENDMODE_MOD");
                    }
                }
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
    Window = SDL_CreateWindow("Click to change blending mode",
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
    ParticleTexture = LoadTexture("graphics/particle.png");

    if(Background == NULL || ParticleTexture == NULL)
        return false;

    return true;
}

void CleanUp()
{
    SDL_DestroyTexture(Background);
    SDL_DestroyTexture(ParticleTexture);

    //We have to clean up the renderer when we're done with it
    SDL_DestroyRenderer(Renderer);

    //Clean up the window
    SDL_DestroyWindow(Window);

    //And quit :)
    SDL_Quit();
}

void InitParticles()
{
    for(int i = 0; i < NUM_PARTICLES; i++)
    {
        ResetParticle(&ParticleList[i]);
    }
}

void ResetParticle(Particle* p)
{
    int mouseX;
    int mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    p->xVel = 2-rand()%4;
    p->yVel = 0-rand()%5;
    p->xAccel = 1-rand()%3;
    p->yAccel = 1-rand()%3;
    p->life = rand()%255;
    p->r = rand()%255;
    p->g = rand()%255;
    p->b = rand()%255;
    p->scale = rand()%50;
    p->x = mouseX - p->scale/2;
    p->y = mouseY - p->scale;
}

void UpdateGame()
{
    for(int i = 0; i < NUM_PARTICLES; i++)
    {
        ParticleList[i].x += ParticleList[i].xVel;
        ParticleList[i].y += ParticleList[i].yVel;
        ParticleList[i].xVel += ParticleList[i].xAccel;
        ParticleList[i].yVel += ParticleList[i].yAccel;
        ParticleList[i].life--;

        if(ParticleList[i].life < 0)
        {
            ResetParticle(&ParticleList[i]);
        }
    }
}

void DrawScreen()
{
    //Clear the screen
    SDL_SetRenderDrawColor(Renderer, 255, 255, 250, 255);
    SDL_RenderClear(Renderer);

    //Draw the background on the entire screen
    SDL_RenderCopy(Renderer, Background, NULL, NULL);

    for(int i = 0; i < NUM_PARTICLES; i++)
    {
        SDL_SetTextureColorMod(ParticleTexture, ParticleList[i].r, ParticleList[i].g, ParticleList[i].b);
        SDL_SetTextureAlphaMod(ParticleTexture, ParticleList[i].life);

        SDL_Rect ParticleDestRect = {ParticleList[i].x, ParticleList[i].y, ParticleList[i].scale, ParticleList[i].scale};

        SDL_RenderCopy(Renderer, ParticleTexture, NULL, &ParticleDestRect);
    }

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
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", "Failed to load texure!", Window);
    }

    return texture;
}
