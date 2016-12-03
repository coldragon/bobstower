#include "hdr/struct.h"
#include <SDL2/SDL_mixer.h>

void callbackActionObject(int* objectType, leBob* BOB, leMap* MAP, leJeu* JEU)
{

    switch(*objectType) {
    case 1:
    if(BOB->hp < BOB->hpMax)
    {
      BOB->hp+=5;
      *objectType = 0;
      Mix_PlayChannel(1, JEU->son2, 0);
      printf("\n vie : %i / %i \n", BOB->hp, BOB->hpMax);
    }
    break;

    case 2:
      BOB->hpMax++;
      BOB->hp++;
      *objectType = 0;
      printf("\n vie : %i / %i \n", BOB->hp, BOB->hpMax);
      Mix_PlayChannel(1, JEU->son3, 0);
    break;

    case 3:
      BOB->money+=50;
      printf("money :%i \n", BOB->money);
      Mix_PlayChannel(1, JEU->son1, 0);
      *objectType = 4;
    break;

    default:
    break;
    }

}

void checkObject(leBob* BOB, leMap* MAP, leJeu *JEU)
{

  int* hautObjCheck = &MAP->obj[(BOB->pos.y+20)/32][(BOB->pos.x+4)/32];
  if (*hautObjCheck != 0)
  {
    callbackActionObject(hautObjCheck, BOB, MAP, JEU);
  }

  int* droiteObjCheck = &MAP->obj[(BOB->pos.y+20)/32][(BOB->pos.x+28)/32];
  if (*droiteObjCheck != 0)
  {
    callbackActionObject(droiteObjCheck, BOB, MAP, JEU);
  }
  int* basObjCheck = &MAP->obj[(BOB->pos.y+32)/32][(BOB->pos.x+4)/32];
  if (*basObjCheck != 0)
  {
    callbackActionObject(basObjCheck, BOB, MAP, JEU);
  }
  int* basDroiteObjCheck = &MAP->obj[(BOB->pos.y+32)/32][(BOB->pos.x+28)/32];
  if (*basDroiteObjCheck != 0)
  {
    callbackActionObject(basDroiteObjCheck, BOB, MAP, JEU);
  }
}

/*void healthpack(leBob *BOB, leMap *MAP)
{
  if (BOB->hp<BOB->hpMax)
  {

      MAP->obj[(BOB->pos.y+20)/32][(BOB->pos.x+4)/32]=0;
      BOB->hp++;
    }
    if (MAP->obj[(BOB->pos.y+20)/32][(BOB->pos.x+28)/32]== 1)
    {
      MAP->obj[(BOB->pos.y+20)/32][(BOB->pos.x+28)/32]=0;
      BOB->hp++;
    }
    if (MAP->obj[(BOB->pos.y+32)/32][(BOB->pos.x+4)/32]== 1)
    {
      BOB->hp++;
      MAP->obj[(BOB->pos.y+32)/32][(BOB->pos.x+4)/32]=0;
    }
    if (MAP->obj[(BOB->pos.y+32)/32][(BOB->pos.x+28)/32]== 1)
    {
      MAP->obj[(BOB->pos.y+32)/32][(BOB->pos.x+28)/32]= 0;
      BOB->hp++;
    }
  }
}*/
