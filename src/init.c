#include "hdr/texture.h"

#include "hdr/basic.h"
#include "hdr/collision.h"
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <time.h>
#include <stdlib.h> 
#include "hdr/map.h"
#include "hdr/other_screen.h"
#include "hdr/affichage.h"
#include "hdr/attack.h"
#include "hdr/event.h"

void open_sdl_shit()
{
	SDL_Init(SDL_INIT_VIDEO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	Mix_AllocateChannels(10);
	TTF_Init();
}

void close_sdl_shit()
{
	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}

void coreInit(leCore *CORE)
{
	srand((unsigned int)time(NULL));

	CORE->WINDOW = SDL_CreateWindow("Bob's tower Alpha", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WWIN, HWIN, 0);
	CORE->RENDER = SDL_CreateRenderer(CORE->WINDOW, -1, SDL_RENDERER_ACCELERATED);

	// TEXTURE AND GUI
	CORE->TEXPACK.tileset = TextureCreate(CORE->RENDER, "res/tileset.png", 255, 0, 255, 255);
	CORE->TEXPACK.objset = TextureCreate(CORE->RENDER, "res/objset.png", 255, 0, 255, 255);
	CORE->TEXPACK.screentitle = TextureCreate(CORE->RENDER, "res/screentitle.png", 255, 0, 255, 255);
	CORE->TEXPACK.sortset = TextureCreate(CORE->RENDER, "res/sortset.png", 255, 0, 255, 255);
	CORE->TEXPACK.guiset = TextureCreate(CORE->RENDER, "res/guiset.png", 255, 0, 255, 255);
	CORE->TEXPACK.loose = TextureCreate(CORE->RENDER, "res/loose.png", 255, 0, 255, 255);
	CORE->FONT = TTF_OpenFont("ttf/FiraSans-Medium.ttf", 10);

	// AUDIO
	CORE->AUDIO.sound1 = Mix_LoadWAV("snd/loot1.wav"); // loot1
	CORE->AUDIO.sound2 = Mix_LoadWAV("snd/loot2.wav");  // loot2
	CORE->AUDIO.sound3 = Mix_LoadWAV("snd/loot3.wav"); // loot3
	CORE->AUDIO.sound4 = Mix_LoadWAV("snd/hit1.wav"); // hit1
	CORE->AUDIO.sound5 = Mix_LoadWAV("snd/mort1.wav"); // mort1
	CORE->AUDIO.sound6 = Mix_LoadWAV("snd/fireball1.wav"); // hit1
	CORE->AUDIO.sound7 = Mix_LoadWAV("snd/attackenm.wav"); // hit1
	CORE->AUDIO.sound8 = Mix_LoadWAV("snd/hit3.ogg");
	CORE->AUDIO.music1 = Mix_LoadMUS("snd/music.ogg");
	CORE->AUDIO.music2 = Mix_LoadMUS("");

	Mix_Volume(1, 65);
	Mix_Volume(2, 65);
	Mix_Volume(3, 65);
	Mix_Volume(4, 65);
	Mix_VolumeMusic(25);

	// MAP
	CORE->MAP = calloc(1, sizeof(leMap));

	// INPUT
	CORE->INPUT = calloc(1, sizeof(leInput));

}

void coreFree(leCore *CORE)
{
	
}

leBob bob_init(leBob BOB, SDL_Renderer *render)
{
    BOB.skin=TextureCreate(render, "res/bob.png", 255, 0, 255, 255);
    BOB.skinPos.x=0;
    BOB.skinPos.y=0;
    BOB.skinPos.w=BOB.skin->w/4;
    BOB.skinPos.h=BOB.skin->h;
    BOB.level = 1;
    BOB.hpMax = 100;
    BOB.hp = BOB.hpMax;
    BOB.speed = 3;
    BOB.money = 0;
    BOB.luck= 1;
    BOB.direction=2;
    BOB.collision = 20;
    BOB.attackspeed=410;
    BOB.distattack=30;
    BOB.pos.x = WWIN / 2 - BOB.skin->w / 2;
    BOB.pos.y = HWIN / 2 - BOB.skin->h / 2;
    BOB.pos.w = BOB.skin->w/4;
    BOB.pos.h = BOB.skin->h;
    BOB.posTemp=BOB.pos;
    BOB.exist=1;
    return BOB;
}

leBob enm_init(leBob BOB, leBob BOB0, leMap *MAP, SDL_Renderer *render)
{
    BOB.skin=TextureCreate(render, "res/gob1.png", 255, 0, 255, 255);
    BOB.skinPos.x=0;
    BOB.skinPos.y=0;
    BOB.skinPos.w=TCASE;
    BOB.skinPos.h=TCASE;
    BOB.level = 1;
    BOB.hpMax = 1;
    BOB.hp = 4;
    BOB.speed = 2;
    BOB.money = 10;
    BOB.luck= 1;
    BOB.collision = 20;
    BOB.fov=225; // Distance de vue
    BOB.attackspeed=410; // Vitesse entre chaque attaque
    BOB.distattack=30; // Distance d'attaque cac
    BOB.exist=1;
    BOB.pos.x = aleatoire(0, WWIN-TCASE);
    BOB.pos.y = aleatoire(0, HWIN-TCASE);

    while
    (
        collisionmap(&BOB.pos, MAP, 1, 16, 0, 4, 4) ||
        collisionmap(&BOB.pos, MAP, 2, 0, 16, 4, 4) ||
        distancepoint(BOB0.pos.x, BOB0.pos.y, BOB.pos.x, BOB.pos.y)<BOB.fov
    )
    {
        BOB.pos.x = aleatoire(0, WWIN-TCASE);
        BOB.pos.y = aleatoire(0, HWIN-TCASE);
    }

    BOB.pos.w = TCASE;
    BOB.pos.h = TCASE;
    BOB.posTemp=BOB.pos;
    return BOB;
}

void sort_init(leAudio *JEU, SDL_Renderer *render)
{
    int i;
    JEU->sort1.last_use=0;
    JEU->sort1.power=5;
    JEU->sort1.scale=10;
    JEU->sort1.skin=1;
    JEU->sort1.speed=6;
    JEU->sort1.distanceattaque=130;
    for (i=0; i<MAX_PROJECTILES_PAR_SORT; i++)
    {
        JEU->sort1.projectiles[i].pos.x=0;
        JEU->sort1.projectiles[i].pos.y=0;
        JEU->sort1.projectiles[i].pos.h=TCASE;
        JEU->sort1.projectiles[i].pos.w=TCASE;
        JEU->sort1.projectiles[i].d.x=0;
        JEU->sort1.projectiles[i].d.y=0;
        JEU->sort1.projectiles[i].mov.duration=0;
        JEU->sort1.projectiles[i].mov.now=0;
        JEU->sort1.projectiles[i].mov.start=0;
        JEU->sort1.projectiles[i].exist=0;
    }

    JEU->sort1_enm.last_use=0;
    JEU->sort1_enm.power=5;
    JEU->sort1_enm.scale=10;
    JEU->sort1_enm.skin=2;
    JEU->sort1_enm.speed=4;
    JEU->sort1_enm.distanceattaque=130;
    for (i=0; i<MAX_PROJECTILES_PAR_SORT; i++)
    {
        JEU->sort1_enm.projectiles[i].pos.x=0;
        JEU->sort1_enm.projectiles[i].pos.y=0;
        JEU->sort1_enm.projectiles[i].pos.h=TCASE;
        JEU->sort1_enm.projectiles[i].pos.w=TCASE;
        JEU->sort1_enm.projectiles[i].d.x=0;
        JEU->sort1_enm.projectiles[i].d.y=0;
        JEU->sort1_enm.projectiles[i].mov.duration=0;
        JEU->sort1_enm.projectiles[i].mov.now=0;
        JEU->sort1_enm.projectiles[i].mov.start=0;
        JEU->sort1_enm.projectiles[i].exist=0;
    }
}

void map_init(leMap *MAP)
{
	MAP->quitfloor = 0;
	memset(MAP->tile, 0, sizeof(MAP->tile));
	memset(MAP->tile2, 0, sizeof(MAP->tile2));
	memset(MAP->obj, 0, sizeof(MAP->obj));
	memset(MAP->col, 0, sizeof(MAP->col));
	MAP->ey = 0; MAP->ex = 0;
	MAP->sy = 0; MAP->sx = 0;
}

void main_loop(leCore *CORE)
{
	leBob BOB0 = { 0 };
	leBob ENM[ENNEMY_MAX] = { 0 };
	leInput INPUT = { 0 };
	int continuer = 1;
	int restartgame = 1;
	int startmenu = 1;
	int i;
	while (restartgame)
	{
		
		inputInit(&INPUT);
		startmenu = 1;
		continuer = 1;
		TextureRender(CORE->RENDER, CORE->TEXPACK.screentitle, 0, 0, NULL);
		SDL_RenderPresent(CORE->RENDER);
		Mix_PlayMusic(CORE->AUDIO.music1, -1);
		Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

		while (startmenu)
		{
			menuavantjeux(&INPUT, &startmenu, &restartgame, &continuer);
		}

		map_load(CORE->MAP);

		BOB0 = bob_init(BOB0, CORE->RENDER);
		BOB0.pos.x = CORE->MAP->sx;
		BOB0.pos.y = CORE->MAP->sy;
		BOB0.posTemp.x = CORE->MAP->sx;
		BOB0.posTemp.y = CORE->MAP->sy;

		for (i = 0; i < ENNEMY_MAX; i++)
			ENM[i] = enm_init(ENM[i], BOB0, CORE->MAP, CORE->RENDER);
		int enmTotal = ENNEMY_MAX;
		int endtrigger = 0;


		CORE->AUDIO.etage = 1;

		sort_init(&CORE->AUDIO, CORE->RENDER);

		Mix_PlayMusic(CORE->AUDIO.music2, -1);

		Mix_PauseMusic();

		long t, t0 = 0;
		static const int FPS = 60;
		int TICKS = 1000 / FPS;
		BOB0.pos.x = CORE->MAP->sy;
		BOB0.pos.y = CORE->MAP->sx;
		while (continuer)
		{
			t = SDL_GetTicks();

			if (t - t0 > TICKS)
			{
				// Input
				inputReturn(&INPUT);

				// Mouvement
				mouvement(&INPUT, CORE->RENDER, &BOB0, CORE->MAP, &continuer, &restartgame);
				mov_enm(CORE->RENDER, ENM, &BOB0);
				move_projectile(&CORE->AUDIO, &BOB0);

				// Collision
				collisionEnm(ENM, CORE->MAP, &BOB0);
				sortcollision(CORE->MAP, ENM, &CORE->AUDIO, &BOB0);
				objetcollision(CORE->MAP, &BOB0, &CORE->AUDIO);

				// Attaque
				attackcac_enm(ENM, &BOB0, &CORE->AUDIO);
				attack_bob(&BOB0, &CORE->AUDIO, &INPUT);

				// Affichage
				AFFICHAGE(CORE, ENM, &BOB0);

				// Defaite
				if (BOB0.hp < 1)
				{
					if (BOB0.hp < 0)
						BOB0.hp = 0;

					continuer = 0;
					TextureRender(CORE->RENDER, CORE->TEXPACK.loose, 0, 0, NULL);
					SDL_RenderPresent(CORE->RENDER);
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
					CORE->MAP->obj[CORE->MAP->ey][CORE->MAP->ex] = 9;
					endtrigger = 1;
				}
				if (CORE->MAP->quitfloor)
				{
					changemap_screen(CORE->RENDER);
					map_load(CORE->MAP);
					BOB0.pos.x = CORE->MAP->sx;
					BOB0.pos.y = CORE->MAP->sy;
					BOB0.posTemp.x = CORE->MAP->sx;
					BOB0.posTemp.y = CORE->MAP->sy;
					CORE->AUDIO.etage++;
					for (i = 0; i < ENNEMY_MAX; i++)
						ENM[i] = enm_init(ENM[i], BOB0, CORE->MAP, CORE->RENDER);
					enmTotal = ENNEMY_MAX;
					CORE->MAP->quitfloor = 0; endtrigger = 0;
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
}