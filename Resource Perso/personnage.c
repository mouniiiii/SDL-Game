
#include"personnage.h"


void initperso(personne* p)
{
    p->x =50;          // type de mesure
    p->y = 350;
    p->etat = ETAT_SOL;
    p->vx = p->vy = 0;
p->vitesse=0.5;
p->acceleration=0;
p->num=1;
p->direction=-1;
p->vi=0;
p->position_vie.x=50;
p->position_vie.y=50;
p->fig=0;
char nomFich[20];
int i;
for(i=0;i<20;i++)
{
    sprintf(nomFich,"image/sprite%d.png",i);
    p->sprite[i]=IMG_Load(nomFich);
}
char nomvie[20];
int j;
for(j=0;j<3;j++)
{
    sprintf(nomvie,"image/vie%d.png",j);
    p->vie[j]=IMG_Load(nomvie);
}

}


void Miseajour(personne* p,SDL_Surface* screen)
{
   
      p->position_perso.x =p->x;          
      p->position_perso.y= p->y;
      p->position_perso.w= 20;
      p->position_perso.h = 40;
  
}
 

void afficherperso(personne* p,SDL_Surface *ecran)
{  
//SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
SDL_BlitSurface(p->sprite[p->num],NULL,ecran,&(p->position_perso));
SDL_BlitSurface(p->vie[p->vi],NULL,ecran,&(p->position_vie));

}

 

void Saute(personne* p,float impulsion)
{
    p->vy = -impulsion;             
    p->etat = ETAT_AIR;            
}




void deplacerperso(personne *p,Uint32 dt)
{ if(p->position_perso.x ==100)
  {
      ControleSol(p);
  }
    p->dx = (0.5*p->acceleration)*dt*dt+(p->vitesse)*dt;//CALCUL DE LA DISTANCE ENGENDRE
 if(p->deplacement==1)
 {
  p->x+=(p->dx);
 }
else if(p->deplacement==0)
 {
    p->x-=(p->dx);
 }
  
}



void ControleSol(personne* p)
{
    if (p->y>380)    
    {
        p->y = 380;
        if (p->vy>0)
            p->vy = 0.0f;
        p->etat = ETAT_SOL;
    }
}

void Gravite(personne* p,float factgravite,float factsautmaintenu,Uint8* keys)
{
    if (p->etat == ETAT_AIR &&( keys[SDLK_UP]||keys[SDLK_z]))
        factgravite/=factsautmaintenu; 
    p->vy += factgravite;
}


void animerperso(personne* p)
 {  
     if(p->direction==0)
     {if(p->num>=5)
      p->num=1;
      else p->num++;
     }
     else if(p->direction==1)
     {
      if(p->num==10||p->num<6||p->num>11)
       p->num=6;
       else p->num++;
      }
 else if(p->direction==2)
     {
      if(p->num==13||p->num<11||p->num>14)
       p->num=11;
       else p->num++;
      }
 else if(p->direction==3)
     {
   
       p->num=16;
    
      }
else if(p->direction==4)
     {
     
       p->num=17;
     
      }
 else 
     {
      if(p->num==15||p->num<14||p->num>16)
       p->num=14;
       else p->num++;
      }
 
      }


void Updateperso(personne* p,Uint8* keys)
{ 
    float impulsion = 6;
    float factgravite = 0.5;
    float factsautmaintenu = 3;
 
    Gravite(p,factgravite,factsautmaintenu,keys);
    ControleSol(p);
      
    p->x +=p->vx;
    p->y +=p->vy;


}






