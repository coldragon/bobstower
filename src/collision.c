#include "hdr/struct.h"
#include "hdr/object_power.h"
#include "hdr/define.h"

void collision(leBob *BOB, leMap *MAP)
{
    if (BOB->pos.x != BOB->posTemp.x || BOB->pos.y != BOB->posTemp.y)
    {
        if (MAP->col[(BOB->pos.y+23)/TCASE][(BOB->pos.x+4)/32]== 1 || MAP->col[(BOB->pos.y+23)/32][(BOB->pos.x+28)/32]== 1 ||
            MAP->col[(BOB->pos.y+32)/TCASE][(BOB->pos.x+4)/32]== 1 || MAP->col[(BOB->pos.y+32)/32][(BOB->pos.x+28)/32]== 1)
        {
            BOB->pos.x=BOB->posTemp.x;
            BOB->pos.y=BOB->posTemp.y;
        }

        if (MAP->col[(BOB->pos.y)/32][(BOB->pos.x+4)/32]== 2 || MAP->col[(BOB->pos.y)/32][(BOB->pos.x+28)/32]== 2 ||
            MAP->col[(BOB->pos.y+10)/32][(BOB->pos.x+4)/32]== 2 || MAP->col[(BOB->pos.y+10)/32][(BOB->pos.x+28)/32]== 2)
        {
            BOB->pos.x=BOB->posTemp.x;
            BOB->pos.y=BOB->posTemp.y;
        }
    }
}

void collisionEnm(leBob *ENM, leMap *MAP, leBob *BOB)
{
    int i, j;
    int c[ENNEMY_MAX]= {0};
    for (i=0; i<ENNEMY_MAX; i++)
    {
        if (MAP->col[(ENM[i].pos.y+23)/32][(ENM[i].pos.x+4)/32]== 1 || MAP->col[(ENM[i].pos.y+23)/32][(ENM[i].pos.x+28)/32]== 1 ||
            MAP->col[(ENM[i].pos.y+32)/32][(ENM[i].pos.x+4)/32]== 1 || MAP->col[(ENM[i].pos.y+32)/32][(ENM[i].pos.x+28)/32]== 1)
        {
            c[i]=1;
        }

        if (MAP->col[(ENM[i].pos.y)/32][(ENM[i].pos.x+4)/32]== 2 || MAP->col[(ENM[i].pos.y)/32][(ENM[i].pos.x+28)/32]== 2 ||
            MAP->col[(ENM[i].pos.y+10)/32][(ENM[i].pos.x+4)/32]== 2 || MAP->col[(ENM[i].pos.y+10)/32][(ENM[i].pos.x+28)/32]== 2)
        {
            c[i]=1;
        }

        if (distancepoint(ENM[i].pos.x+16, ENM[i].pos.y+16, BOB->pos.x+16, BOB->pos.y+16)<ENM[i].collision)
        {
            c[i]=1;
        }

        for (j=0; j<ENNEMY_MAX; j++)
        {
            if (j!=i)
            {
                if (distancepoint(ENM[i].pos.x+16, ENM[i].pos.y+16, ENM[j].pos.x+16, ENM[j].pos.y+16)<ENM[i].collision)
                {
                    if (ENM[j].exist)
                    c[i]=1;
                }
            }
            if (c[i] && ENM[i].exist)
            {
                ENM[i].pos.x=ENM[i].posTemp.x;
                ENM[i].pos.y=ENM[i].posTemp.y;
            }
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

void sortcollision(leMap *MAP, leBob *ENM, leJeu *JEU)
{
    int i, j;
    for (i=0; i<MAX_PROJECTILES_PAR_SORT; i++)
    {
        for (j=0; j<ENNEMY_MAX; j++)
        {
            if (ENM[j].exist)
            {
                if (distancepoint(ENM[j].pos.x, ENM[j].pos.y, JEU->sort1.projectiles[i].pos.x, JEU->sort1.projectiles[i].pos.y)<=JEU->sort1.scale+(ENM[i].collision/2))
                {
                    if (JEU->sort1.projectiles[i].exist)
                    {
                        ENM[j].hp--;
                        JEU->sort1.projectiles[i].exist=0;
                        if(ENM[j].hp<1)
                        Mix_PlayChannel(2, JEU->son5, 0);
                    }
                }
            }
        }

        if (MAP->col[(JEU->sort1.projectiles[i].pos.y+23)/32][(JEU->sort1.projectiles[i].pos.x+4)/32]== 1 || MAP->col[(JEU->sort1.projectiles[i].pos.y+23)/32][(JEU->sort1.projectiles[i].pos.x+28)/32]== 1 ||
                MAP->col[(JEU->sort1.projectiles[i].pos.y+32)/32][(JEU->sort1.projectiles[i].pos.x+4)/32]== 1 || MAP->col[(JEU->sort1.projectiles[i].pos.y+32)/32][(JEU->sort1.projectiles[i].pos.x+28)/32]== 1   )
        {
            JEU->sort1.projectiles[i].exist=0;
        }

        if (distancepoint(JEU->sort1.projectiles[i].pos.x, JEU->sort1.projectiles[i].pos.y, JEU->sort1.projectiles[i].posOrigin.x, JEU->sort1.projectiles[i].posOrigin.y)>=JEU->sort1.distanceattaque)
        {
            JEU->sort1.projectiles[i].exist=0;
        }

    }
}
