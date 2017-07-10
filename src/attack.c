#include "hdr/attack.h"
#include "hdr/basic.h"
#include "hdr/struct.h"

void attackcac_enm(leBob *ENM, leBob *BOB, leAudio *JEU)
{
    int i;
    for (i=0; i<ENNEMY_MAX; i++)
    {
        if(ENM[i].exist)
        {
            if (ENM[i].tatt.now-ENM[i].tatt.start >= ENM[i].attackspeed*2)
            {
                if (distancepoint(ENM[i].pos.x+16, ENM[i].pos.y+16, BOB->pos.x+16, BOB->pos.y+16)<ENM[i].distattack)
                {
                    BOB->hp--;
                    Mix_PlayChannel(4, JEU->sound7, 0);
                }

                if (ENM[i].pos.x-BOB->pos.x>=0 && ENM[i].pos.x-BOB->pos.x<8)
                {
                    create_projectile(JEU, &JEU->sort1_enm, &ENM[i]);
                    Mix_PlayChannel(4, JEU->sound7, 0);
                }

                if (ENM[i].pos.x-BOB->pos.x<=0 && ENM[i].pos.x-BOB->pos.x>-8)
                {
                    create_projectile(JEU, &JEU->sort1_enm, &ENM[i]);
                    Mix_PlayChannel(4, JEU->sound7, 0);
                }

                if (ENM[i].pos.y-BOB->pos.y>=0 && ENM[i].pos.y-BOB->pos.y<8)
                {
                    create_projectile(JEU, &JEU->sort1_enm, &ENM[i]);
                    Mix_PlayChannel(4, JEU->sound7, 0);
                }

                if (ENM[i].pos.y-BOB->pos.y<=0 && ENM[i].pos.y-BOB->pos.y>-8)
                {
                    create_projectile(JEU, &JEU->sort1_enm, &ENM[i]);
                    Mix_PlayChannel(4, JEU->sound7, 0);
                }
                ENM[i].tatt.start=ENM[i].tatt.now;
            }
            ENM[i].tatt.now=SDL_GetTicks();
        }
    }
}

void create_projectile(leAudio *JEU, leSort *SORT, leBob *BOB)
{
    if (SORT->last_use>=MAX_PROJECTILES_PAR_SORT)
        SORT->last_use=0;

    if(SORT->projectiles[SORT->last_use].exist)
        SORT->projectiles[SORT->last_use].exist=0;

    SORT->projectiles[SORT->last_use].pos.x=BOB->pos.x;
    SORT->projectiles[SORT->last_use].pos.y=BOB->pos.y;
    SORT->projectiles[SORT->last_use].posOrigin.x=BOB->pos.x;
    SORT->projectiles[SORT->last_use].posOrigin.y=BOB->pos.y;

    if (BOB->direction==0)
    {
        SORT->projectiles[SORT->last_use].d.x=0;
        SORT->projectiles[SORT->last_use].d.y=-1;

    }
    if (BOB->direction==1)
    {
        SORT->projectiles[SORT->last_use].d.x=1;
        SORT->projectiles[SORT->last_use].d.y=0;
    }
    if (BOB->direction==2)
    {
        SORT->projectiles[SORT->last_use].d.x=0;
        SORT->projectiles[SORT->last_use].d.y=1;
    }
    if (BOB->direction==3)
    {
        SORT->projectiles[SORT->last_use].d.x=-1;
        SORT->projectiles[SORT->last_use].d.y=0;
    }
    SORT->projectiles[SORT->last_use].exist=1;

    SORT->last_use++;
}

void move_projectile(leAudio *JEU, leBob *BOB)
{
    int i;
    for (i=0; i<MAX_PROJECTILES_PAR_SORT; i++)
    {
        if (JEU->sort1.projectiles[i].exist)
        {
            JEU->sort1.projectiles[i].pos.x+=JEU->sort1.projectiles[i].d.x*JEU->sort1.speed;
            JEU->sort1.projectiles[i].pos.y+=JEU->sort1.projectiles[i].d.y*JEU->sort1.speed;
        }
        }

    for (i=0; i<MAX_PROJECTILES_PAR_SORT; i++)
    {
        if (JEU->sort1_enm.projectiles[i].exist)
        {
            JEU->sort1_enm.projectiles[i].pos.x+=JEU->sort1_enm.projectiles[i].d.x*JEU->sort1_enm.speed;
            JEU->sort1_enm.projectiles[i].pos.y+=JEU->sort1_enm.projectiles[i].d.y*JEU->sort1_enm.speed;
        }
    }
}

void attack_bob(leBob *BOB, leAudio *JEU, leInput *INPUT)
{
    if(INPUT->key[SDL_SCANCODE_SPACE])
    {
        if (BOB->tatt.now-BOB->tatt.start >= BOB->attackspeed)
        {
            create_projectile(JEU, &JEU->sort1, BOB);
            Mix_PlayChannel(3, JEU->sound6, 0);

            BOB->tatt.start=BOB->tatt.now;
        }
        BOB->tatt.now=SDL_GetTicks();
    }
}
