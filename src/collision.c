#include "hdr/struct.h"
#include "hdr/object_power.h"

void collision(leBob *BOB, leMap *MAP)
{
  //printf("COLISION pos.x = %i, pos.y = %i, posTemp.x = %i; posTemp.y= %i \n", BOB->pos.x, BOB->pos.y, BOB->posTemp.x, BOB->posTemp.y);
  if (BOB->pos.x != BOB->posTemp.x || BOB->pos.y != BOB->posTemp.y)
  {
    if (MAP->col[(BOB->pos.y+23)/32][(BOB->pos.x+4)/32]== 1 || MAP->col[(BOB->pos.y+23)/32][(BOB->pos.x+28)/32]== 1 ||
    MAP->col[(BOB->pos.y+32)/32][(BOB->pos.x+4)/32]== 1 || MAP->col[(BOB->pos.y+32)/32][(BOB->pos.x+28)/32]== 1)
    {
      BOB->pos.x=BOB->posTemp.x;
      BOB->pos.y=BOB->posTemp.y;
    }
    //
//
    if (MAP->col[(BOB->pos.y+23)/32][(BOB->pos.x+4)/32]== 2 || MAP->col[(BOB->pos.y+23)/32][(BOB->pos.x+28)/32]== 2 ||
    MAP->col[(BOB->pos.y+32)/32][(BOB->pos.x+4)/32]== 2 || MAP->col[(BOB->pos.y+32)/32][(BOB->pos.x+28)/32]== 2)
    {
      BOB->pos.x=BOB->posTemp.x;
      BOB->pos.y=BOB->posTemp.y;
    }
  }
}

void objetcollision(leMap *MAP, leBob *BOB)
{
  if (BOB->pos.x != BOB->posTemp.x || BOB->pos.y != BOB->posTemp.y)
  {
    checkObject(BOB, MAP);
  }
}
