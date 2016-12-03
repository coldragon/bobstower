#include <SDL2/SDL.h>
#include "hdr/other_screen.h"
#include "hdr/struct.h"

void mouvement(SDL_Event event, SDL_Renderer *render ,leBob *BOB0, int *continuer, int *restartgame)
{
  SDL_WaitEvent(&event);
  switch(event.type)
  {

    case SDL_QUIT:
    *continuer = 0;
    *restartgame = 0;
    break;


    case SDL_KEYDOWN:
    BOB0->posTemp.x=BOB0->pos.x;
    BOB0->posTemp.y=BOB0->pos.y;
    switch(event.key.keysym.sym)
    {
      case SDLK_UP:
      printf("PRESS HAUT \n");
      BOB0->pos.y=BOB0->pos.y-BOB0->speed;
      BOB0->skinPos.x=TCASE;
      //printf("pos.x = %i, pos.y = %i, posTemp.x = %i; posTemp.y= %i \n", BOB0->pos.x, BOB0->pos.y, BOB0->posTemp.x, BOB0->posTemp.y);
      break;

      case SDLK_DOWN:
      printf("PRESS BAS \n");
      BOB0->pos.y=BOB0->pos.y+BOB0->speed;
      BOB0->skinPos.x=0;
      //printf("pos.x = %i, pos.y = %i, posTemp.x = %i; posTemp.y= %i \n", BOB0->pos.x, BOB0->pos.y, BOB0->posTemp.x, BOB0->posTemp.y);
      break;

      case SDLK_RIGHT:
      printf("PRESS DROITE \n");
      BOB0->pos.x=BOB0->pos.x+BOB0->speed;
      BOB0->skinPos.x=TCASE*3;
      //printf("pos.x = %i, pos.y = %i, posTemp.x = %i; posTemp.y= %i \n", BOB0->pos.x, BOB0->pos.y, BOB0->posTemp.x, BOB0->posTemp.y);
      break;

      case SDLK_LEFT:
      printf("PRESS GAUCHE \n");
      BOB0->pos.x=BOB0->pos.x-BOB0->speed;
      BOB0->skinPos.x=TCASE*2;
      //printf("pos.x = %i, pos.y = %i, posTemp.x = %i; posTemp.y= %i \n", BOB0->pos.x, BOB0->pos.y, BOB0->posTemp.x, BOB0->posTemp.y);
      break;

      case SDLK_ESCAPE:
      if(menu_escape(render)==1)
      {
        *continuer = 0;
        *restartgame = 0;
      }
      break;

      case SDLK_a:
      if (BOB0->hp<BOB0->hpMax)
      BOB0->hp+=5;
      printf("hp++ :: Hp = %i / %i \n", BOB0->hp, BOB0->hpMax);
      break;

      case SDLK_z:
      if (BOB0->hp>0)
      BOB0->hp-=5;
      printf("hp-- :: Hp = %i / %i \n", BOB0->hp, BOB0->hpMax);
      break;
    }

    break;
  }
}

void menuavantjeux(SDL_Event event, int *startmenu, int *restartgame, int *continuer)
{
  SDL_WaitEvent(&event);
  switch(event.type)
  {
    case SDL_QUIT:
    *restartgame = 0;
    *continuer = 0;
    *startmenu = 0;
    break;

    case SDL_KEYDOWN:
    switch(event.key.keysym.sym)
    {
      case SDLK_RETURN:
      *startmenu=0;
      break;
    }
    break;
  }
}
