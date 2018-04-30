#include <SDL2/SDL.h>
#include <stdio.h>
#include "hdr/texture.h"
#include "hdr/struct.h"
#include "hdr/event.h"

extern const SDL_Color WHITE;

void cleanScreen(SDL_Renderer* render, int r, int g, int b)
{
    SDL_SetRenderDrawColor(render, r, g, b, 255);
    SDL_RenderClear(render);
}

void afficherMap_layer1(SDL_Renderer* render, Texture* tileset, leMap *MAP)
{
	SDL_Rect posTile = {0,0,TCASE,TCASE};
    const int wtileset = tileset->w/TCASE;
    for (int i=0; i<HCASE; i++)
        for (int j=0; j<WCASE; j++)
        {
            posTile.x=TCASE*(MAP->tile[i][j]%(wtileset));
            posTile.y=TCASE*(MAP->tile[i][j]/(wtileset));
            TextureRender(render, tileset, j*TCASE, i*TCASE, &posTile);
        }
}

void afficherMap_layer2(SDL_Renderer* render, Texture* tileset, leMap *MAP)
{
    SDL_Rect posTile = {0,0,TCASE,TCASE};
    const int wtileset = tileset->w/TCASE;
    for (int i=0; i<HCASE; i++)
        for (int j=0; j<WCASE; j++)
        {
            posTile.x=TCASE*(MAP->tile2[i][j]%(wtileset));
            posTile.y=TCASE*(MAP->tile2[i][j]/(wtileset));
            if (MAP->tile2[i][j])
                TextureRender(render, tileset, j*TCASE, i*TCASE, &posTile);
        }
}

void afficherObj(SDL_Renderer* render, Texture* objset, leMap *MAP)
{
	SDL_Rect posObj = {0,0,TCASE,TCASE};
    const int wobjset = objset->w/TCASE;
    for (int i=0; i<HCASE; i++)
        for (int j=0; j<WCASE; j++)
        {
            posObj.x=TCASE*(MAP->obj[i][j]%(wobjset));
            posObj.y=TCASE*(MAP->obj[i][j]/(wobjset));
            TextureRender(render, objset, j*TCASE + 2, i*TCASE + 1, &posObj);
        } 
}

void afficherCol(SDL_Renderer* render, leMap *MAP, Texture *gui)
{
	for (int i = 0; i<HCASE; i++)
		for (int j = 0; j < WCASE; j++)
		{
			if (MAP->col[i][j] == 1)
			{
				SDL_Rect rect = { 0,0,32,32 }; TextureRender(render, gui, j*TCASE, i*TCASE, &rect);
			}

			if (MAP->col[i][j] == 2)
			{
				SDL_Rect rect = { 32,0,32,32 }; TextureRender(render, gui, j*TCASE, i*TCASE, &rect);
			}
		}
}

void afficherSpawn(SDL_Renderer* render, leMap *MAP, Texture* gui)
{

	if (MAP->sx != 0)
	{
		SDL_Rect rect = {0,0,32,32}; TextureRender(render, gui, MAP->sx, MAP->sy, &rect);
	}
}

void afficherExit(SDL_Renderer* render, leMap *MAP, Texture* gui)
{
	if (MAP->ex != 0)
	{
		SDL_Rect rect = { 32,0,32,32 }; TextureRender(render, gui, MAP->ex*TCASE, MAP->ey*TCASE, &rect);
	}
}

void afficherGui(SDL_Renderer* render, leInput *INPUT, Texture* gui)
{
	if (INPUT->focus)
	{
		// Black menu bar
		SDL_Rect rect = { 0,0,800,32 };
		TextureRender(render, gui, 0, 0, &rect);
	}
	else
	{
		// Grey menu bar
		SDL_Rect rect = { 0,32,800,32 };
		TextureRender(render, gui, 0, 0, &rect);

	}}

