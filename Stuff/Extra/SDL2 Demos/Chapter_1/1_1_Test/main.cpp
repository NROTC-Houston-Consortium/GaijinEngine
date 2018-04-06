#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

    //This is new in SDL 2.  It's now possible to show message boxes.  This is more fitting
    //than using printf in some cases.
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SDL", "Windows FTW!!!", NULL);

	SDL_Quit();

	return 0;
}
