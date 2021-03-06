#include "hdr/struct.h"
#include "hdr/object_power.h"
#include "hdr/define.h"
#include "hdr/basic.h"

int collisionmap(SDL_Rect *rect, leMap *MAP, int type, int haut, int bas, int gauche, int droite)
{
    if
    (
        MAP->col[(rect->y+haut)/TCASE][(rect->x+gauche)/TCASE]== type ||
        MAP->col[(rect->y+haut)/TCASE][(rect->x+rect->w-droite)/TCASE]== type ||
        MAP->col[(rect->y+rect->h-bas)/TCASE][(rect->x+gauche)/TCASE]== type ||
        MAP->col[(rect->y+rect->h-bas)/TCASE][(rect->x+rect->w-droite)/TCASE]== type
    )
        return 1;
    else
        return 0;
}

void collisionEnm(leBob *ENM, leMap *MAP, leBob *BOB)
{
    int i, j;
    int c[ENNEMY_MAX]= {0};
    for (i=0; i<ENNEMY_MAX; i++)
    {
        if(collisionmap(&ENM[i].pos, MAP, 1, 16, 0, 4, 4) || collisionmap(&ENM[i].pos, MAP, 2, 0, 16, 4, 4))
            c[i]=1;

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

void objetcollision(leMap *MAP, leBob *BOB, leAudio *JEU)
{
    if (BOB->pos.x != BOB->posTemp.x || BOB->pos.y != BOB->posTemp.y)
    {
        checkObject(BOB, MAP, JEU);
    }
}

void sortcollision(leMap *MAP, leBob *ENM, leAudio *JEU, leBob *BOB)
{
    int i, j;
    for (i=0; i<MAX_PROJECTILES_PAR_SORT; i++)
    {
        for (j=0; j<ENNEMY_MAX; j++)
        {
            if (distancepoint(ENM[j].pos.x, ENM[j].pos.y, JEU->sort1.projectiles[i].pos.x, JEU->sort1.projectiles[i].pos.y)<=JEU->sort1.scale+(ENM[j].collision/2) && ENM[j].exist)
            {
                if (JEU->sort1.projectiles[i].exist)
                {
                    ENM[j].hp--;
                    JEU->sort1.projectiles[i].exist=0;
                    if(ENM[j].hp<1)
                        Mix_PlayChannel(2, JEU->sound5, 0);
                }
            }

            if (distancepoint(BOB->pos.x, BOB->pos.y, JEU->sort1_enm.projectiles[i].pos.x, JEU->sort1_enm.projectiles[i].pos.y)<=JEU->sort1_enm.scale+(BOB->collision/2))
            {
                if (JEU->sort1_enm.projectiles[i].exist)
                {
                    BOB->hp--;
                    Mix_PlayChannel(8, JEU->sound8, 0);
                    JEU->sort1_enm.projectiles[i].exist=0;
                    if(BOB->hp<1)
                        Mix_PlayChannel(2, JEU->sound5, 0);
                }
            }
        }



        if(collisionmap(&JEU->sort1.projectiles[i].pos, MAP, 1, 32, 0, 10, 10) || collisionmap(&JEU->sort1.projectiles[i].pos, MAP, 2, 0, 32, 10, 10))
        {
            JEU->sort1.projectiles[i].exist=0;
        }

        /*if (distancepoint(JEU->sort1.projectiles[i].pos.x, JEU->sort1.projectiles[i].pos.y, JEU->sort1.projectiles[i].posOrigin.x, JEU->sort1.projectiles[i].posOrigin.y)>=JEU->sort1.distanceattaque)
        {
            JEU->sort1.projectiles[i].exist=0;
        }*/

        if(collisionmap(&JEU->sort1_enm.projectiles[i].pos, MAP, 1, 32, 0, 10, 10) || collisionmap(&JEU->sort1_enm.projectiles[i].pos, MAP, 2, 0, 32, 10, 10))
        {
            JEU->sort1_enm.projectiles[i].exist=0;
        }

    }
}
