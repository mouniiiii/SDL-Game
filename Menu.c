#include "Resource Menu/Header/Constantes.h"
#include "Resource Menu/Header/Background.h"
#include "Resource Menu/Header/Music.h"
#include "Resource Menu/Header/Buttons.h"
#include "Resource Menu/Header/Text.h"
#include "Resource Menu/Header/Menu.h"
////////////////////////////////////////
#include "Resource Perso/personnage.h"
#include "Resource Back/background.h"
#include "Resource Back/collisionparfaite.h"
#include "Resource Entite/ennemy.h"
#include "Resource MiniMap/minimap.h"
#include "Resource Menu/Header/tic.h"
#include "Resource Enigme5/enigme.h"
#include "Resource Enigme 6/EnigmeSF.h"
////////////////////////////////////////

void NewGame(SDL_Surface *screen, int *Mode)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    FILE *fichier = NULL;
    fichier = fopen("Resource MiniMap/nomficher.txt", "a+");
    TTF_Init();
    TTF_Font *police = NULL;
    SDL_Color Color = {255, 255, 255};
    police = TTF_OpenFont("Resource MiniMap/pol.ttf", 50);

    SDL_Event event;
    /////////////////////
    Ennemi E;
    Enigme e;
    tic t;
    /////////////////////

    // Mounir's Updates:
    enigme eSF;
    eSF.num_enigme = -1;
    int s, r = 0, run = 1, alea;
    char image[30] = "";
    int time = 0; //, r = 0;
    ///////////////////////
    ////wided decl/////

    background ba, bm;

    ////////////////////
    personne S;
    Uint8 *keys;
    Uint32 dt = 1, t_prev = 1;
    int impulsion = 6;
    int i;
    SDL_Rect camera;
    minimap m;
    int temps;
    int joueur, x, o, coup;
    /////////////////////
    int die = 0;
    int die2 = 0;
    int continuer = 1;
    int boucle = 1;
    int boucle1 = 1;
    int random;
    int Game;
    SDL_WM_SetCaption("NEW GAME", NULL);

    /////////////////////
    // wided init////

    initialisation_back(&ba); // initback
    initBackMasque(&bm);      // pour la collision parfaite

    // initialiserperso(&perso);
    //////////
    initperso(&S);
    initEnnemi(&E);
    init_map(&m);
    initialisation(&t);
    Init_Enigme(&e, "Resource Enigme5/questions.txt", "Resource Enigme5/reponses.txt", "Resource Enigme5/vraireponses.txt");
    init_enigme(&eSF, "Resource Enigme 6/enigme.txt");

    /////////////////////
    // mahmoud updates
    // SDL_Surface * ecran;
    // ecran=SDL_SetVideoMode(552,541,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    int cnt = 1;

    while (continuer)
    {
        // mahmoud tache blanche
        /*while(cnt)
       {
          affichage(t,screen);
          SDL_Flip(screen);
          if( t.tour<9 &&atilganer(t.tabsuivi)==0)
          {
           if((t.tour+joueur)%2==0)//tour du PC
              {calcul_coup(t.tabsuivi);
              t.tour++;}
          else
          {
          SDL_WaitEvent(&event);
          switch(event.type)
          {
          case SDL_QUIT:
              continuer=0;
              break;
          case SDL_MOUSEBUTTONUP:
              x=event.button.x/190;
              o=event.button.y/190;
              coup=3*o+x;
              t.tour++;
              break;
          }

          t.tabsuivi[coup]=-1;
          }
          }
          else
          {
          Resultat(t,screen);
         // cnt=0;
          }
       //}
        */

        // SDL_FreeSurface(ecran);

        /////////////////////
        t_prev = SDL_GetTicks();
        /////////////////////////////////////////

        deplacerIA(&E, S.position_perso);

        //////////////////////////////////////////

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
            case SDLK_RIGHT:

                if (collisionparfaite(screen, S) == 10)
                {
                    scrolling(&ba, 0); // scrollingymin;
                    scrolling(&bm, 0);
                    E.posSpike.x--;
                    E.posEnemy.x++;
                }

                break;
            case SDLK_LEFT:

                if (collisionparfaite(screen, S) == 10)
                {
                    scrolling(&ba, 1); // scrolllingysar;
                    scrolling(&bm, 1);
                    E.posSpike.x++;
                    E.posEnemy.x--;
                }

                break;
            case SDLK_UP:

                if (collisionparfaite(screen, S) == 10)
                {
                    scrolling(&ba, 2); // scrollingymin;
                    scrolling(&bm, 2);
                    E.posSpike.y--;
                    E.posEnemy.y--;
                }
                break;
            case SDLK_DOWN:

                if (collisionparfaite(screen, S) == 10)
                {
                    scrolling(&ba, 3); // scrollingymin;
                    scrolling(&bm, 3);
                    E.posSpike.y++;
                    E.posEnemy.y++;
                }
                break;
            }
            break;
        }

        //////////////////////////////////////
        keys = SDL_GetKeyState(NULL);
        if (keys[SDLK_RIGHT] == 0 && keys[SDLK_LEFT] == 0 && keys[SDLK_j] == 0 && keys[SDLK_UP] == 0 && keys[SDLK_w] == 0)
        {
            S.direction = -1;
            S.deplacement = -1;
        }
        if (keys[SDLK_RIGHT] == 1)
        {
            S.deplacement = 1;
            S.direction = 0;
        }
        if (keys[SDLK_j])
        {
            S.direction = 2;
        }
        if (keys[SDLK_w])
        {
            S.direction = 4;
        }
        if (keys[SDLK_a])
        {
            S.acceleration = 0;
        }
        if (keys[SDLK_LEFT])
        {
            S.deplacement = 0;
            S.direction = 1;
        }
        if (keys[SDLK_UP] && S.etat == ETAT_SOL)
        {
            Saute(&S, impulsion);
            S.direction = 3;
        }

        //////////////////////////////////////

        afficheBack(bm, screen);
        collision(screen, &S);
        animerBackground(&ba);
        afficheBack2(ba, screen);
        afficherminimap(m, screen);
        affichertemp(&temps, screen, police);
        MAJMinimap(S.position_perso, &m, camera, 20);
        afficherEnnemi(E, screen);
        afficherperso(&S, screen);
        afficherEnnemi2(E, screen);
        animerEnnemi(&E);
        deplacer(&E);
        animerperso(&S);
        deplacerperso(&S, dt);
        Updateperso(&S, keys);
        dt = SDL_GetTicks() - t_prev;

        // SDL_Flip(screen);
        SDL_Delay(10);
        die = collisionBB(S, E);
        if (die == 1)
        {
            while (boucle == 1)
            {
                SDL_Flip(screen);
                do
                {
                    afficherEnigme(eSF, screen);
                    time = (SDL_GetTicks() - t_prev) / 1000;
                    SDL_BlitSurface(eSF.anim.spritesheet, &eSF.anim.clips[eSF.anim.cliploaded], screen, &eSF.anim.pos);
                    SDL_Flip(screen);
                    switch (time)
                    {
                    case 5:
                        animer(&eSF);
                        break;

                    case 10:
                        animer(&eSF);
                        break;

                    case 15:
                        animer(&eSF);
                        break;

                    case 20:
                        animer(&eSF);
                        break;

                    case 25:
                        animer(&eSF);
                        break;

                    case 30:
                        animer(&eSF);
                        break;
                    }
                    r = resolution(&continuer, &run);

                } while (time <= 30 && (r > 3 || r < 1) && continuer != 0);

                afficher_resultat(screen, eSF.reponsevrai, r, &eSF);
                SDL_Flip(screen);
                boucle = 0;
            }
        }
        die2 = collisionBB2(S, E);
        if (die2 == 1)
        {
            while (boucle1 == 1)
            {

                boucle1 = Play_Enigme(&e, screen, &Game);
            }

            if (Game)
            {
                printf("you win!!!");
            }
            else if (!Game)
            {
                printf("you lost!!! %d ", Game);
            }
        }

        SDL_Flip(screen);
    }

    /////////////////////////////////////
    for (i = 0; i < 20; i++)
    {
        SDL_FreeSurface(S.sprite[i]);
    }
    SDL_FreeSurface(S.jeu.HUD_etoiles);
    SDL_FreeSurface(S.jeu.HUD_vie);
    /////////////////////////////////////
    SDL_FreeSurface(m.map);
    /////////////////////////////////////
    SDL_FreeSurface(ba.imgback);
    SDL_FreeSurface(bm.imgback);
    SDL_FreeSurface(ba.image_flower);
    SDL_FreeSurface(bm.image_flower);
    /////////////////////////////////////
    SDL_FreeSurface(eSF.img[0]);

    SDL_FreeSurface(eSF.anim.spritesheet);
    /////////////////////////////////////
    for (i = 0; i < 5; i++)
    {
        SDL_FreeSurface(e.boutons[i]);
        SDL_FreeSurface(e.reponses[i]);
    }
    SDL_FreeSurface(e.background[0]);
    SDL_FreeSurface(e.background[1]);
    SDL_FreeSurface(e.lost);
    SDL_FreeSurface(e.win);
    SDL_FreeSurface(e.question);
    liberationmemoire(t);
    /////////////////////////////////////
    freeEnnemy(E);

    fclose(fichier);
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
