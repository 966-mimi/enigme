/**
 * @file main.c
 * @brief Point d'entrée principal du programme.
 *
 * Ce fichier contient la fonction main qui initialise SDL, crée la fenêtre principale
 * et appelle la fonction d'affichage du menu de sauvegarde.
 *
 * @author Votre Nom
 * @date 2025
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "sauv.h"

/**
 * @brief Fonction principale du programme.
 *
 * Initialise SDL, crée la fenêtre graphique, affiche le sous-menu de sauvegarde,
 * puis quitte proprement SDL.
 *
 * @return int Code de retour du programme (0 = succès, autre = erreur)
 */
int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("Erreur d'initialisation SDL : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!ecran) {
        printf("Erreur de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    afficher_sous_menu_sauvegarde(ecran);

    SDL_Quit();
    return 0;
}
