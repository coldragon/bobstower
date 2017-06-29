#ifndef HEADER_INCLUDED_STRUCT
#define HEADER_INCLUDED_STRUCT

#include "define.h"
#include "texture.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>

struct leTimer
{
    long start;
    long now;
    long duration;
};
typedef struct leTimer leTimer;

struct leBob
{
    SDL_Rect pos, posTemp;
    Texture *skin;
    SDL_Rect skinPos;
    //caract
    int direction;
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
    int exist;
    leTimer tmov;
    leTimer tatt;
};
typedef struct leBob leBob;

struct leMap
{
    int tile[HCASE][WCASE];
    int tile2[HCASE][WCASE];
    int col[HCASE][WCASE];
    int obj[HCASE][WCASE];
	int sx, sy; // Spawn position in PIXEL !!
	int ex, ey; // Exit position in CASE !!
	int quitfloor;
};
typedef struct leMap leMap;

struct leProjectiles
{
    SDL_Rect pos, posOrigin;
    SDL_Rect d;
    leTimer mov;
    int exist;
};
typedef struct leProjectiles leProjectiles;

struct leSort
{
    leProjectiles projectiles[MAX_PROJECTILES_PAR_SORT];
    int skin;
    int last_use;
    int distanceattaque;
    int scale;
    int power;
    int speed;
};
typedef struct leSort leSort;

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
    leSort sort1;
    leSort sort1_enm;
};
typedef struct leJeu leJeu;

struct leInput
{
    char key[SDL_NUM_SCANCODES];
    int quit;
};
typedef struct leInput leInput;

#endif
