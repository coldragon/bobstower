#include "hdr/attack.h"
#include "hdr/basic.h"
#include "hdr/struct.h"

void attackcac_enm(leBob *ENM, leBob *BOB, leJeu *JEU)
{
    int i;
    for (i=0; i<ENNEMY_MAX; i++)
    {
        if(ENM[i].exist=1)
        {
            if (ENM[i].tatt.now-ENM[i].tatt.start >= ENM[i].attackspeed)
            {
                if (distancepoint(ENM[i].pos.x+16, ENM[i].pos.y+16, BOB->pos.x+16, BOB->pos.y+16)<ENM[i].distattack)
                {
                    BOB->hp--;
                    Mix_PlayChannel(1, JEU->son4, 0);
                }
                ENM[i].tatt.start=ENM[i].tatt.now;
            }
            ENM[i].tatt.now=SDL_GetTicks();
        }
    }
}

void create_projectile(leJeu *JEU, leBob *BOB)
{
    if (JEU->sort1.last_use>=MAX_PROJECTILES_PAR_SORT)
        JEU->sort1.last_use=0;

    if(JEU->sort1.projectiles[JEU->sort1.last_use].exist)
        JEU->sort1.projectiles[JEU->sort1.last_use].exist=0;

    JEU->sort1.projectiles[JEU->sort1.last_use].pos.x=BOB->pos.x;
    JEU->sort1.projectiles[JEU->sort1.last_use].pos.y=BOB->pos.y;

    if (BOB->direction==0)
    {
        JEU->sort1.projectiles[JEU->sort1.last_use].d.x=0;
        JEU->sort1.projectiles[JEU->sort1.last_use].d.y=-1;

    }
    if (BOB->direction==1)
    {
        JEU->sort1.projectiles[JEU->sort1.last_use].d.x=1;
        JEU->sort1.projectiles[JEU->sort1.last_use].d.y=0;
    }
    if (BOB->direction==2)
    {
        JEU->sort1.projectiles[JEU->sort1.last_use].d.x=0;
        JEU->sort1.projectiles[JEU->sort1.last_use].d.y=1;
    }
    if (BOB->direction==3)
    {
        JEU->sort1.projectiles[JEU->sort1.last_use].d.x=-1;
        JEU->sort1.projectiles[JEU->sort1.last_use].d.y=0;
    }
    JEU->sort1.projectiles[JEU->sort1.last_use].exist=1;

    JEU->sort1.last_use++;
}

void move_projectile(leJeu *JEU, leBob *BOB)
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
}

void attack_bob(leBob *BOB, leBob *ENM, leJeu *JEU, leInput *INPUT)
{
    if(INPUT->key[SDL_SCANCODE_SPACE])
    {
        if (BOB->tatt.now-BOB->tatt.start >= BOB->attackspeed)
        {

            create_projectile(JEU, BOB);
            Mix_PlayChannel(1, JEU->son4, 0);

            BOB->tatt.start=BOB->tatt.now;
        }
        BOB->tatt.now=SDL_GetTicks();
    }
}
