#include "Scene.h"

using namespace std;


// -- Menu ---------------------
// Affiche et gère le menu du jeu
// * paramètres entrées :
// - "screen" : La surface 'écran', principale du jeu
// * paramètre de sortie :
// - int, gamestate, renvoie l'état du jeu à la fin de l'éxecution du menu
// ----------------------------------------------
int menu(SDL_Surface* screen)
{
    // etat du jeu actuel
    int gameState = 0;
    bool done = false;
    // CHargement des polices
    TTF_Font *big = TTF_OpenFont("./assets/M.ttf",64);
    TTF_Font *regular = TTF_OpenFont("./assets/M.ttf",24);
    //Chargement du fond du menu
    SDL_Surface *background=load_image("assets/Game_background.jpg");
    bool start = true;
    while(!done)
    {
        //Gestion des évenements
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            //on quitte sur la fenetre SDL est fermée
            case SDL_QUIT:
                done = true;
                gameState = 2;
                break;

            }
        }

        //Insérer ici la logique de la phase de jeu
        //Gestion des Entrées de touches
        Uint8 *keystate = SDL_GetKeyState(NULL);

        //action à réaliser lorsque le joueur press echap
        if(keystate[SDLK_ESCAPE]){ done=true; gameState=2;}

        //gestion des mouvement des palettes
        if(keystate[SDLK_LEFT] || keystate[SDLK_RIGHT]){ start = !start;SDL_Delay(250);}

        //action à réaliser lorsque le joueur appuie sur espace
        if(keystate[SDLK_SPACE])
        {
            if(start)
            {
                gameState = 1;
                done = true;
            }
            else
            {
                gameState = 2;
                done = true;
            }
        }

        // On efface l'écran
        SDL_Rect clip;
        clip.x = 0; clip.y = 0; clip.h = WINDOW_HEIGHT; clip.w = WINDOW_WIDTH;
        applySurface(0,0,background,screen, &clip);
        Point p = getTextSize("Anticipation", big);
        RGBA c;
        c.r = 255;
        c.g = 255;
        c.b = 255;
        c.a = 255;
        drawText("Anticipation", WINDOW_WIDTH/2-p.x/2, WINDOW_HEIGHT/2-p.y/2-120,big,64,c,screen );

        //détermine le texte du menu à afficher
        string menu = "< Lancer >";
        if(!start)
            menu = "< Quitter >";

        //On affiche l'option du menu actuellement séléctionnée
        p = getTextSize(menu, regular);
        c.r = 255;
        c.g = 255;
        c.b = 255;
        c.a = 255;
        drawText(menu, WINDOW_WIDTH/2-p.x/1.5, WINDOW_HEIGHT/2-p.y/2+120,regular,24,c,screen );

        //afficher le texte "press space"
        p = getTextSize("- press space -", regular);
        c.r = 255;
        c.g = 255;
        c.b = 255;
        c.a = 255;
        drawText("- press space -", WINDOW_WIDTH/2-p.x/1.5, WINDOW_HEIGHT/2-p.y/2+200,regular,24,c,screen );

        //actualise l'écran
        SDL_Flip(screen);
        SDL_Delay(10);
    }
    //Libération des ressources utilisées par le menu
    SDL_FreeSurface(background);
    TTF_CloseFont(regular);
    TTF_CloseFont(big);
    return gameState;
}

