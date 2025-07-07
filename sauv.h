/**
 * @file sauv.h
 * @brief En-tête du module de gestion du menu de sauvegarde.
 *
 * Ce module fournit les fonctions permettant d'afficher un menu interactif
 * pour sauvegarder ou charger une partie dans un jeu.
 *
 * @author Votre Nom
 * @date 2025
 */

#ifndef SAUV_H
#define SAUV_H

#include <SDL/SDL.h>

/**
 * @brief Affiche le sous-menu de sauvegarde avec gestion des événements.
 *
 * Cette fonction gère l'affichage graphique, les interactions utilisateur
 * (clavier/souris), et les transitions entre les différents états du menu.
 *
 * @param ecran Surface SDL principale sur laquelle dessiner
 */
void afficher_sous_menu_sauvegarde(SDL_Surface *ecran);

/**
 * @brief Simule le chargement d'une sauvegarde.
 *
 * Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Charger".
 *
 * @param ecran Surface SDL principale (non utilisée ici)
 */
void charger_jeu(SDL_Surface *ecran);

/**
 * @brief Simule le démarrage d'une nouvelle partie.
 *
 * Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Nouvelle Partie".
 *
 * @param ecran Surface SDL principale (non utilisée ici)
 */
void nouvelle_partie(SDL_Surface *ecran);

#endif // SAUV_H
