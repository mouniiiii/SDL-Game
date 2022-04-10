#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED
 
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#define DROITE 1
#define GAUCHE 0

#define ETAT_SOL 0
#define ETAT_AIR 1
typedef struct Gestion
{

    SDL_Surface *screen;
    //HUD
    SDL_Surface *HUD_vie, *HUD_etoiles;
    int vies, etoiles;
} Gestion;
typedef struct
{   
    Gestion jeu;
    float dx;
    int num,vi;
    float x,y;
    float vx,vy;
    SDL_Rect position_perso,position_vie;
    SDL_Surface *sprite[20],*vie[3];
    int fig;
    int etat;
    float acceleration,vitesse;
    int deplacement;
    int direction;
    int vieper;
} personne;

//LES FONCTIONS DEVELOPPEES
void initperso(personne* p);
void Miseajour(personne* p,SDL_Surface* screen);
void afficherperso(personne* p,SDL_Surface *ecran);
void deplacerperso(personne *p,Uint32 dt);
void Saute(personne* p,float impulsion);
void ControleSol(personne* p);
void Gravite(personne* p,float factgravite,float factsautmaintenu,Uint8* keys);
void animerperso(personne* p);
void Updateperso(personne* p,Uint8* keys);
void Updateperso1(personne* p1,Uint8* keys);
//---------------------------------------------
void drawImage(SDL_Surface *image,SDL_Surface *screen, int x, int y);
void drawString(char *text,SDL_Surface *screen, int x, int y, TTF_Font *font);
void drawHud(personne *p,SDL_Surface *screen,TTF_Font *font);
void cleanup(personne *p);
TTF_Font *loadFont(char *name, int size);
void closeFont(TTF_Font *font);
#endif
