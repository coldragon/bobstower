#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "hdr/texture.h"
#include "hdr/define.h"
#include "hdr/struct.h"
#include "hdr/affichage.h"
#include "hdr/init.h"
#include "hdr/event.h"
#include "hdr/collision.h"

int main(int argc, char* args[])
{ leMap MAP0, MAP1, MAP2;
  leBob BOB0;
  leJeu JEU;
  int continuer = 1;
  int restartgame = 1;
  int startmenu =1;

  // Variable de SDL
  SDL_Window *window;
  SDL_Renderer* render;
  Mix_Music *musique;
  Texture *tileset;
  Texture *objset;
  Texture *screentitle;
  SDL_Event event;

  // SDL Init
  SDL_Init(SDL_INIT_VIDEO);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
  Mix_AllocateChannels(10);
  TTF_Init();

  window = SDL_CreateWindow(
    "Bob Adventure SDL2 Proto",      // window title
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
  musique = Mix_LoadMUS("snd/music.mp3");

  while(restartgame)
  {
    CleanScreen(render, 0, 0, 0);
    TextureRender(render, screentitle, 0, 0, NULL);
    SDL_RenderPresent(render);
    Mix_PlayMusic(musique, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

    while (startmenu)
    {
      menuavantjeux(event, &startmenu, &restartgame, &continuer);
    }

      MAP0=map_init(MAP0);
      MAP1=map_init(MAP1);
      MAP2=map_init(MAP2);
      BOB0=bob_init(BOB0, render);
      JEU.son1 = Mix_LoadWAV("snd/loot1.wav"); // loot1
      JEU.son2 = Mix_LoadWAV("snd/loot2.wav");  // loot2
      JEU.son3 = Mix_LoadWAV("snd/loot3.wav"); // loot3
    Mix_PauseMusic();

    while (continuer)
    {
      mouvement(event, render, &BOB0, &continuer, &restartgame);
      collision(&BOB0, &MAP1);
      objetcollision(&MAP1, &BOB0, &JEU);
      AfficherMap_layer1(render, tileset, MAP1);
      AfficherObj(render, objset, MAP1);
      AfficherBob(render, BOB0);
      AfficherMap_layer2(render, tileset, MAP1);
      SDL_RenderPresent(render);
    }
  }
  // Closing
  TTF_Quit();
  Mix_CloseAudio();
  SDL_Quit();
  return 0;
}
