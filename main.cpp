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
    SDL_Surface *lignes[256] = {NULL};
    SDL_Rect position;
    int i = 0;


    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640, 256, 32, SDL_HWSURFACE);

    for (i = 0 ; i <= 255 ; i++)
        lignes[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 640, 1, 32, 0, 0, 0, 0);

    SDL_WM_SetCaption("Layered Test on SDL !", NULL);

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    for (i = 0 ; i <= 255 ; i++)
    {
        position.x = 0; // Les lignes sont � gauche (abscisse de 0)
        position.y = i; // La position verticale d�pend du num�ro de la ligne
        SDL_FillRect(lignes[i], NULL, SDL_MapRGB(ecran->format, i, i, i));
        SDL_BlitSurface(lignes[i], NULL, ecran, &position);
    }

    SDL_Flip(ecran);
    pause();

    for (i = 0 ; i <= 255 ; i++) // N'oubliez pas de lib�rer les 256 surfaces
        SDL_FreeSurface(lignes[i]);
    SDL_Quit(); // Arr�t de la SDL

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
