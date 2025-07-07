#ifndef ENIGME_H
#define ENIGME_H
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <SDL/SDL.h>
//largeur et l'hauteur de la fenetre.
#define SCREEN_H 1100
#define SCREEN_W 800

typedef struct 
{
 char question[200]; //tableau de caractères,stocke la question,yhez 200 caractères.
 //tableau de caractères,stocke les réponses, kol tableau yhez 20 caractères.
 char rep1[20];
 char rep2[20];
 //des pointeurs vers des surfaces SDL.
 SDL_Surface* q_surface;
 SDL_Surface* rep1_surface;
 SDL_Surface* rep2_surface;
 //structure qui definissent les positions des surfaces de la question et des réponses a l'ecran.
 SDL_Rect q_pos;
 SDL_Rect rep1_pos;
 SDL_Rect rep2_pos;
 SDL_Surface* anime_surface[5];//tableau de pointeurs vers des surfaces SDL.
 SDL_Rect anime_pos;//structure qui definit la position de l'animation a l'ecran.
 int correct;//un entier qui indique anehi l reponse shiha.
}Enigme; //structure enigme.

void generer_enigme(Enigme E[7],char filename[]);
int  alea_enigme(Enigme E[7]);
void afficher_enigme(Enigme E[7],int num_e, SDL_Surface* fenetre);
void afficher_resultat(char resultat_text[],SDL_Surface* fenetre);
void animer_enigme(Enigme E[5],int num, SDL_Surface *fenetre);
void free_enigme(Enigme E[7]);
#endif



