#include "hdr/texture.h"
#include "hdr/struct.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "hdr/affichage.h"
#include "hdr/event.h"

void open_sdl_shit()
{
	srand(time(NULL));
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER );
}

void close_sdl_shit()
{
	SDL_Quit();
}

void coreInit(leCore *CORE)
{
	CORE->WINDOW = SDL_CreateWindow(
		"Bob's Tower Map Editor",
		SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
		WWIN,HWIN,SDL_WINDOW_BORDERLESS);
	CORE->RENDER = SDL_CreateRenderer(CORE->WINDOW, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	CORE->TEXPACK.tileset = TextureCreate(CORE->RENDER, "res/img/tileset.png", 255, 0, 255, 255);
	SDL_SetTextureBlendMode(CORE->TEXPACK.tileset->handle, SDL_BLENDMODE_BLEND);
	CORE->TEXPACK.objset = TextureCreate(CORE->RENDER, "res/img/objset.png", 255, 0, 255, 255);
	CORE->TEXPACK.gui = TextureCreate(CORE->RENDER, "res/img/gui_editor.png", 255, 0, 255, 255);
	CORE->TEXPACK.gui_exit_spawn = TextureCreate(CORE->RENDER, "res/img/gui_exit_spawn.png", 255, 0, 255, 255);
	CORE->TEXPACK.gui_col = TextureCreate(CORE->RENDER, "res/img/gui_col.png", 255, 0, 255, 255);
	CORE->TEXPACK.gui_layer = TextureCreate(CORE->RENDER, "res/img/gui_layer.png", 255, 0, 255, 255);
	CORE->TEXPACK.gui_tileedit = TextureCreate(CORE->RENDER, "res/img/gui_tileedit.png", 255, 0, 255, 255);
	CORE->INPUT = calloc(1, sizeof(leInput));
	CORE->MAP = calloc(1, sizeof(leMap));
	memset(&CORE->STATE, 0, sizeof(leState)); 
	CORE->STATE.tile = 1; CORE->STATE.tile2 = 1;
	CORE->STATE.col = 1; CORE->STATE.obj = 1;
	CORE->STATE.sp = 1; CORE->STATE.ex = 1;
	CORE->STATE.actualTile = 1;
}

void coreFree(leCore *CORE)
{
	SDL_DestroyRenderer(CORE->RENDER);
	SDL_DestroyWindow(CORE->WINDOW);
	TextureFree(CORE->TEXPACK.gui);
	TextureFree(CORE->TEXPACK.gui_exit_spawn);
	TextureFree(CORE->TEXPACK.objset);
	TextureFree(CORE->TEXPACK.tileset);
	TextureFree(CORE->TEXPACK.gui_tileedit);
	TextureFree(CORE->TEXPACK.gui_col);
	TextureFree(CORE->TEXPACK.gui_layer);
	free(CORE->INPUT);
	free(CORE->MAP);
}

void mainLoop(leCore *CORE)
{
	while (!CORE->INPUT->quit)
	{
		CORE->LIMITER.actual = SDL_GetTicks();
		if (CORE->LIMITER.actual - CORE->LIMITER.last > LOGICAL_TICKS_LIMITER)
		{
			LOGICAL(CORE);
			CORE->LIMITER.last = CORE->LIMITER.actual;
		}
		else
			SDL_Delay(LOGICAL_TICKS_LIMITER - (CORE->LIMITER.actual - CORE->LIMITER.last));
		AFFICHAGE(CORE);
	}
}