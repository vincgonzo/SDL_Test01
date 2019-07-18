#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

void pause();

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL;

    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE); // Ouverture de la fenêtre

    if(ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode video : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("That is my window Game", NULL);
    pause(); // Mise en pause du programme

    SDL_Quit(); // Arrêt de la SDL

    return EXIT_SUCCESS; // Fermeture du programme
}

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
