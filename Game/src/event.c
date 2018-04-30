#include <SDL2/SDL.h>
#include <string.h>
#include "hdr/other_screen.h"
#include "hdr/struct.h"
#include "hdr/basic.h"
#include "hdr/collision.h"
#include "hdr/init.h"
#include "hdr/map.h"
#include "hdr/attack.h"


void inputReturn(leInput *INPUT)
{
	SDL_Event event;

	while(SDL_PollEvent(&event))

	{
		switch (event.type)
		{
		case SDL_QUIT:
			INPUT->quit=1;
			break;
		case SDL_KEYDOWN:
			INPUT->key[event.key.keysym.scancode]=1;
			break;
		case SDL_KEYUP:
			INPUT->key[event.key.keysym.scancode]=0;
			break;
		default:
			break;
		}
	}
}

void inputInit(leInput *INPUT)
{
	memset(INPUT->key, 0, sizeof(INPUT->key));
	INPUT->quit=0;
}


void mouvement(leInput *INPUT, SDL_Renderer *render,leBob *BOB, leMap *MAP, int *continuer, int *restartgame)
{
	// Deplacement
	BOB->posTemp.x=BOB->pos.x;
	BOB->posTemp.y=BOB->pos.y;

	if  (INPUT->quit)
	{
		*continuer = 0;
		*restartgame = 0;
	}
	if  (INPUT->key[SDL_SCANCODE_UP])
	{
		BOB->pos.y=BOB->pos.y-BOB->speed;
		if (collisionmap(&BOB->pos, MAP, 1, 32, 0, 4, 4) || collisionmap(&BOB->pos, MAP, 2, 0, 32, 4, 4))
			BOB->pos.y=BOB->posTemp.y;
		BOB->skinPos.x=TCASE;
		BOB->direction=0;
	}
	if  (INPUT->key[SDL_SCANCODE_DOWN])
	{
		BOB->pos.y=BOB->pos.y+BOB->speed;
		if (collisionmap(&BOB->pos, MAP, 1, 32, 0, 4, 4) || collisionmap(&BOB->pos, MAP, 2, 0, 32, 4, 4))
			BOB->pos.y=BOB->posTemp.y;
		BOB->skinPos.x=0;
		BOB->direction=2;
	}
	if  (INPUT->key[SDL_SCANCODE_LEFT])
	{
		BOB->pos.x=BOB->pos.x-BOB->speed;
		if (collisionmap(&BOB->pos, MAP, 1, 32, 0, 4, 4) || collisionmap(&BOB->pos, MAP, 2, 0, 32, 4, 4))
			BOB->pos.x=BOB->posTemp.x;
		BOB->skinPos.x=TCASE*2;
		BOB->direction=3;

	}
	if  (INPUT->key[SDL_SCANCODE_RIGHT])
	{
		BOB->pos.x=BOB->pos.x+BOB->speed;
		if (collisionmap(&BOB->pos, MAP, 1, 32, 0, 4, 4) || collisionmap(&BOB->pos, MAP, 2, 0, 32, 4, 4))
			BOB->pos.x=BOB->posTemp.x;
		BOB->skinPos.x=TCASE*3;
		BOB->direction=1;
	}
	if  (INPUT->key[SDL_SCANCODE_ESCAPE])
	{
		if(menu_escape(render, INPUT)==1)
		{
			*continuer = 0;
			*restartgame = 0;
		}
	}
}

void mov_enm(SDL_Renderer *render, leBob *ENM, leBob *BOB)
{
	int i;
	for (i=0; i<ENNEMY_MAX; i++)
	{
		if (ENM[i].exist)
		{
			if (ENM[i].tmov.now-ENM[i].tmov.start >= 50)
			{
				ENM[i].posTemp.x=ENM[i].pos.x;
				ENM[i].posTemp.y=ENM[i].pos.y;

				if (distancepoint(ENM[i].pos.x, ENM[i].pos.y, BOB->pos.x, BOB->pos.y)<ENM[i].fov)
				{
					int x, y;
					x=ENM[i].pos.x-BOB->pos.x;
					y=ENM[i].pos.y-BOB->pos.y;

					if (x<-3)
					{
						ENM[i].pos.x+=ENM[i].speed;
						ENM[i].direction=1;
					}
					if (x>3)
					{
						ENM[i].pos.x-=ENM[i].speed;
						ENM[i].direction=3;
					}
					if (y<-3)
					{
						ENM[i].pos.y+=ENM[i].speed;
						ENM[i].direction=2;
					}
					if (y>3)
					{
						ENM[i].pos.y-=ENM[i].speed;
						ENM[i].direction=0;
					}
				}

				ENM[i].tmov.start=ENM[i].tmov.now;
			}
			ENM[i].tmov.now=SDL_GetTicks();
		}
	}
}