// -- game ---------------------
// affiche et gère le déroulement du jeu
// * paramètres entrées :
// - "screen" : Surface écran, principale du jeu
// * paramètre de sortie : int, gamestate, renvoie l'état du jeu à la fin de l'edxécution du jeu
// ----------------------------------------------
int game(SDL_Surface* screen)
{

    // CHargement de la police utilisée
    TTF_Font *fonts = TTF_OpenFont("./assets/M.ttf",100);
    //initialisation du compte à rebours
    float counter = 4;
    //Chargemetnt du fond du jeu
    SDL_Surface *background=load_image("assets/Game_background.jpg");
    bool done = false;
    //Etat actuel du jeu
    int gameState = 1;


    //Initialisation des entitées
    //Utilisation d'un tableau pour ajouter de éventuellesz futures entitées telles que des bonus ou des malus etc..
    Entity entities[NB_ENTITIES];
    entities[0] =createEntity(0,0,"assets/ball.png");
    entities[1] = createEntity(0,0,"assets/player01.png");
    entities[2] = createEntity(0,0,"assets/player01.png");

    //On affecte un pointeur nminatif à chacune des entités principales pour plus de comodités
    Entity *balle = &entities[0];
    Entity *joueur1 = &entities[1];
    Entity *joueur2 = &entities[2];

    //on positionne correctement les entités
    joueur1 -> x = 5; joueur1 -> y = WINDOW_HEIGHT/2 - joueur1 -> height /2;
    joueur2 -> x = WINDOW_WIDTH - joueur2 -> width -5; joueur2 -> y = WINDOW_HEIGHT/2 - joueur2 -> height /2;
    replaceBall(balle);

    // points des deux joueurs
    int pointsj1 = 0;
    int pointsj2 = 0;

    while (!done)
    {
        //Gestion des évenements
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            //on quitte sur la fenetre SDL est fermée
            case SDL_QUIT:
                done = true;
                gameState = 2;
                break;

            }
        }


        //Insérer ici la logique de la phase de jeu
        //Gestion des Entrées de touches
        Uint8 *keystate = SDL_GetKeyState(NULL);

        //action à réaliser lorsque le joueur press echap
        if(keystate[SDLK_ESCAPE]){ done=true; gameState=0;SDL_Delay(150);}

        //gestion des mouvement des palettes
        if(keystate[SDLK_DOWN]){ joueur2->velocityY += 30;}
        if(keystate[SDLK_UP]){ joueur2->velocityY -= 30;}
        if(keystate[SDLK_z]){ joueur1->velocityY -= 30;}
        if(keystate[SDLK_s]){ joueur1->velocityY += 30;}


        //on teste les collisions de la balle avec les joueurs
        if (collision(*joueur1 , *balle) && balle->velocityX < 0 || collision(*joueur2 , *balle ) && balle->velocityX > 0)
        {
            if (balle->velocityX<0)
                balle->velocityX -= 0.2;
            else
                balle->velocityX +=0.2;
            balle->velocityX *=-1;
        }

        //On met à jour la position de tout les élements
        for(int i = 0; i<NB_ENTITIES;i++)
        {
            if(&entities[i] != balle)
                updateEntity(&entities[i]);
            else if(counter <= 0)
            {
                int score = updateBall(balle);
                if(score == 1)
                {
                    pointsj1 += 1;
                    replaceBall(balle);
                    counter = 4;
                }

                else if(score == 2)
                {
                    pointsj2 += 1;
                    replaceBall(balle);
                    counter = 4;
                }
            }

        }

        // On efface l'écran
        SDL_Rect clip;
        clip.x = 0; clip.y = 0; clip.h = WINDOW_HEIGHT; clip.w = WINDOW_WIDTH;
        applySurface(0,0,background,screen, &clip);
        //On affiche le score
        if(counter <= 0)
        {
            stringstream ss;
            ss << pointsj1 << " : " << pointsj2;
            string s = ss.str();
            Point p = getTextSize(s, fonts);
            RGBA color;
            color.r = 255;
            color.g = 255;
            color.b = 255;
            color.a = 80;
            drawText(s,WINDOW_WIDTH /2 - p.x / 1.5  ,WINDOW_HEIGHT/2-p.y/2,fonts,65,color,screen);
        }

        //On dessine tout les éléments
        for(int i = 0; i< NB_ENTITIES;i++)
        {
            drawEntity(&entities[i],screen);
        }

        //On gère et affiche le compteur si celui si est supérieur à zéro
        if(counter > 0)
        {
            counter -= 0.025;
        //On affiche le compteur
        stringstream ss;
        ss << ((int)counter) ;
        string s = ss.str();
        Point p = getTextSize(s, fonts);
        RGBA color;
        color.r = 255;
        color.g = 255;
        color.b = 255;
        color.a = 255;
        drawText(s,WINDOW_WIDTH /2 - p.x / 2  ,WINDOW_HEIGHT/2-p.y/2,fonts,65,color,screen);
        }


        //On met à jour l'écran
        SDL_Flip(screen);
        SDL_Delay(10);

        // On vérifie si il y a un vainqueur
        if(pointsj1 > 9 || pointsj2 > 9)
        {
            done = true;
            int winner = 1;
            if(pointsj2 > pointsj1)
                winner = 2;
            gameState = win(winner, screen);
        }
    }
    //On libère la mémoire utilisée avant de changer de scene
    SDL_FreeSurface(background);
    SDL_FreeSurface(joueur1->sprite.texture);
    SDL_FreeSurface(joueur2->sprite.texture);
    SDL_FreeSurface(balle->sprite.texture);
    TTF_CloseFont(fonts);
    return gameState;


}

