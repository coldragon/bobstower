#include <SDL2/SDL.h>
#include "hdr/other_screen.h"
#include "hdr/struct.h"

void inputReturn(SDL_Event event, leInput *input)
{

}

void inputInit(leInput *input)
{
    input->haut=0;
    input->bas=0;
    input->gauche=0;
    input->droite=0;
    input->echap=0;
    input->quitter=0;

}


void mouvement(leInput *input, SDL_Event event, SDL_Renderer *render,leBob *BOB0, int *continuer, int *restartgame)
{
    BOB0->posTemp.x=BOB0->pos.x;
    BOB0->posTemp.y=BOB0->pos.y;
    if  (input->quitter)
    {
        *continuer = 0;
        *restartgame = 0;
    }
    if  (input->haut)
    {
        BOB0->pos.y=BOB0->pos.y-BOB0->speed;
        BOB0->skinPos.x=TCASE;
    }
    if  (input->bas)
    {
        BOB0->pos.y=BOB0->pos.y+BOB0->speed;
        BOB0->skinPos.x=0;
    }
    if  (input->gauche)
    {
        BOB0->pos.x=BOB0->pos.x-BOB0->speed;
        BOB0->skinPos.x=TCASE*2;
    }
    if  (input->droite)
    {
        BOB0->pos.x=BOB0->pos.x+BOB0->speed;
        BOB0->skinPos.x=TCASE*3;
    }
    if  (input->echap)
    {
        if(menu_escape(render)==1)
          {
            *continuer = 0;
            *restartgame = 0;
          }
    }

    if (input->a)
    {
        if (BOB0->hp<BOB0->hpMax)
        BOB0->hp+=5;
    }

    if (input->z)
    {
        BOB0->hp-=5;
    }

    /*

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
          printf("hp+5 :: Hp = %i / %i \n", BOB0->hp, BOB0->hpMax);
          break;

          case SDLK_z:
          if (BOB0->hp>0)
          BOB0->hp-=5;
          printf("hp-5 :: Hp = %i / %i \n", BOB0->hp, BOB0->hpMax);
          break;
        }

        break;
      }*/
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
