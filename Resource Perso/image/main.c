#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include "Personnage.h"

int main(int argc, char *argv[])
{
  int i=-1;
  int continuer = 1;
  Uint8 *etat;
  int tempsA;
  SDL_Surface *ecran = NULL,*fond = NULL ;
  SDL_Surface *character[15]={NULL};
  SDL_Rect position_fond, position_perso;
  SDL_Event event;
  SDL_Init(SDL_INIT_EVERYTHING);

  ecran = SDL_SetVideoMode(600,460,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
  fond = IMG_Load("map.png");

  character[0] = IMG_Load("image/right1.png");
  character[1] = IMG_Load("image/right2.png");
  character[2] = IMG_Load("image/right3.png");
  character[3] = IMG_Load("image/right4.png");
  character[4] = IMG_Load("image/right5.png");
  character[5] = IMG_Load("image/right6.png");

  character[6] = IMG_Load("image/left1.png");
  character[7] = IMG_Load("image/left2.png");
  character[8] = IMG_Load("image/left3.png");
  character[9] = IMG_Load("image/left4.png");
  character[10] = IMG_Load("image/left5.png");
  character[11] = IMG_Load("image/left6.png");
  
  position_fond.x = 0;
  position_fond.y = 0;

  position_perso.x = 30;
  position_perso.y = 100;

  SDL_BlitSurface(fond,NULL,ecran,&position_fond);
  SDL_BlitSurface(character[0],NULL,ecran,&position_perso);
  SDL_Flip(ecran);

  SDL_ShowCursor(SDL_DISABLE);
  while (continuer)
  {
    tempsA = SDL_GetTicks();
     SDL_PollEvent(&event);
     switch (event.type)
     {
       case SDL_QUIT:
                     continuer = 0;
                     break;
        case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                     case SDLK_ESCAPE:
                          		continuer = 0;
                         		break;
		    }

      }
    etat = SDL_GetKeyState(NULL);
    if(etat[SDLK_RIGHT] == 1 && etat[SDLK_LEFT] !=1)
    {
      for(i=0;i<6;i++)
      {
        position_perso.x += 5;
        SDL_BlitSurface(fond,NULL,ecran,&position_fond);
        SDL_BlitSurface(character[i],NULL,ecran,&position_perso);
        SDL_Flip(ecran);
        SDL_Delay(50);
      }
    }
    if(etat[SDLK_LEFT] == 1 && etat[SDLK_RIGHT] !=1)
    {
      for(i=5;i<12;i++)
      {
        position_perso.x -= 5;
        SDL_BlitSurface(fond,NULL,ecran,&position_fond);
        SDL_BlitSurface(character[i],NULL,ecran,&position_perso);
        SDL_Flip(ecran);
        SDL_Delay(50);
      }
    }
  
   }


 SDL_FreeSurface(ecran);
 SDL_FreeSurface(fond);
 SDL_FreeSurface(character[15]);
 SDL_Quit();
   

 return 0;
}

