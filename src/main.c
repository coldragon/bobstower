#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "hdr/texture.h"
#include "hdr/struct.h"
#include "hdr/affichage.h"
#include "hdr/init.h"
#include "hdr/event.h"
#include "hdr/collision.h"
#include "hdr/define.h"
#include "hdr/attack.h"
#include "hdr/map.h"
#include "hdr/other_screen.h"

const SDL_Color WHITE = { 255,255,255 };

int main(int argc, char* args[])
{
	leMap MAP1;
	leBob BOB0 = { 0 };
	leBob ENM[ENNEMY_MAX] = { 0 };
	leJeu JEU = { 0 };
	leInput INPUT = { 0 };
	int continuer = 1;
	int restartgame = 1;
	int startmenu = 1;
	int i;
	srand((unsigned int)time(NULL));
	// Variable de SDL
	SDL_Window *window;
	SDL_Renderer* render = { 0 };
	TTF_Font *police = { 0 };
	Mix_Music *musique, *musique2;
	Texture *tileset;
	Texture *objset;
	Texture *guiset;
	Texture *sortset;
	Texture *screentitle;
	Texture *loose;

	open_sdl_shit();

	window = SDL_CreateWindow("Bob's tower Alpha",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WWIN,HWIN,0);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	tileset = TextureCreate(render, "res/tileset.png", 255, 0, 255, 255);
	objset = TextureCreate(render, "res/objset.png", 255, 0, 255, 255);
	screentitle = TextureCreate(render, "res/screentitle.png", 255, 0, 255, 255);
	sortset = TextureCreate(render, "res/sortset.png", 255, 0, 255, 255);
	guiset = TextureCreate(render, "res/guiset.png", 255, 0, 255, 255);
	loose = TextureCreate(render, "res/loose.png", 255, 0, 255, 255);
	police = TTF_OpenFont("ttf/FiraSans-Medium.ttf", 10);

	while (restartgame)
	{
		musique = Mix_LoadMUS("snd/music.ogg");
		musique2 = Mix_LoadMUS("");
		inputInit(&INPUT);
		startmenu = 1;
		continuer = 1;
		TextureRender(render, screentitle, 0, 0, NULL);
		SDL_RenderPresent(render);
		Mix_PlayMusic(musique, -1);
		Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

		while (startmenu)
		{
			menuavantjeux(&INPUT, &startmenu, &restartgame, &continuer);
		}

		map_init(&MAP1);
		map_load(&MAP1);

		BOB0 = bob_init(BOB0, render);
		BOB0.pos.x = MAP1.sx;
		BOB0.pos.y = MAP1.sy;
		BOB0.posTemp.x = MAP1.sx;
		BOB0.posTemp.y = MAP1.sy;

		for (i = 0; i < ENNEMY_MAX; i++)
			ENM[i] = enm_init(ENM[i], BOB0, &MAP1, render);
		int enmTotal = ENNEMY_MAX;
		int endtrigger = 0;
		JEU.son1 = Mix_LoadWAV("snd/loot1.wav"); // loot1
		JEU.son2 = Mix_LoadWAV("snd/loot2.wav");  // loot2
		JEU.son3 = Mix_LoadWAV("snd/loot3.wav"); // loot3
		JEU.son4 = Mix_LoadWAV("snd/hit1.wav"); // hit1
		JEU.son5 = Mix_LoadWAV("snd/mort1.wav"); // mort1
		JEU.son6 = Mix_LoadWAV("snd/fireball1.wav"); // hit1
		JEU.son7 = Mix_LoadWAV("snd/attackenm.wav"); // hit1
		JEU.son8 = Mix_LoadWAV("snd/hit3.ogg");

		JEU.etage = 1;

		sort_init(&JEU, render);

		Mix_Volume(1, 65);
		Mix_Volume(2, 65);
		Mix_Volume(3, 65);
		Mix_Volume(4, 65);

		Mix_PlayMusic(musique2, -1);
		Mix_VolumeMusic(25);
		Mix_PauseMusic();

		long t, t0 = 0;
		static const int FPS = 60;
		int TICKS = 1000 / FPS;
		BOB0.pos.x = MAP1.sy;
		BOB0.pos.y = MAP1.sx;
		while (continuer)
		{
			t = SDL_GetTicks();

			if (t - t0 > TICKS)
			{
				// Input
				inputReturn(&INPUT);

				// Mouvement
				mouvement(&INPUT, render, &BOB0, &MAP1, &continuer, &restartgame);
				mov_enm(render, ENM, &BOB0);
				move_projectile(&JEU, &BOB0);

				// Collision
				collisionEnm(ENM, &MAP1, &BOB0);
				sortcollision(&MAP1, ENM, &JEU, &BOB0);
				objetcollision(&MAP1, &BOB0, &JEU);

				// Attaque
				attackcac_enm(ENM, &BOB0, &JEU);
				attack_bob(&BOB0, &JEU, &INPUT);

				// Affichage
				AfficherMap_layer1(render, tileset, MAP1);
				AfficherObj(render, objset, MAP1);
				AfficherBob(render, &BOB0);
				AfficherEnm(render, ENM);
				AfficherSort(render, sortset, &JEU);
				AfficherMap_layer2(render, tileset, MAP1);
				AfficherGui(render, guiset, &BOB0, police);
				SDL_RenderPresent(render);

				// Defaite
				if (BOB0.hp < 1)
				{
					if (BOB0.hp < 0)
						BOB0.hp = 0;

					continuer = 0;
					TextureRender(render, loose, 0, 0, NULL);
					SDL_RenderPresent(render);
					SDL_Delay(2500);
				}

				// Ennemy mort
				for (i = 0; i < ENNEMY_MAX; i++)
				{
					if (ENM[i].hp < 1 && ENM[i].exist == 1)
					{
						ENM[i].exist = 0;
						BOB0.money += ENM[i].money;
						enmTotal--;
					}
				}

				if (enmTotal < 1 && !endtrigger)
				{
					MAP1.obj[MAP1.ey][MAP1.ex] = 9;
					endtrigger = 1;
				}
				if (MAP1.quitfloor)
				{
					changemap_screen(render);
					map_load(&MAP1);
					BOB0.pos.x = MAP1.sx;
					BOB0.pos.y = MAP1.sy;
					BOB0.posTemp.x = MAP1.sx;
					BOB0.posTemp.y = MAP1.sy;
					JEU.etage++;
					for (i = 0; i < ENNEMY_MAX; i++)
						ENM[i] = enm_init(ENM[i], BOB0, &MAP1, render);
					enmTotal = ENNEMY_MAX;
					MAP1.quitfloor = 0; endtrigger = 0;
				}

				t0 = t;
			}
			else
			{
				SDL_Delay(TICKS - (t - t0));
			}
		}
		Mix_PauseMusic();
	}

	close_sdl_shit();

	return 0;
}
