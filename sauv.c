/**
 * @file sauv.c
 * @brief Implémentation des fonctions pour afficher et gérer un menu de sauvegarde.
 *
 * Ce module permet d'afficher un sous-menu interactif avec deux options :
 * "Oui" (pour passer à l'écran suivant) et "Non" (pour quitter), avec gestion
 * des événements souris, texte SDL et fond d'écran.
 *
 * @author Votre Nom
 * @date 2025
 */

#include "sauv.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>

/**
 * @brief Affiche un sous-menu demandant si l'utilisateur souhaite sauvegarder le jeu.
 *
 * Cette fonction charge toutes les images nécessaires, initialise la police,
 * affiche le texte "Voulez-vous sauvegarder le jeu ?", gère les boutons
 * "Oui"/"Non", et permet la transition vers un autre écran ou la fermeture du menu.
 *
 * @param ecran La surface SDL principale sur laquelle dessiner
 */
void afficher_sous_menu_sauvegarde(SDL_Surface *ecran) {
    // Chargement du fond d'écran
    SDL_Surface *background = IMG_Load("background.png");
    if (!background)
        printf("Erreur : background.png non trouvé.\n");

    // Chargement des images des boutons normaux et survolés
    SDL_Surface *boutonOui = IMG_Load("bouton_oui.png");
    SDL_Surface *boutonOui1 = IMG_Load("bouton_oui1.png");
    SDL_Surface *boutonNon = IMG_Load("bouton_non.png");
    SDL_Surface *boutonNon1 = IMG_Load("bouton_non1.png");
    SDL_Surface *boutonCharger = IMG_Load("charger.png");
    SDL_Surface *boutonCharger1 = IMG_Load("charger1.png");
    SDL_Surface *boutonNpartie = IMG_Load("Npartie.png");
    SDL_Surface *boutonNpartie1 = IMG_Load("Npartie1.png");

    // Vérification que toutes les images sont chargées
    if (!boutonOui || !boutonOui1 || !boutonNon || !boutonNon1 ||
        !boutonCharger || !boutonCharger1 || !boutonNpartie || !boutonNpartie1) {
        printf("Erreur de chargement d'une image.\n");
        return;
    }

    // Initialisation de l'audio
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        printf("Erreur d'ouverture audio : %s\n", Mix_GetError());
        return;
    }

    // Chargement de la musique de fond
    Mix_Music *musique = Mix_LoadMUS("music.mp3");
    if (!musique)
        printf("Erreur : music.mp3 non trouvé.\n");

    // Lancement de la musique en boucle
    Mix_PlayMusic(musique, -1);

    // Positions des éléments graphiques
    SDL_Rect posBackground = {0, 0};
    SDL_Rect posBoutonOui = {100, 200};
    SDL_Rect posBoutonNon = {400, 200};
    SDL_Rect posBoutonCharger = {100, 400};
    SDL_Rect posBoutonNpartie = {400, 400};

    SDL_Event event;
    int running = 1;
    int etat_affichage = 0; // 0: Oui/Non, 1: Charger/Npartie

    // Initialisation de la bibliothèque TTF
    if (TTF_Init() == -1) {
        printf("Erreur d'initialisation TTF : %s\n", TTF_GetError());
        return;
    }

    // Chargement de la police
    TTF_Font *police = TTF_OpenFont("arial.ttf", 36);
    if (!police) {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
        TTF_Quit();
        return;
    }

    // Couleur du texte (blanc)
    SDL_Color couleurTexte = {255, 255, 255};

    // Création de la surface du texte
    SDL_Surface *texteSurface = TTF_RenderText_Blended(police,
        "Voulez-vous sauvegarder le jeu ?", couleurTexte);
    SDL_Rect posTexte = {200, 100}; // Position du texte à l'écran

    // Boucle principale
    while (running) {
        // Affichage du fond d'écran
        SDL_BlitSurface(background, NULL, ecran, &posBackground);

        // Affichage conditionnel des boutons selon l'état d'affichage
        if (etat_affichage == 0) {
            SDL_BlitSurface(boutonOui, NULL, ecran, &posBoutonOui);
            SDL_BlitSurface(boutonNon, NULL, ecran, &posBoutonNon);
            if (texteSurface)
                SDL_BlitSurface(texteSurface, NULL, ecran, &posTexte);
        } else if (etat_affichage == 1) {
            SDL_BlitSurface(boutonCharger, NULL, ecran, &posBoutonCharger);
            SDL_BlitSurface(boutonNpartie, NULL, ecran, &posBoutonNpartie);
        }

        // Mise à jour de l'écran
        SDL_Flip(ecran);

        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_MOUSEMOTION:
                    if (etat_affichage == 0) {
                        // Bouton Oui survolé
                        if (event.motion.x >= 100 && event.motion.x <= 300 &&
                            event.motion.y >= 200 && event.motion.y <= 350) {
                            SDL_BlitSurface(boutonOui1, NULL, ecran, &posBoutonOui);
                            SDL_Flip(ecran);
                            SDL_Delay(10);
                        }
                        // Bouton Non survolé
                        if (event.motion.x >= 400 && event.motion.x <= 600 &&
                            event.motion.y >= 200 && event.motion.y <= 350) {
                            SDL_BlitSurface(boutonNon1, NULL, ecran, &posBoutonNon);
                            SDL_Flip(ecran);
                            SDL_Delay(10);
                        }
                    } else if (etat_affichage == 1) {
                        // Bouton Charger survolé
                        if (event.motion.x >= 90 && event.motion.x <= 310 &&
                            event.motion.y >= 390 && event.motion.y <= 460) {
                            SDL_BlitSurface(boutonCharger1, NULL, ecran, &posBoutonCharger);
                            SDL_Flip(ecran);
                            SDL_Delay(10);
                        }
                        // Bouton Nouvelle Partie survolé
                        if (event.motion.x >= 390 && event.motion.x <= 510 &&
                            event.motion.y >= 390 && event.motion.y <= 460) {
                            SDL_BlitSurface(boutonNpartie1, NULL, ecran, &posBoutonNpartie);
                            SDL_Flip(ecran);
                            SDL_Delay(10);
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (etat_affichage == 0) {
                        // Clic sur "Oui"
                        if (event.button.x >= 100 && event.button.x <= 300 &&
                            event.button.y >= 200 && event.button.y <= 350) {
                            etat_affichage = 1;
                        }
                        // Clic sur "Non"
                        if (event.button.x >= 400 && event.button.x <= 600 &&
                            event.button.y >= 200 && event.button.y <= 350) {
                            running = 0;
                        }
                    } else if (etat_affichage == 1) {
                        // Clic sur "Charger"
                        if (event.button.x >= 100 && event.button.x <= 300 &&
                            event.button.y >= 400 && event.button.y <= 450) {
                            charger_jeu(ecran);
                        }
                        // Clic sur "Nouvelle Partie"
                        if (event.button.x >= 400 && event.button.x <= 500 &&
                            event.button.y >= 400 && event.button.y <= 450) {
                            nouvelle_partie(ecran);
                        }
                    }
                    break;
            }
        }
    }

    // Nettoyage des ressources
    if (texteSurface)
        SDL_FreeSurface(texteSurface);
    TTF_CloseFont(police);
    TTF_Quit();

    Mix_FreeMusic(musique);
    Mix_CloseAudio();

    // Libération des surfaces graphiques
    SDL_FreeSurface(background);
    SDL_FreeSurface(boutonOui);
    SDL_FreeSurface(boutonOui1);
    SDL_FreeSurface(boutonNon);
    SDL_FreeSurface(boutonNon1);
    SDL_FreeSurface(boutonCharger);
    SDL_FreeSurface(boutonCharger1);
    SDL_FreeSurface(boutonNpartie);
    SDL_FreeSurface(boutonNpartie1);
}

/**
 * @brief Simule le chargement d'une sauvegarde.
 *
 * Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Charger".
 * Elle affiche simplement un message dans la console.
 *
 * @param ecran Surface SDL principale (non utilisée ici)
 */
void charger_jeu(SDL_Surface *ecran) {
    printf("Option 'Charger' sélectionnée.\n");
}

/**
 * @brief Simule le démarrage d'une nouvelle partie.
 *
 * Cette fonction est appelée lorsque l'utilisateur clique sur le bouton "Nouvelle Partie".
 * Elle affiche simplement un message dans la console.
 *
 * @param ecran Surface SDL principale (non utilisée ici)
 */
void nouvelle_partie(SDL_Surface *ecran) {
    printf("Option 'Nouvelle partie' sélectionnée.\n");
}
