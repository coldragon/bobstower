#ifndef HEADER_INCLUDED_STRUCT
#define HEADER_INCLUDED_STRUCT

#include "define.h"
#include "texture.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>

struct leBob
{
    SDL_Rect pos, posTemp;
    Texture *skin;
    SDL_Rect skinPos;
    //caract
    int speed;
    int hp;
    int hpMax;
    int money;
    int level;
    int luck;
    int fov;
    int attack;
    int attackspeed;
    int distattack;
    int collision;
    long tempsDeplacement;
    long tempsInitialDeplacement;
    long tempsAttack;
    long tempsInitialAttack;
};
typedef struct leBob leBob;

struct leMap
{
    int tile[HCASE][WCASE];
    int tile2[HCASE][WCASE];
    int col[HCASE][WCASE];
    int obj[HCASE][WCASE];
    int tpin[HCASE][WCASE];
    int tpout[HCASE][WCASE];
};
typedef struct leMap leMap;

struct leJeu
{
    // Son
    Mix_Chunk *son1;
    Mix_Chunk *son2;
    Mix_Chunk *son3;
    Mix_Chunk *son4;
    Mix_Chunk *son5;
    Mix_Chunk *son6;
    Mix_Chunk *son7;
    Mix_Chunk *son8;
    Mix_Chunk *son9;

    // Etage
    int etage;
};
typedef struct leJeu leJeu;

struct leInput
{
    char key[SDL_NUM_SCANCODES];
    int quit;
};
typedef struct leInput leInput;

#endif
