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

const SDL_Color WHITE = {255,255,255};

int main(int argc, char* args[])
{
    leMap MAP0, MAP1, MAP2;
	leBob BOB0 = { 0 };

	leBob ENM[ENNEMY_MAX] = { 0 };

    leJeu JEU;
    leInput INPUT = {0};
    int continuer = 1;
    int restartgame = 1;
    int startmenu =1;
    int i;
    srand((unsigned int)time(NULL));
    // Variable de SDL
    SDL_Window *window;
    SDL_Renderer* render;
    TTF_Font *police = NULL;
    Mix_Music *musique, *musique2;
    Texture *tileset;
    Texture *objset;
    Texture *guiset;
    Texture *screentitle;

    // SDL Init
    SDL_Init(SDL_INIT_VIDEO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_AllocateChannels(10);
    TTF_Init();

    window = SDL_CreateWindow(
                 "Bob's tower",      // window title
                 SDL_WINDOWPOS_UNDEFINED,   // initial x position
                 SDL_WINDOWPOS_UNDEFINED,   // initial y position
                 WWIN,                      // width, in pixels
                 HWIN,                      // height, in pixels
                 SDL_WINDOW_OPENGL          // flags - see below
             );
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    tileset=TextureCreate(render, "res/tileset.png", 255, 0, 255, 255);
    objset=TextureCreate(render, "res/objset.png", 255, 0, 255, 255);
    screentitle=TextureCreate(render, "res/screentitle.png", 255, 0, 255, 255);
    guiset=TextureCreate(render, "res/guiset.png", 255, 0, 255, 255);
    musique = Mix_LoadMUS("snd/music.mp3");
    musique2 = Mix_LoadMUS("snd/music2.mp3");
    police = TTF_OpenFont("ttf/FiraSans-Medium.ttf", 12);

    while(restartgame)
    {
        startmenu=1;
        continuer=1;
        TextureRender(render, screentitle, 0, 0, NULL);
        SDL_RenderPresent(render);
        Mix_PlayMusic(musique, -1);
        Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

        while (startmenu)
        {
            menuavantjeux(&startmenu, &restartgame, &continuer);
        }

        map_init(&MAP0);
        map_init(&MAP1);
        map_init(&MAP2);
        BOB0=bob_init(BOB0, render);
        for (i=0; i<ENNEMY_MAX; i++)
        ENM[i]=enm_init(ENM[i], &MAP1, render);

        JEU.son1 = Mix_LoadWAV("snd/loot1.wav"); // loot1
        JEU.son2 = Mix_LoadWAV("snd/loot2.wav");  // loot2
        JEU.son3 = Mix_LoadWAV("snd/loot3.wav"); // loot3
        JEU.son4 = Mix_LoadWAV("snd/hit1.wav"); // hit1
        JEU.etage = 0;

        Mix_Volume(1, 65);

        Mix_PlayMusic(musique2, -1);
        Mix_VolumeMusic(30);

        int hpTemp = 0, moneyTemp = 0;

        long
        t = 0,
        t0 = 0;

        static const int FPS = 60;
        int TICKS = 1000 / FPS;

        while(continuer)
        {
            t=SDL_GetTicks();

            if (t-t0>TICKS)
            {
                inputReturn(&INPUT);
                mouvement(&INPUT, render, &BOB0, &continuer, &restartgame);
                mov_enm(render, ENM, &BOB0);
                collision(&BOB0, &MAP1);
                collisionEnm(ENM, &MAP1);
                objetcollision(&MAP1, &BOB0, &JEU);
                AfficherMap_layer1(render, tileset, MAP1);
                AfficherObj(render, objset, MAP1);
                AfficherBob(render, &BOB0);
                AfficherEnm(render, ENM);
                AfficherMap_layer2(render, tileset, MAP1);
                if (moneyTemp!=BOB0.money || hpTemp!=BOB0.hp)
                    AfficherGui(render, guiset, &BOB0, police);
                SDL_RenderPresent(render);
                if (BOB0.hp<1)
                    continuer=0;
                t0=t;
                hpTemp=BOB0.hp;
                moneyTemp=BOB0.money;
            }
            else
            {
                SDL_Delay(TICKS-(t-t0));
            }
        }
        Mix_PauseMusic();
    }
    // Closing
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}