void start_menu(leInput *INPUT, leState *STATE)
{
	SDL_Event event;
	while (STATE->startmenu)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			STATE->game_restarter = 0;
			STATE->game_is_running = 0;
			STATE->startmenu = 0;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_RETURN:
				STATE->startmenu = 0;
				break;
			default:;
			}
			break;
		default:;
		}
	}
}

void LOGICAL(leCore *CORE)
{
	// Input
	inputReturn(CORE->INPUT);

	// Mouvement
	mouvement(CORE->INPUT, CORE->RENDER, &CORE->ENTITYPACK.BOB, CORE->MAP, &CORE->STATE.game_is_running, &CORE->STATE.game_restarter);
	mov_enm(CORE->RENDER, CORE->ENTITYPACK.ENM, &CORE->ENTITYPACK.BOB);
	move_projectile(&CORE->AUDIO, &CORE->ENTITYPACK.BOB);

	// Collision
	collisionEnm(CORE->ENTITYPACK.ENM, CORE->MAP, &CORE->ENTITYPACK.BOB);
	sortcollision(CORE->MAP, CORE->ENTITYPACK.ENM, &CORE->AUDIO, &CORE->ENTITYPACK.BOB);
	objetcollision(CORE->MAP, &CORE->ENTITYPACK.BOB, &CORE->AUDIO);

	// Attaque
	attackcac_enm(CORE->ENTITYPACK.ENM, &CORE->ENTITYPACK.BOB, &CORE->AUDIO);
	attack_bob(&CORE->ENTITYPACK.BOB, &CORE->AUDIO, CORE->INPUT);

	// Ennemy mort
	for (int i = 0; i < ENNEMY_MAX; i++)
	{
		if (CORE->ENTITYPACK.ENM[i].hp < 1 && CORE->ENTITYPACK.ENM[i].exist == 1)
		{
			CORE->ENTITYPACK.ENM[i].exist = 0;
			CORE->ENTITYPACK.BOB.money += CORE->ENTITYPACK.ENM[i].money;
			CORE->STATE.enmTotal--;
		}
	}

	if (CORE->STATE.enmTotal < 1 && !CORE->STATE.endtrigger)
	{
		CORE->MAP->obj[CORE->MAP->ey][CORE->MAP->ex] = 9;
		CORE->STATE.endtrigger = 1;
	}
	if (CORE->MAP->quitfloor)
	{
		changemap_screen(CORE->RENDER);
		map_load(CORE->MAP);
		CORE->ENTITYPACK.BOB.pos.x = CORE->MAP->sx;
		CORE->ENTITYPACK.BOB.pos.y = CORE->MAP->sy;
		CORE->ENTITYPACK.BOB.posTemp.x = CORE->MAP->sx;
		CORE->ENTITYPACK.BOB.posTemp.y = CORE->MAP->sy;
		for (int i = 0; i < ENNEMY_MAX; i++)
			CORE->ENTITYPACK.ENM[i] = enm_init(CORE->ENTITYPACK.ENM[i], CORE->ENTITYPACK.BOB, CORE->MAP, CORE->RENDER);
		CORE->STATE.enmTotal = ENNEMY_MAX;
		CORE->MAP->quitfloor = 0; CORE->STATE.endtrigger = 0;
	}

	// Defaite
	if (CORE->ENTITYPACK.BOB.hp < 1)
	{
		if (CORE->ENTITYPACK.BOB.hp < 0)
			CORE->ENTITYPACK.BOB.hp = 0;

		CORE->STATE.game_is_running = 0;
		TextureRender(CORE->RENDER, CORE->TEXPACK.loose, 0, 0, NULL);
		SDL_RenderPresent(CORE->RENDER);
		SDL_Delay(2500);
	}
}