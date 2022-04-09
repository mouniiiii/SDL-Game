#ifndef Ennemy_H
#define Ennemy_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
/////////////////////////
typedef struct
{
    SDL_Surface *sprite[6];

    SDL_Rect position_perso;

    int num;

    int direction1;

    int distance;

    int position_initiale;
} personne;
////////////////////////
typedef struct
{
    SDL_Surface *Enemy[2][6];

    SDL_Rect posEnemy;

    int num;

    int direction;

    int direction1;

    int distance;

    int position_initiale;
} Ennemi;

void initEnnemi(Ennemi *E);
void afficherEnnemi(Ennemi E, SDL_Surface *screen);
void animerEnnemi(Ennemi *E);
void deplacer(Ennemi *E);
int collisionBB(personne P, Ennemi E);
void deplacerIA(Ennemi *E, SDL_Rect posPerso);
void freeEnnemy(Ennemi E);
#endif // !Ennemy_H
