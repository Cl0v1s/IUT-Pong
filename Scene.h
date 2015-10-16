/********************************************************************************************
 * Projet: Anticipation (Un simple Pong avec effet d'inertie sur les palettes)
 * Fonction: Fichier Scene, contient l'ensemble des écrans (scenes) du jeu
 * ------------------------------------------------------------------------------------------
 * Auteurs: Théo Bouzans, Clovis Portron
 * License: This work is licensed under the Creative Commons
 *          Attribution-NonCommercial-ShareAlike 4.0 International License.
 *********************************************************************************************/
#ifndef Scene
#define Scene

#include <stdlib.h>
#include <string>
#include "main.h"
#include "Entities.h"
#include <sstream>



int menu(SDL_Surface* screen);

int game(SDL_Surface* screen);

int win(int who, SDL_Surface* screen);

int pause();

int quit(bool &done);

#endif // Scene
