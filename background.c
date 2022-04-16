#include "Resource Back/background.h"

/*void initBack (background *b)
{
//background
b->imgback=IMG_Load("map.bmp");
b->posback.x=0;
b->posback.y=0;
//camera
b->camera.x=0;
b->camera.y=0;
b->camera.w=SCREEN_W;
b->camera.h=SCREEN_H;
//musique
b->son=Mix_LoadMUS("musique.mp3"); //Chargement de la musique

}
*/
void initBackMasque(background *b)
{
	// background
	b->imgback = SDL_LoadBMP("Resource Back/mapMasque.bmp");
	b->posback.x = 0;
	b->posback.y = 0;

	// camera
	b->camera.x = 0;
	b->camera.y = 0;
	b->camera.w = SCREEN_W;
	b->camera.h = SCREEN_H;
}

void initBack2(background *b)
{
	// background2
	b->imgback = IMG_Load("Resource Back/map.bmp");
	b->posback2.x = 0;
	b->posback2.y = 0;
	// camera2
	b->camera2.x = 0;
	b->camera2.y = 0;
	b->camera2.w = SCREEN_W;
	b->camera2.h = SCREEN_H;
	// musique
	b->son = Mix_LoadMUS("Resource Back/musique.mp3"); // Chargement de la musique
	b->image_flower = IMG_Load("Resource Back/flower.png");
	b->pos_image_flower.x = 500;
	b->pos_image_flower.y = 100;

	b->single_flower.w = 56;
	b->single_flower.h = 107;
	b->single_flower.x = 0;
	b->single_flower.y = 0;

	b->flower_num = 0;
}

void initialisation_back(background *b)
{
	// initBack(b);
	initBack2(b);
}

void afficheBack(background b, SDL_Surface *ecran)
{
	/* On blitte par-dessus l'écran */
	Mix_PlayMusic(b.son, -1);
	SDL_BlitSurface(b.imgback, &b.camera, ecran, &b.posback);
}

void afficheBack2(background b, SDL_Surface *ecran)
{
	/* On blitte par-dessus l'écran */
	Mix_PlayMusic(b.son, -1); // Jouer infiniment la musique
	SDL_BlitSurface(b.imgback, &b.camera2, ecran, &b.posback2);
	displayFlower(b, ecran);
}
/*void afficher_back(background b, SDL_Surface *ecran)
{
	afficheBack(b,ecran);
	afficheBack2(b,ecran);

}*/

void scrolling(background *b, int direction)
{
	const int speed = 1;
	if (direction == 0)
	{ // yminbac1
		b->camera.x += speed;

		b->camera2.x += speed;
	}
	else if (direction == 1)
	{ // ysarbac1
		b->camera.x -= speed;

		b->camera2.x -= speed;
	}
	else if (direction == 4)
	{ // yminbac2
		b->camera2.x += speed;
	}
	else if (direction == 7)
	{ // isarback2
		b->camera2.x -= speed;
	}
	else if (direction == 2)
	{ // isarback2
		b->camera.y -= speed;

		b->camera2.y -= speed;
	}
	else if (direction == 3)
	{ // isarback2
		b->camera.y += speed;

		b->camera2.y += speed;
	}
}

void displayFlower(background b, SDL_Surface *ecran)
{
	SDL_BlitSurface(b.image_flower, &(b.single_flower), ecran, &b.pos_image_flower);
}
void animerBackground(background *b)
{

	if (b->flower_num >= 0 && b->flower_num < 8)
	{
		b->single_flower.x = b->flower_num * b->single_flower.w;
		b->flower_num++;
	}

	if (b->flower_num == 8)
	{
		b->single_flower.x = b->flower_num * b->single_flower.w;
		b->flower_num = 0;
	}
}
