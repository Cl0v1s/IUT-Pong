#include "main.h"

using namespace std;




// -- main --------------------------------------
// initialise et lance le jeu
// ----------------------------------------------
int main ()
{
    //paramétrage de la SDL
    SDL_Init( SDL_INIT_VIDEO);
    TTF_Init();
    SDL_WM_SetCaption("Anticipation", "Anticipation");
    SDL_Surface* screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
    srand (time(NULL));

    //déclaration des variables de "déroulement"
    int gameState = 0;
    bool done = false;

    while(!done)
    {
        //Appel de la logique du jeu
        switch(gameState)
        {
        case 0:
            gameState = menu(screen);
            break;
        case 1:
            gameState = game(screen);
            break;
        case 2:
            gameState = quit(done);
            break;
        }
    }

    return 0;
}
