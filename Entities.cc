#include "Entities.h"
#include "main.h"
using namespace std;

// -- createSprite ---------------------
// Créer et initialise une structure Sprite.
// * paramètres entrées :
// - "file" : Fichier image à utiliser
// * paramètre de sortie :
// - Sprite initialisé
// ----------------------------------------------
Sprite createSprite(string file)
{
    Sprite e;
    e.texture = LoadImageTransparent(file,0,255,0);
    e.frame = 0;
    e.clip.x = 0;
    e.clip.y = 0;
    e.clip.w = e.texture->w;
    e.clip.h = e.texture->h;
    return e;
}

// -- createEntity ---------------------
// Créer et initialise une nouvelle entitée
// * paramètres entrées :
// - "x" : int, position x de l'entité
// - "y" : int, position y de l'entité
// - "sprite" : string, nom du fichier image à affecter à l'entité
// * paramètre de sortie :
// - Entity, entité crée et initialisée
// ----------------------------------------------
Entity createEntity(int x, int y, std::string sprite)
{
    Entity e;
    e.x = x;
    e.y = y;
    e.solid = true;
    e.velocityX = 0;
    e.velocityY = 0;
    e.sprite = createSprite(sprite);
    e.width = e.sprite.texture->w;
    e.height = e.sprite.texture->h;
    return e;
}

// -- updateEntity ---------------------
// Met à jour l'état de l'entité passée en paramètre
// * paramètres entrées :
// - "e" : Entity, l'entité à mettre à jour
// ----------------------------------------------
void updateEntity(Entity* e)
{
    // On affecte sa nouvelle position à l'entité en fonction de sa vélocité
    e->velocityX -= 0.03*e->velocityX;
    if(e->velocityY > 0)
        e->velocityY -= 0.03*e->velocityY;
    else
        e->velocityY -= 0.06*e->velocityY;
    if(e->velocityY > 0 && e-> velocityY < 5 || e->velocityY < 0 && e->velocityY > -5)
        e->velocityY = 0;
    e->x += e->velocityX*0.03;
    e->y += e->velocityY*0.03;
    //on vérifie que l'entité ne sort pas de l'écran
    if(e -> y < 0)
    {
        e -> y = 0;
        e->velocityY *= -1;
    }
    else if(e-> y + e -> height >= WINDOW_HEIGHT)
    {
        e-> y = WINDOW_HEIGHT - e -> height;
        e->velocityY *= -0.5;
    }
}

// -- updateBall ---------------------
// Met à jour l'état de l'entité passée en paramètre, en lui affectant un comportement de balle
// * paramètres entrées :
// - "e" : Entity, entité correspondant à la balle en jeu
// * paramètre de sortie :
// - int, indique 1 si le joueur 1 à marqué un point, 2 si c'est le joueur 2 qui a marqué et 0 sinon.
// ----------------------------------------------
int updateBall(Entity *e)
{
    // Affectation de la nouvelle position de la balle en fonction de sa velocité
    e->x += e->velocityX;
    e->y += e->velocityY;
    //on gère les rebonds de la balle sur le bord de l'écran
    if(e->y <= 0 || e->y+e->height>=WINDOW_HEIGHT)
    {
        e->velocityY *= -1;
    }
    //On teste si la balle est sortie sur l'in des bords verticaux de l'écran
    if(e->x+e->width < 0)
        return 2;
    if(e->x > WINDOW_WIDTH)
        return 1;

    return 0;
}

// -- replaceBall ---------------------
// Replace la balle au centre de l'écran
// * paramètres entrées :
// - "e" : Entity, entité correspondant à la balle en jeu
// ----------------------------------------------
void replaceBall(Entity *e)
{
    //On remplace la balle au centre de l'écran
    e->x = WINDOW_WIDTH/2 - e->width/2;
    e->y = WINDOW_HEIGHT/2 - e->height/2;
    //On lui affecte une nouvelle velocité et une nouvelle direction
    e->velocityX=10;
    e->velocityY=aleatoire(1,2);
    if(round(aleatoire(0,1))==1)
        e->velocityY *= -1;
    if(round(aleatoire(0,1))==1)
        e->velocityX *= -1;
}

// -- collision ---------------------
// Détermine si les deux entités passées en paramètres son entrées en collision entre elles ou non
// * paramètres entrées :
// - "e1" : Entity, l'une des entités à vérifier
// - "e2" : Entity, l'une des entités à vérifier
// * paramètre de sortie :
// - bool, true si les entités sont en collision, false sinon
// ----------------------------------------------
bool collision(Entity e1, Entity e2)
{
    if(e1.solid == true && e2.solid == true)
    {
        if(e2.x<=e1.x+e1.width && e2.x+e2.width>=e1.x && e2.y<=e1.y+e1.height && e2.y+e2.height>=e1.y)
        {
            return true;
        }
    }
    return false;
}

// -- drawEntity ---------------------
// Affiche l'entité passée en paramètre à l'écran
// * paramètres entrées :
// - "e" : Entity, entité à dessiner
// - "screen" : SDL_Surface, écran principale du jeu, surface sur laquelle déssiner l'entité
// ----------------------------------------------
void drawEntity(Entity* e, SDL_Surface* screen)
{
    applySurface(e->x,e->y,e->sprite.texture,screen, &e->sprite.clip);
}




