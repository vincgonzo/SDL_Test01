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
    SDL_Surface *rectangle = NULL;

    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE); // Ouverture de la fenêtre

    SDL_Rect position;

    position.x = (640/2) - (220/2);
    position.y = (480/2) - (220/2);
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 180, 32, 0, 0, 0, 0);

    if(ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode video : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("That is my window Game", NULL);

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));
    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_BlitSurface(rectangle, NULL, ecran, &position);

    SDL_Flip(ecran);
    pause(); // Mise en pause du programme

    SDL_FreeSurface(rectangle);
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
