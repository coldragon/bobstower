#ifndef HEADER_INCLUDED_STRUCT
#define HEADER_INCLUDED_STRUCT

#include "define.h"
#include "texture.h"

typedef struct
{
	long last;
	long actual;
	int activated;

} leLimiter;

typedef struct
{
    int tile[HCASE][WCASE];
    int tile2[HCASE][WCASE];
    int col[HCASE][WCASE];
    int obj[HCASE][WCASE];
	int sy, sx; // Spawn position in PIXEL !!
	int ey, ex; // Exit position in CASE !!
	int quitfloor;

} leMap;

typedef struct
{
    char key[SDL_NUM_SCANCODES];
	int wheelup;
	int wheeldown;
	int quit;
	int leftclic;
	int leftclic_position_x;
	int leftclic_position_y;
	int rightclic;
	int rightclic_position_x;
	int rightclic_position_y;
	int mousex;
	int mousey;
	int focus;
	char *filedrop;

} leInput;

typedef struct
{
	int tile;
	int tile2;
	int obj;
	int col;
	int sp;
	int ex;
	int actualLayer;
	int actualTile;
	int fullscreen;

} leState;

typedef struct
{
	Texture *tileset;
	Texture *objset;
	Texture *gui;
	Texture *gui_exit_spawn;
	Texture *gui_col;
	Texture *gui_layer;
	Texture *gui_tileedit;

} leTexPack;

typedef struct
{
	SDL_Window *WINDOW;
	SDL_Renderer *RENDER;
	leMap *MAP;
	leInput *INPUT;
	leState STATE;	
	leTexPack TEXPACK;
	leLimiter LIMITER;

} leCore;

#endif
