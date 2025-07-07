//les biblioteques eli nesthakohom.
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <SDL/SDL_events.h>
#include "enigme.h"
#include <time.h>
#define FRAME_RATE 60
#define FRAME_DELAY (1000 / FRAME_RATE)

int main(int argc,char *argv[])
{
 SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER); //SDL_Init() :pour initialiser les sous-systemes video,timer.
 if (TTF_Init() == -1) {
    printf("Error initializing SDL_ttf: %s\n", TTF_GetError());//verification.
    exit(1);
  }
 SDL_Surface *fenetre = NULL; //creer la surface principale (fenetre).
 SDL_Surface *B_enigme = NULL;
 SDL_Rect B_enigme_pos;
 Enigme E[7]; //tableau d'enigmes.
 SDL_Event event; //evenement.
 int boucle = 1;
 int rep = 0;
 int num;
 int n=0;

 
 SDL_Color color={255,255,255}; //couleur blanc.
 SDL_Surface* time_surface = NULL;
 SDL_Rect time_pos;
 int deb_time=SDL_GetTicks(); //SDL_GetTicks() une fonction utilisée pour obtenir le temps écoulé en millisecondes.

 int temps_ecoule=0;
 int temps_restant=60;
 int temps_actuel;
 char time_string[10];
 int time_running=1;
 //position wel font mtaa time.
 TTF_Font *font=TTF_OpenFont("text.ttf",32);
 time_pos.x=400;
 time_pos.y=550;

 fenetre=SDL_SetVideoMode(SCREEN_H,SCREEN_W,32,SDL_HWSURFACE); //creation mtaa surface (fenetre) .
 if(fenetre == NULL)
 {
 printf("Could not initialize SDL:%s.\n",SDL_GetError()); //ki ma tsiresh l creation .
 return -1;
 }
 //position o loading mtaa l'image de background.
 B_enigme=IMG_Load("back.png");
 B_enigme_pos.x=50;
 B_enigme_pos.y=15;
 generer_enigme(E,"enigme.txt"); //fichier texte.

 for(num=0;num<7;num++) //loading les images (sablier).
  {
  E[num].anime_surface[0]=IMG_Load("image1.png");
  E[num].anime_surface[1]=IMG_Load("image2.png");
  E[num].anime_surface[2]=IMG_Load("image3.png");
  E[num].anime_surface[3]=IMG_Load("image4.png");
  E[num].anime_surface[4]=IMG_Load("image5.png");
 
  E[num].anime_pos.x=700; //position mteehom.
  E[num].anime_pos.y=520;
  }

 srand(time(NULL)); //une fonction qui initialise le generateur de nbres aleatoires de maniere unique a chaque execution , thadher lel fonction rand().
  while(boucle) //boucle principale tant que different de 0.
  { 
    if(SDL_PollEvent(&event)) //mtaa les evenement souris,clavier,manette.
    {
       
      switch(event.type) //type mtaa l'event :KEYDOWN.
       { 
         case SDL_QUIT:
           boucle=0;
         break;
         case SDL_KEYDOWN:
	switch(event.key.keysym.sym)
	{
	    case SDLK_LEFT: //ki tenzel ala bouton gauche.
		rep=1;
		n=1;
	    break;
	    case SDLK_RIGHT: //ki tenzel ala bouton droite.
		rep=2;
		n=1;
	    break; 
	    case SDLK_RETURN: //ki tenzel ala retourner.
		num=alea_enigme(E); //taayet lel fonction alea.
		rep=0;
		deb_time=SDL_GetTicks();
		n=0;
		time_running=1;
	    break;
	}
         break;
       }
    }
   
   if(time_running)
    {
    int temps_actuel = SDL_GetTicks();
    temps_ecoule = temps_actuel - deb_time;
    temps_restant =60-(temps_ecoule/1000); //formule.
    }

   
    sprintf(time_string,"Time:%d",temps_restant); 
    time_surface = TTF_RenderText_Blended(font,time_string,color);
    SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 0, 0, 0)); //couleur de la fenetre (noir).
    SDL_BlitSurface(B_enigme,NULL,fenetre,&B_enigme_pos); //thot taswira mtaa l background fl fenetre.
  
    animer_enigme(E,num,fenetre); //fonction.
    
   if(num>=0 && num<7)
   {
     afficher_enigme(E,num,fenetre); //fonction.
     SDL_BlitSurface(time_surface,NULL,fenetre,&time_pos);
     if(temps_restant==0)
       { 
             SDL_BlitSurface(B_enigme,NULL,fenetre,&B_enigme_pos);
             afficher_resultat("Temps ecoule",fenetre); //ken ma jewebsh .
             time_running=0;
       }     
     else if(rep == 1 || rep == 2) //ken wahda wahda m les reponses.
       {
        SDL_BlitSurface(B_enigme,NULL,fenetre,&B_enigme_pos);
        if(rep==E[num].correct && n==1) //comparaison .
        { 
            afficher_resultat(" bravo, bien joue <3 !",fenetre);//ken jeweb b shih.
        }
        else if(rep!=E[num].correct && n==1)
        {
            afficher_resultat("c'est faux !!",fenetre);//ken jeweb bl ghalet.
        }  
       }
    
  }
  SDL_Flip(fenetre); //mettre a jour.

}

  //liberation de la memoire.
  SDL_FreeSurface(B_enigme);
  SDL_FreeSurface(time_surface);
  free_enigme(E); 
  TTF_Quit();
  SDL_Quit();
return 0;
}
