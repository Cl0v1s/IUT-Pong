#ifndef Lib
#define Lib
#include <stdlib.h>
#include <string>
#include <SDL/SDL.h>
#include <SDL_image.h>
/********************************************************************************************
 * Projet: Anticipation (Un simple Pong avec effet d'inertie sur les palettes)
 * Fonction: Fichier Lib. Ensemble des commandes relatives à la SDL utilisées dans ce projet
 * ------------------------------------------------------------------------------------------
 * Auteurs: Nicholas Journet, Clovis Portron.
 *********************************************************************************************/
 #include <SDL/SDL_ttf.h>

#include <sstream>
#include <iostream>
#include <math.h>


// -- Point ---------------------
// Représente un Point ou un Vecteur selon les situations
// * Champs:
// "x" : position x du point (valeur horizontale du vecteur)
// "y" : position y du point (valeur verticale du vecteur)
// ----------------------------------------------
typedef struct
{
    int x;
    int y;
}Point;

// -- RGBA ---------------------
// Représente une couleur potentiallement transparente
// * Champs:
// "r" : rouge
// "g" : vert
// "b" : bleu
// "a" : opacité
// ----------------------------------------------
typedef struct
{
    int r;
    int g;
    int b;
    int a;
}RGBA;


//Charge une image
SDL_Surface *load_image(std::string filename);

//Charge une image avec la transparence
SDL_Surface *LoadImageTransparent(std::string filename, int r, int g , int b);

//Colle une image à l'écran
void applySurface(int x,int y,SDL_Surface *toapply, SDL_Surface *onapply, SDL_Rect* clip );

//retourne une valeur aléatoir'e comprise entre mi et ma
float aleatoire(float mi, float ma);

//retourne l'arrondiu d'un nombre decimal value
int round(float value);

//affiche du texte à l'écran
void drawText(std::string message,int x,int y,TTF_Font *font,int fontSize,RGBA textColor,SDL_Surface* &screen);

//retourne la taille occupée par un texte à l'écran
Point getTextSize(std::string text, TTF_Font *font);
#endif
