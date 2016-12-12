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
    if (MAP->col[(BOB->pos.y)/32][(BOB->pos.x+4)/32]== 2 || MAP->col[(BOB->pos.y)/32][(BOB->pos.x+28)/32]== 2 ||
    MAP->col[(BOB->pos.y+10)/32][(BOB->pos.x+4)/32]== 2 || MAP->col[(BOB->pos.y+10)/32][(BOB->pos.x+28)/32]== 2)
    {
      BOB->pos.x=BOB->posTemp.x;
      BOB->pos.y=BOB->posTemp.y;
    }
  }
}

void collisionEnm(leBob *ENM, leMap *MAP)
{
    int i;
    for (i=0; i<ENNEMY_MAX; i++)
    {
    if (MAP->col[(ENM[i].pos.y+23)/32][(ENM[i].pos.x+4)/32]== 1 || MAP->col[(ENM[i].pos.y+23)/32][(ENM[i].pos.x+28)/32]== 1 ||
    MAP->col[(ENM[i].pos.y+32)/32][(ENM[i].pos.x+4)/32]== 1 || MAP->col[(ENM[i].pos.y+32)/32][(ENM[i].pos.x+28)/32]== 1)
    {
      ENM[i].pos.x=ENM[i].posTemp.x;
      ENM[i].pos.y=ENM[i].posTemp.y;
    }

    if (MAP->col[(ENM[i].pos.y)/32][(ENM[i].pos.x+4)/32]== 2 || MAP->col[(ENM[i].pos.y)/32][(ENM[i].pos.x+28)/32]== 2 ||
    MAP->col[(ENM[i].pos.y+10)/32][(ENM[i].pos.x+4)/32]== 2 || MAP->col[(ENM[i].pos.y+10)/32][(ENM[i].pos.x+28)/32]== 2)
    {
      ENM[i].pos.x=ENM[i].posTemp.x;
      ENM[i].pos.y=ENM[i].posTemp.y;
    }
    }
}

void objetcollision(leMap *MAP, leBob *BOB, leJeu *JEU)
{
  if (BOB->pos.x != BOB->posTemp.x || BOB->pos.y != BOB->posTemp.y)
  {
    checkObject(BOB, MAP, JEU);
  }
}
