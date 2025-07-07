#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_events.h>
#include "enigme.h"
#include <time.h>
//generer les enigmes ml fichier texte "enigme.txt".
void generer_enigme(Enigme E[7],char filename[]) //enigme E : tableau d'enigme.
{
  
  FILE* f=fopen(filename,"r");//en mode read.
  if(f==NULL)
  {
   printf("ERROR:could not open file %s",filename); //verification.
   return;
  }
  char ligne[300]; //tableau de caracteres temporaire, stocke kol ligne lue a partir ml enigme.txt.

  int num_e=0; //variable indice pour acceder et manipuler les enigmes fl tableau.

  char *question_fin ,*rep1_deb,*rep1_fin,*rep2_deb,*rep2_fin;//des pointeurs bsh yshoufou l position mtaa l question, reponse 1 et reponse 2.

  char *correct_deb,*correct_fin; //pointeur bsh yshouf l position mtaa l reponse correct.
  int correct=0; //variable testocki l reponse correct.
  while(fgets(ligne,sizeof(ligne),f)&& num_e <7)
  { 
   
   question_fin=strchr(ligne,'?');//tlawej al point d'interogation bsh taaref win toufa l question.
   if(question_fin ==NULL)
    {
      printf("ERROR: problem with question in line %d\n",num_e+1); //verification.
    }
    else
    {
    *question_fin='\0';
    strncpy(E[num_e].question,ligne,100);//houni baed ma talka l question fl tableau de caracteres ligne, tcopiha fl tableau d'enigmes f champ question.
    }
    

    rep1_deb=question_fin +2; //position l reponse 1.
    rep1_fin=strchr(rep1_deb,' ');//tlawej al espace bsh taaref l reponse 1.
    if(rep1_fin==NULL)
    {
      printf("ERROR: problem with answer1 in line %d\n",num_e+1); //verification.
    }
    else
    {
     *rep1_fin='\0';
     strncpy(E[num_e].rep1,rep1_deb,20);//houni baed ma talka l reponse fl tableau de caracteres ligne, tcopiha fl tableau d'enigmes f champ rep1.
    }
    
 
    rep2_deb =rep1_fin+1; //position l reponse 2.
    rep2_fin =strchr(rep2_deb,' ');//houni tlawej al espace bsh taaref l reponse 2.
    if(rep2_fin==NULL)
    {
      printf("ERROR: problem with answer2 in line %d\n",num_e+1); //verification.
    }
    else 
    {
     *rep2_fin='\0';
     strncpy(E[num_e].rep2,rep2_deb,20);//houni baed ma talka l reponse fl tableau de caracteres ligne, tcopiha fl tableau d'enigmes f champ rep2.
    }
    

    correct_deb=rep2_fin+1; //position l reponse correct.
    correct_fin=strchr(correct_deb,'\n');
    if(correct_fin==NULL)
    {
      printf("ERROR:problem with correct in line %d\n",num_e+1); //verification.
    }
    else
    {
     *correct_fin='\0';
     correct=strtol(correct_deb,NULL,10); //strtol tconverti chaine de caractere l entier.
    if(correct!=1 && correct !=2)
    { 
      printf("ERROR: problem with correct in line %d\n",num_e+4); //verification.
    }
    else
    {
      E[num_e].correct=correct; 
    }
    }	//affichage fl terminal.
        printf("Enigme %d:\n", num_e+1);
        printf("Question: %s\n", E[num_e].question);
        printf("Réponse 1: %s\n", E[num_e].rep1);
        printf("Réponse 2: %s\n", E[num_e].rep2);
        printf("Réponse correcte: %d\n", E[num_e].correct);
        printf("\n");
    
    num_e++;
  }
  fclose(f); 
}
//fonction takhtar aleatoirement enigme.
int alea_enigme(Enigme E[7])
{
  TTF_Font* font=TTF_OpenFont("text.ttf",32); //initialise l police .
 
  if (font == NULL) 
  {
    printf("Error: Could not open font file: %s\n", TTF_GetError());
    return 1;
  }

  SDL_Color color={0,0,0};

 int num_e=rand()%7; //takhtar ay ligne m tableau d'enigme aleatoirement mn 0 l 6 .

  //l police wel couleur.
  E[num_e].q_surface=TTF_RenderText_Blended(font,E[num_e].question,color); 
  E[num_e].rep1_surface=TTF_RenderText_Blended(font,E[num_e].rep1,color);
  E[num_e].rep2_surface=TTF_RenderText_Blended(font,E[num_e].rep2,color);
  SDL_Rect q_pos = {150,170,0,0}; //position mtaa l question.

  //les positions mtaa les reponses fl ecran.
  SDL_Rect rep1_pos = {410,300,0,0};
  SDL_Rect rep2_pos = {600,300,0,0};
  
  E[num_e].q_pos=q_pos;
  E[num_e].rep1_pos = rep1_pos;
  E[num_e].rep2_pos = rep2_pos;
return num_e ;
}
void afficher_enigme(Enigme E[7],int num_e, SDL_Surface* fenetre)
{ //tcopie l contenu mtaa l tableau d'enigmes f surface.
  SDL_BlitSurface(E[num_e].q_surface,NULL,fenetre,&E[num_e].q_pos);
  SDL_BlitSurface(E[num_e].rep1_surface,NULL,fenetre,&E[num_e].rep1_pos);
  SDL_BlitSurface(E[num_e].rep2_surface,NULL,fenetre,&E[num_e].rep2_pos);
  SDL_Delay(1);
}
//yaffichi une enigme specifique.
void afficher_resultat(char resultat_text[],SDL_Surface* fenetre)
{
  SDL_Surface* resultat_surface;
  SDL_Rect resultat_pos; //position mtaa l resultat .
  TTF_Font* font=TTF_OpenFont("text.ttf",32);

  if (font == NULL) {
    printf("Error: Could not open font file: %s\n", TTF_GetError()); //verification.
    return;
  }
  SDL_Color color={0,0,0}; //couleur noir.

  resultat_surface=TTF_RenderText_Blended(font,resultat_text,color); //couleur mtaa l resultat o l police.

  resultat_pos.x=450; //position de la resultat.
  resultat_pos.y=400;

  SDL_BlitSurface(resultat_surface,NULL,fenetre,&resultat_pos);
  
  SDL_FreeSurface(resultat_surface); //liberation surface mtaa l resultat.
  TTF_CloseFont(font);
}
//l'animation de l'enigme.
void animer_enigme(Enigme E[5],int num, SDL_Surface *fenetre)
{
   static int i=0;

   if(i<5)
     {
       SDL_BlitSurface(E[num].anime_surface[i],NULL,fenetre,&E[num].anime_pos);
       SDL_Delay(900); //lwakt bin kol image o image.
       i++;
     }
    else if(i==5)
     {
       i=0;
     }

}
//liberation de la memoire allouee lel enigmes.
void free_enigme(Enigme E[7])
{
  int i;
  int j;
 for(i=0;i<7;i++)
 {
  //liberation de la memoire.
  SDL_FreeSurface(E[i].q_surface);
  SDL_FreeSurface(E[i].rep1_surface);
  SDL_FreeSurface(E[i].rep2_surface);
  for(j=0;j<5;j++)
  {
   SDL_FreeSurface(E[i].anime_surface[j]);
  }
 }
}

