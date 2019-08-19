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
    SDL_Surface *ecran = NULL, *zozor = NULL;
    SDL_Rect positionZozor;
    SDL_Event event; /* La variable contenant l'événement */
    int continuer = 1; /* Notre booléen pour la boucle */
    int tempPrecedent = 0, tempActuel = 0;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
    SDL_WM_SetCaption("Gestion des evenements en SDL", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    /* On centre Zozor à l'écran */

    zozor = SDL_LoadBMP("images/zozor.bmp");

    positionZozor.x = ecran->w / 2 - zozor->w / 2;
    positionZozor.y = ecran->h / 2 - zozor->h / 2;

    SDL_SetColorKey(zozor, SDL_SRCCOLORKEY, SDL_MapRGB(zozor->format, 0, 0, 255));
    SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);
    SDL_Flip(ecran);

    // Option for keyBoard &| mouse
    SDL_EnableKeyRepeat(10, 10);
    //SDL_ShowCursor(SDL_DISABLE); // To disable mouse display into screen
    SDL_WarpMouse(ecran->w / 2, ecran->h / 2);

    while (continuer) /* TANT QUE la variable ne vaut pas 0 */
    {
        tempActuel = SDL_GetTicks();
        //SDL_WaitEvent(&event); /* On attend un événement qu'on récupère dans event */
        SDL_PollEvent(&event);

        if(tempActuel - tempPrecedent > 30)
        {
            positionZozor.x++;
            tempPrecedent = tempActuel;
        }
        switch(event.type) /* On teste le type d'événement */
        {
            case SDL_QUIT: /* Si c'est un événement QUITTER */
                continuer = 0; /* On met le booléen à 0, donc la boucle va s'arrêter */
                break;
            case SDL_MOUSEBUTTONUP:
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        positionZozor.x = event.button.x;
                        positionZozor.y = event.button.y;
                        break;
                    case SDL_BUTTON_RIGHT:
                        continuer = 0;
                        break;
                }
                break;
            case SDL_VIDEORESIZE:
                positionZozor.x = event.resize.w / 2 - zozor->w / 2;
                positionZozor.y = event.resize.h / 2 - zozor->h / 2;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                        continuer = 0;
                        break;
                    case SDLK_UP: // Flèche haut
                        positionZozor.y--;
                        break;
                    case SDLK_DOWN: // Flèche bas
                        positionZozor.y++;
                        break;
                    case SDLK_RIGHT: // Flèche droite
                        positionZozor.x++;
                        break;
                    case SDLK_LEFT: // Flèche gauche
                        positionZozor.x--;
                        break;
                }
                break;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(zozor);
    SDL_Quit();

    return EXIT_SUCCESS;
}
