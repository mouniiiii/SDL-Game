#include "Resource Menu/Header/Constantes.h"
#include "Resource Menu/Header/Background.h"
#include "Resource Menu/Header/Music.h"
#include "Resource Menu/Header/Buttons.h"
#include "Resource Menu/Header/Text.h"
#include "Resource Menu/Header/Menu.h"
#include "Resource Perso/personnage.h"
#include "Resource Back/background.h"
#include "Resource Back/collisionparfaite.h"
#include "Resource Entite/ennemy.h"
#include "Resource MiniMap/minimap.h"
#include "Resource Enigme 6/EnigmeSF.h"

void NewGame(SDL_Surface *screen, int *Mode)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Background NGame;
    SDL_Event event;
    Ennemi E;
    int die = 0;
    int continuer = 1;

    SDL_WM_SetCaption("NEW GAME", NULL);
    initBackNGame(&NGame);

    initEnnemi(&E);

    while (continuer)
    {
        /////////////////////////////////////////
        afficherEnnemi(E, screen);
        afficherEnnemi2(E, screen);
        animerEnnemi(&E);
        deplacer(&E);
        // deplacerIA(&E, p.position_perso);
        SDL_Flip(screen);

        SDL_Delay(10);
        // die = collisionBB(p, E);
        //////////////////////////////////////////
        if (die == 1)
        {
            // done = 0;
        }
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            SaveScreenMode(screen, Mode);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = 0;
                SaveScreenMode(screen, Mode);
                break;
            }
            break;
        }
        AfficherNGame(NGame, screen);
        SDL_Flip(screen);
    }
    freeBackNGame(NGame);
    freeEnnemy(E);
}

void Settings(SDL_Surface *screen, int *Mode, int *niv_volume, int *volume)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    //////////////////////////////
    SDL_Event event;
    Buttons B;
    Background Set;
    int continuer = 2;
    //////////////////////////////
    SDL_WM_SetCaption("SETTINGS", NULL);
    initBackSet(&Set);
    initButSet(&B);
    //////////////////////////////
    SDL_EnableKeyRepeat(0, 50);
    while (continuer)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            SaveScreenMode(screen, Mode);
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = 0;
                SDL_BlitSurface(B.Quit, NULL, screen, &B.positionQuit);
                SDL_Flip(screen);
                SaveScreenMode(screen, Mode);
                break;
            case SDLK_LEFT:
                volumeDown(niv_volume, volume);
                SDL_BlitSurface(B.Moins, NULL, screen, &B.positionMoins);
                SDL_Flip(screen);
                break;
            case SDLK_RIGHT:
                volumeUp(niv_volume, volume);
                SDL_BlitSurface(B.Plus, NULL, screen, &B.positionPlus);
                SDL_Flip(screen);
                break;
            case SDLK_f:
                SetFull(screen, Mode);

                break;
            case SDLK_n:
                SetNorm(screen, Mode);

                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (event.button.x > 260 && event.button.x < 380 && event.button.y > 210 && event.button.y < 330)
                {
                    volumeDown(niv_volume, volume);
                    SDL_BlitSurface(B.Moins, NULL, screen, &B.positionMoins);
                    SDL_Flip(screen);
                }
                else if (event.button.x > 610 && event.button.x < 730 && event.button.y > 210 && event.button.y < 330)
                {
                    volumeUp(niv_volume, volume);
                    SDL_BlitSurface(B.Plus, NULL, screen, &B.positionPlus);
                    SDL_Flip(screen);
                }
                else if (event.button.x > 410 && event.button.x < 494 && event.button.y > 440 && event.button.y < 528)
                {
                    SetFull(screen, Mode);
                }
                else if (event.button.x > 495 && event.button.x < 578 && event.button.y > 440 && event.button.y < 528)
                {
                    SetNorm(screen, Mode);
                }
                else if (event.button.x > 445 && event.button.x < 566 && event.button.y > 530 && event.button.y < 649)
                {
                    continuer = 0;
                    SDL_BlitSurface(B.Quit, NULL, screen, &B.positionQuit);
                    SaveScreenMode(screen, Mode);
                    break;
                }
            }
            break;
        }
        AfficherSet(Set, screen);
        AfficherButOption(B, screen);
        AfficherButMoins(B, screen);
        AfficherButPlus(B, screen);
        AfficherButScreen(B, screen, Mode);
        SDL_Flip(screen);
    }
    freeBackSet(Set);
    freeButSet(B);
}

void SaveScreenMode(SDL_Surface *screen, int *Mode)
{
    if (*Mode == 0)
    {
        SDL_Flip(screen);
        screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    }
    else
    {
        SDL_Flip(screen);
        screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_FULLSCREEN);
    }
    SDL_WM_SetCaption("Game Menu", NULL);
}

void SetFull(SDL_Surface *screen, int *Mode)
{
    *Mode = 1;
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_FULLSCREEN);
}
void SetNorm(SDL_Surface *screen, int *Mode)
{
    *Mode = 0;
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_ANYFORMAT);
}
