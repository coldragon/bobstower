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

  // Variable de SDL
  SDL_Window *window;
  SDL_Renderer* render;
  Mix_Music *musique;
  Texture *tileset;
  Texture *objset;
  SDL_Event event;

  // SDL Init
  SDL_Init(SDL_INIT_VIDEO);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
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

  //Init Variables
  MAP0=map_init(MAP0);
  MAP1=map_init(MAP1);
  MAP2=map_init(MAP2);
  BOB0=bob_init(BOB0, render);
  tileset=TextureCreate(render, "res/tileset.png", 255, 0, 255, 255);
  objset=TextureCreate(render, "res/objset.png", 255, 0, 255, 255);

  Mix_AllocateChannels(10);
  musique = Mix_LoadMUS("snd/music.mp3");
  JEU.son1 = Mix_LoadWAV("snd/loot1.wav");
  Mix_PlayMusic(musique, -1);
  Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
  CleanScreen(render, 0, 0, 0);
  SDL_RenderPresent(render);
  SDL_Delay(500);

  while (continuer)
  {
    mouvement(event, &BOB0, &continuer);
    collision(&BOB0, &MAP1);
    objetcollision(&MAP1, &BOB0, &JEU);
    AfficherMap(render, tileset, MAP1);
    AfficherObj(render, objset, MAP1);
    AfficherBob(render, BOB0);
    SDL_RenderPresent(render);
  }

  // Closing
  TTF_Quit();
  Mix_CloseAudio();
  SDL_Quit();
  return 0;
}
