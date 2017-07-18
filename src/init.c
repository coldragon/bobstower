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

	// STATE
	CORE->STATE.game_is_running=1;
	CORE->STATE.game_restarter=1;
	CORE->STATE.startmenu=1;
	CORE->STATE.endtrigger=1;
	CORE->STATE.enmTotal = ENNEMY_MAX;


	// MAP
	CORE->MAP = calloc(1, sizeof(leMap));

	// INPUT
	CORE->INPUT = calloc(1, sizeof(leInput));

}

void coreFree(leCore *CORE)
{
	
}

void bob_init(leBob *BOB, SDL_Renderer *render, leMap *MAP)
{
    BOB->skin=TextureCreate(render, "res/bob.png", 255, 0, 255, 255);
    BOB->skinPos.x=0;
    BOB->skinPos.y=0;
    BOB->skinPos.w=BOB->skin->w/4;
    BOB->skinPos.h=BOB->skin->h;
    BOB->level = 1;
    BOB->hpMax = 100;
    BOB->hp = BOB->hpMax;
    BOB->speed = 3;
    BOB->money = 0;
    BOB->luck= 1;
    BOB->direction=2;
    BOB->collision = 20;
    BOB->attackspeed=410;
    BOB->distattack=30;
    BOB->pos.x = WWIN / 2 - BOB->skin->w / 2;
    BOB->pos.y = HWIN / 2 - BOB->skin->h / 2;
    BOB->pos.w = BOB->skin->w/4;
    BOB->pos.h = BOB->skin->h;
    BOB->posTemp=BOB->pos;
    BOB->exist=1;
	BOB->pos.x = MAP->sx;
	BOB->pos.y = MAP->sy;
	BOB->posTemp.x = MAP->sx;
	BOB->posTemp.y = MAP->sy;
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
	while (CORE->STATE.game_restarter)
	{
		CORE->STATE.startmenu = 1;
		CORE->STATE.game_is_running = 1;
		
		TextureRender(CORE->RENDER, CORE->TEXPACK.screentitle, 0, 0, NULL);
		SDL_RenderPresent(CORE->RENDER);
		Mix_PlayMusic(CORE->AUDIO.music1, -1);
		Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

		start_menu(CORE->INPUT, &CORE->STATE);

		//Map Init
		map_load(CORE->MAP);
		bob_init(&CORE->ENTITYPACK.BOB, CORE->RENDER, CORE->MAP);
		for (int i = 0; i < ENNEMY_MAX; i++)
			CORE->ENTITYPACK.ENM[i] = enm_init(CORE->ENTITYPACK.ENM[i], CORE->ENTITYPACK.BOB, CORE->MAP, CORE->RENDER);
		sort_init(&CORE->AUDIO, CORE->RENDER);
		Mix_FadeOutMusic(1000);

		inputInit(CORE->INPUT);
		while (CORE->STATE.game_is_running)
		{
			CORE->LIMITER.actual = SDL_GetTicks();

			if (CORE->LIMITER.actual - CORE->LIMITER.last > LOGICAL_TICKS_LIMITER)
			{

				//  //  //  //
				LOGICAL(CORE);
				AFFICHAGE(CORE, CORE->ENTITYPACK.ENM, &CORE->ENTITYPACK.BOB);
				//  //  //  //

				CORE->LIMITER.last = CORE->LIMITER.actual;
			}
			else
				SDL_Delay(LOGICAL_TICKS_LIMITER - (CORE->LIMITER.actual - CORE->LIMITER.last));
		}
	}
}