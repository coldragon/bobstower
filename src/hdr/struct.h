#ifndef HEADER_INCLUDED_STRUCT
#define HEADER_INCLUDED_STRUCT

#include "define.h"
#include "texture.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct
{
    long start;
    long now;
    long duration;

}leTimer;

typedef struct
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

}leBob;

typedef struct
{
    int tile[HCASE][WCASE];
    int tile2[HCASE][WCASE];
    int col[HCASE][WCASE];
    int obj[HCASE][WCASE];
	int sx, sy; // Spawn position in PIXEL !!
	int ex, ey; // Exit position in CASE !!
	int quitfloor;

}leMap;

typedef struct
{
    SDL_Rect pos, posOrigin;
    SDL_Rect d;
    leTimer mov;
    int exist;

}leProjectiles;

typedef struct
{
    leProjectiles projectiles[MAX_PROJECTILES_PAR_SORT];
    int skin;
    int last_use;
    int distanceattaque;
    int scale;
    int power;
    int speed;

}leSort;

typedef struct 
{
	// Son
	Mix_Chunk *sound1, *sound2, *sound3, *sound4, *sound5, *sound6, *sound7, *sound8, *sound9;
	Mix_Music *music1, *music2;
	// Etage
	int etage;
	leSort sort1;
	leSort sort1_enm;

}leAudio;

typedef struct
{
    char key[SDL_NUM_SCANCODES];
    int quit;

}leInput;


typedef struct
{
	long last;
	long actual;
	int activated;

} leLimiter;

typedef struct
{
	Texture *tileset;
	Texture *objset;
	Texture *guiset;
	Texture *sortset;
	Texture *screentitle;
	Texture *loose;

} leTexPack;


typedef struct
{
	leBob BOB;
	leBob ENM[ENNEMY_MAX];
	leAudio AUDIO;
	TTF_Font *FONT;
	SDL_Window *WINDOW;
	SDL_Renderer *RENDER;
	leMap *MAP;
	leInput *INPUT;
	leTexPack TEXPACK;
	leLimiter LIMITER;

} leCore;

#endif