// -- win ---------------------
// Affiche et gère l'écran de fin de partie
// * paramètres entrées :
// - "who" : entier indiquant 1 si le joueur 1 est vainqueur, 2 sinon
// - "screen"    : Surface écran, principale du jeu
//   couleur devient transparente !
// * paramètre de sortie : int, gamestate, indiquant l'état du jeu à la fin de l'exéctution de l'céran de fin de partie
// ----------------------------------------------
int win(int who, SDL_Surface* screen)
{
    //Etat par défaut du jeu après écran fin de partie (ici menu)
    int gameState = 0;
    bool done = false;
    //On charge les polices utilisées
    TTF_Font *font = TTF_OpenFont("./assets/M.ttf",24);
    // Chargement du fond del'écran de fin de partie
    SDL_Surface *background=load_image("assets/Game_background.jpg");
    // Détermination du texte à afficher en fonction du vainqueur
    string text = "Le joueur 1 a gagne !";
    if(who == 2)
        text = "Le joueur 2 a gagne !";
    while(!done)
    {
        //Gestion des évenements
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            //on quitte sur la fenetre SDL est fermée
            case SDL_QUIT:
                done = true;
                gameState = 2;
                break;

            }
        }


        //Insérer ici la logique de la phase de jeu
        //Gestion des Entrées de touches
        Uint8 *keystate = SDL_GetKeyState(NULL);

        //action à réaliser lorsque le joueur presse la touche espace
        if(keystate[SDLK_SPACE]){gameState = 0; done=true;}

        // On affiche le fond
        SDL_Rect clip;
        clip.x = 0; clip.y = 0; clip.h = WINDOW_HEIGHT; clip.w = WINDOW_WIDTH;
        applySurface(0,0,background,screen, &clip);
        // On affiche le texte indiquant l'identité du vainqueur
        Point p = getTextSize(text, font);
        RGBA c;
        c.r = 255;
        c.g = 255;
        c.b = 255;
        c.a = 255;
        drawText(text, WINDOW_WIDTH/2-p.x/1.5, WINDOW_HEIGHT/2-p.y/2,font,24,c,screen );
        // On affiche le texte 'press space'
        p = getTextSize("- press space -", font);
        c.r = 255;
        c.g = 255;
        c.b = 255;
        c.a = 255;
        drawText("- press space -", WINDOW_WIDTH/2-p.x/1.5, WINDOW_HEIGHT/2-p.y/2+50,font,24,c,screen );
        SDL_Flip(screen);
        SDL_Delay(10);
    }
    SDL_Delay(500);
    // On décharge les ressources utilisées dans l'écran de fin de partie
    TTF_CloseFont(font);
    SDL_FreeSurface(background);
    return gameState;
}

// -- quit ---------------------
// permet au jeu de quitter en déchargeant la mémoire proprement si besoin (en cas d'extensions futures)
// * paramètres entrées :
// - "done" : booléan, état globale de continité du jeu, si faux, on quitte complétement le jeu
// * paramètre de sortie : int, gamestate, état du jeu après appel de la fonction quit (inutile en l'état, pour extensions futures)
// ----------------------------------------------
int quit(bool &done)
{

    //Décharger ici tout les sprites initialisés
    done = true;
    return 0;
}

