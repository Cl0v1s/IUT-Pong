/********************************************************************************************
 * Projet: Anticipation (Un simple Pong avec effet d'inertie sur les palettes)
 * Fonction: Fichier Entities, contient l'ensemble des fonctions relatives aux entités en jeu
 * ------------------------------------------------------------------------------------------
 * Auteurs: Théo Bouzans, Clovis Portron
 * License: This work is licensed under the Creative Commons
 *          Attribution-NonCommercial-ShareAlike 4.0 International License.
 *********************************************************************************************/

#ifndef Entities
#define Entities

#include <stdlib.h>
#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include "Lib.h"

// -- Sprite ----------------------------------------------------------------------------------
// Représente une image et ses informations
// * Champs:
// "frame" : index de frame, permettant une éventuelle animation (pour extensions futures)
// "texture" : surface SDL contenant les informations sur l'image en elle même
// "clip" : taille d'une frame, permettant une éventuelle animation (pour extensions futures)
// ---------------------------------------------------------------------------------------------
typedef struct
{
    int frame;
    SDL_Surface *texture;
    SDL_Rect clip;
}Sprite;


// -- Entity ---------------------------------------------------------------------------------------
// Représente un objet interractif en jeu et ses informations
// * Champs:
// "x" : position x de l'entité
// "y" : position y de l'entité
// "width" : largeur totale de l'entité
// "height" : hauteur totale de l'entité
// "velocityX" : vitesse horizontale de l'entité
// "velocityY" : vitesse verticale de l'entité
// "solid" : indique si l'entité est conçernée par les collisions ou non (pour extensions futures)
// "Sprite" : L'image de l'entité et ses informations
// -------------------------------------------------------------------------------------------------
typedef struct
{
    int x;
    int y;
    int width;
    int height;
    float velocityX;
    float velocityY;
    bool solid;
    Sprite sprite;
}Entity;

Sprite createSprite(std::string file);

Entity createEntity(int x, int y, std::string Sprite);

bool collision(Entity e1, Entity e2);

void updateEntity(Entity* e);

int updateBall(Entity* e);

void replaceBall(Entity* e);

void drawEntity(Entity* e,SDL_Surface *screen);

#endif // Entities