void afficherGuiLayer(SDL_Renderer* render, Texture* gui, leState *STATE)
{
	SDL_Rect rect = { 0,0,16,16 };
	SDL_Rect rect2 = { 16,0,32,16 };
	// layer1
	if (STATE->tile==1)
		TextureRender(render, gui, 0, 0, &rect);
	if (STATE->actualLayer==0)
		TextureRender(render, gui, 64, 0, &rect2);

	// layer2
	if (STATE->tile2 == 1)
		TextureRender(render, gui, 0, 16, &rect);
	if (STATE->actualLayer == 1)
		TextureRender(render, gui, 64, 16, &rect2);

	// obj
	if (STATE->obj == 1)
		TextureRender(render, gui, 104, 0, &rect);
	if (STATE->actualLayer == 2)
		TextureRender(render, gui, 168, 0, &rect2);

	// col
	if (STATE->col == 1)
		TextureRender(render, gui, 104, 16, &rect);
	if (STATE->actualLayer == 3)
		TextureRender(render, gui, 168, 16, &rect2);

	// spawn
	if (STATE->sp == 1)
		TextureRender(render, gui, 208, 0, &rect);
	if (STATE->actualLayer == 4)
		TextureRender(render, gui, 272, 0, &rect2);

	// exit
	if (STATE->ex == 1)
		TextureRender(render, gui, 208, 16, &rect);
	if (STATE->actualLayer == 5)
		TextureRender(render, gui, 272, 16, &rect2);
}

void afficherTileEdit(SDL_Renderer* render, leTexPack TEXPACK, leInput *INPUT, leState *STATE)
{
	int x = 0, y = 0; caseReturn(INPUT, &x, &y);
	if (STATE->actualLayer < 2) // Tile
	{
		const int wtileset = TEXPACK.tileset->w / TCASE;
		SDL_SetTextureAlphaMod(TEXPACK.tileset->handle, 110);

		SDL_Rect rect = { TCASE*(STATE->actualTile % (wtileset)) , TCASE*(STATE->actualTile / (wtileset)),TCASE,TCASE };
		TextureRender(render, TEXPACK.tileset, x*TCASE, y*TCASE, &rect);
		SDL_SetTextureAlphaMod(TEXPACK.tileset->handle, 255);
	}
	if (STATE->actualLayer == 2) // Obj
	{
		const int wobjset = TEXPACK.objset->w / TCASE;
		SDL_SetTextureAlphaMod(TEXPACK.objset->handle, 110);
		SDL_Rect rect = { TCASE*(STATE->actualTile % (wobjset)) , TCASE*(STATE->actualTile / (wobjset)),TCASE,TCASE };
		TextureRender(render, TEXPACK.objset, x*TCASE, y*TCASE, &rect);
		SDL_SetTextureAlphaMod(TEXPACK.objset->handle, 255);
	}
	if (STATE->actualLayer == 3) // Col
	{
		if (STATE->actualTile)
		{
			SDL_Rect rect = { TCASE*(STATE->actualTile-1),0,TCASE, TCASE };
			TextureRender(render, TEXPACK.gui_col, x*TCASE, y*TCASE, &rect);
		}
	}
	if (STATE->actualLayer == 4) // Spawn
	{
		SDL_Rect rect = { 0,0,TCASE, TCASE };
		TextureRender(render, TEXPACK.gui_exit_spawn, INPUT->mousex, INPUT->mousey, &rect);
	}
	if (STATE->actualLayer == 5) // Exit
	{
		SDL_Rect rect = { 32,0,TCASE, TCASE };
		TextureRender(render, TEXPACK.gui_exit_spawn, x*TCASE, y*TCASE, &rect);
	}

}

void AFFICHAGE(leCore *CORE)
{
	if (CORE->STATE.tile == 0)
		cleanScreen(CORE->RENDER, 50, 50, 50);
	if (CORE->STATE.tile == 1)
		afficherMap_layer1(CORE->RENDER, CORE->TEXPACK.tileset, CORE->MAP);
	if (CORE->STATE.obj == 1)
		afficherObj(CORE->RENDER, CORE->TEXPACK.objset, CORE->MAP);
	if (CORE->STATE.tile2 == 1)
		afficherMap_layer2(CORE->RENDER, CORE->TEXPACK.tileset, CORE->MAP);
	if (CORE->STATE.col == 1)
		afficherCol(CORE->RENDER, CORE->MAP, CORE->TEXPACK.gui_col);
	if (CORE->STATE.sp == 1)
		afficherSpawn(CORE->RENDER, CORE->MAP, CORE->TEXPACK.gui_exit_spawn);
	if (CORE->STATE.ex == 1)
		afficherExit(CORE->RENDER, CORE->MAP, CORE->TEXPACK.gui_exit_spawn);

	afficherTileEdit(CORE->RENDER, CORE->TEXPACK, CORE->INPUT, &CORE->STATE);
	afficherGui(CORE->RENDER, CORE->INPUT, CORE->TEXPACK.gui);
	afficherGuiLayer(CORE->RENDER, CORE->TEXPACK.gui_layer, &CORE->STATE);

	SDL_RenderPresent(CORE->RENDER);
}