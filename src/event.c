#include <SDL2/SDL.h>
#include "hdr/struct.h"

void mouvement(SDL_Event event, leBob *BOB0, int *continuer)
{
  SDL_WaitEvent(&event);
  switch(event.type)
  {

    case SDL_QUIT:
    *continuer = 0;
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
    }

    break;
  }
}

int quitting(SDL_Event event)
{
  int continuer = 1;
  SDL_WaitEvent(&event);
  switch(event.type)
  {
    case SDL_QUIT:
    continuer = 0;
    break;
  }
  return continuer;
}
