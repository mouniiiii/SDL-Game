#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <time.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "Resource Enigme 6/EnigmeSF.h"

/////////////////////////////////////
void init_enigme(enigme *e, char *nomfichier)
{
	e->anim.pos.x = 6;
	e->anim.pos.y = 6;
	e->anim.spritesheet = IMG_Load("Resource Enigme 6/spritesheet.png");
	e->anim.cliploaded = 1;
	int j, y;
	for (j = 0, y = 0; j < 6; j++, y += 20)
	{
		e->anim.clips[j].x = 6;
		e->anim.clips[j].y = y + 6;
		e->anim.clips[j].w = 200;
		e->anim.clips[j].h = 20;
	}
	int i = 1;

	e->p.x = 0;
	e->p.y = 0;
	e->img = NULL;

	generate_afficher(&e->num_enigme);
	char nomimage[20];
	FILE *f = fopen("Resource Enigme 6/enigme.txt", "r");
	if (f != NULL)
	{

		while (fscanf(f, "%s %d\n", nomimage, &e->reponsevrai) != EOF && i != e->num_enigme)
		{
			i++;
		}

		e->img = IMG_Load(nomimage);
		fclose(f);
	}
	else
		printf("erreur");
}

//////////////////////////////
void generate_afficher(int *alea)
{
	int test = *alea;
	srand(SDL_GetTicks());

	do
	{
		*alea = 1 + rand() % 3;
	} while (*alea == test);
}

/////////////////////////////////////////////
void afficherEnigme(enigme e, SDL_Surface *screen)
{
	SDL_BlitSurface(e.img, NULL, screen, &e.p);
	SDL_Flip(screen);
}

////////////////////////////////
int resolution(int *running, int *run)
{
	SDL_Event event;
	int r = 0;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		*running = 0;
		*run = 0;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
			r = 1;
			break;
		case SDLK_z:
			r = 2;
			break;
		case SDLK_e:
			r = 3;
			break;
		}
		break;
	}
	return r;
}

/////////////////////////////////////////////////////
void afficher_resultat(SDL_Surface *screen, int s, int r, enigme *en)
{

	if (r == s)
	{
		en->img = IMG_Load("Resource Enigme 6/win.png");
		SDL_BlitSurface(en->img, NULL, screen, &(en->p));
		SDL_Flip(screen);
	}
	else
	{
		en->img = IMG_Load("Resource Enigme 6/lose.png");
		SDL_BlitSurface(en->img, NULL, screen, &(en->p));
		SDL_Flip(screen);
	}
}

///////////////////////
void animer(enigme *e)
{
	e->anim.cliploaded++;
	if (e->anim.cliploaded >= 6)
		e->anim.cliploaded = 1;
}
