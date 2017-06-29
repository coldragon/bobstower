#include "hdr/texture.h"
#include "hdr/struct.h"
#include "hdr/basic.h"
#include "hdr/collision.h"

leBob bob_init(leBob BOB, SDL_Renderer *render)
{
    BOB.skin=TextureCreate(render, "res/bob.png", 255, 0, 255, 255);
    BOB.skinPos.x=0;
    BOB.skinPos.y=0;
    BOB.skinPos.w=BOB.skin->w/4;
    BOB.skinPos.h=BOB.skin->h;
    BOB.level = 1;
    BOB.hpMax = 100;
    BOB.hp = BOB.hpMax;
    BOB.speed = 3;
    BOB.money = 0;
    BOB.luck= 1;
    BOB.direction=2;
    BOB.collision = 20;
    BOB.attackspeed=410;
    BOB.distattack=30;
    BOB.pos.x = WWIN / 2 - BOB.skin->w / 2;
    BOB.pos.y = HWIN / 2 - BOB.skin->h / 2;
    BOB.pos.w = BOB.skin->w/4;
    BOB.pos.h = BOB.skin->h;
    BOB.posTemp=BOB.pos;
    BOB.exist=1;
    return BOB;
}

leBob enm_init(leBob BOB, leBob BOB0, leMap *MAP, SDL_Renderer *render)
{
    BOB.skin=TextureCreate(render, "res/gob1.png", 255, 0, 255, 255);
    BOB.skinPos.x=0;
    BOB.skinPos.y=0;
    BOB.skinPos.w=TCASE;
    BOB.skinPos.h=TCASE;
    BOB.level = 1;
    BOB.hpMax = 1;
    BOB.hp = 4;
    BOB.speed = 2;
    BOB.money = 10;
    BOB.luck= 1;
    BOB.collision = 20;
    BOB.fov=225; // Distance de vue
    BOB.attackspeed=410; // Vitesse entre chaque attaque
    BOB.distattack=30; // Distance d'attaque cac
    BOB.exist=1;
    BOB.pos.x = aleatoire(0, WWIN-TCASE);
    BOB.pos.y = aleatoire(0, HWIN-TCASE);

    while
    (
        collisionmap(&BOB.pos, MAP, 1, 16, 0, 4, 4) ||
        collisionmap(&BOB.pos, MAP, 2, 0, 16, 4, 4) ||
        distancepoint(BOB0.pos.x, BOB0.pos.y, BOB.pos.x, BOB.pos.y)<BOB.fov
    )
    {
        BOB.pos.x = aleatoire(0, WWIN-TCASE);
        BOB.pos.y = aleatoire(0, HWIN-TCASE);
    }

    BOB.pos.w = TCASE;
    BOB.pos.h = TCASE;
    BOB.posTemp=BOB.pos;
    return BOB;
}

void sort_init(leJeu *JEU, SDL_Renderer *render)
{
    int i;
    JEU->sort1.last_use=0;
    JEU->sort1.power=5;
    JEU->sort1.scale=10;
    JEU->sort1.skin=1;
    JEU->sort1.speed=6;
    JEU->sort1.distanceattaque=130;
    for (i=0; i<MAX_PROJECTILES_PAR_SORT; i++)
    {
        JEU->sort1.projectiles[i].pos.x=0;
        JEU->sort1.projectiles[i].pos.y=0;
        JEU->sort1.projectiles[i].pos.h=TCASE;
        JEU->sort1.projectiles[i].pos.w=TCASE;
        JEU->sort1.projectiles[i].d.x=0;
        JEU->sort1.projectiles[i].d.y=0;
        JEU->sort1.projectiles[i].mov.duration=0;
        JEU->sort1.projectiles[i].mov.now=0;
        JEU->sort1.projectiles[i].mov.start=0;
        JEU->sort1.projectiles[i].exist=0;
    }

    JEU->sort1_enm.last_use=0;
    JEU->sort1_enm.power=5;
    JEU->sort1_enm.scale=10;
    JEU->sort1_enm.skin=2;
    JEU->sort1_enm.speed=4;
    JEU->sort1_enm.distanceattaque=130;
    for (i=0; i<MAX_PROJECTILES_PAR_SORT; i++)
    {
        JEU->sort1_enm.projectiles[i].pos.x=0;
        JEU->sort1_enm.projectiles[i].pos.y=0;
        JEU->sort1_enm.projectiles[i].pos.h=TCASE;
        JEU->sort1_enm.projectiles[i].pos.w=TCASE;
        JEU->sort1_enm.projectiles[i].d.x=0;
        JEU->sort1_enm.projectiles[i].d.y=0;
        JEU->sort1_enm.projectiles[i].mov.duration=0;
        JEU->sort1_enm.projectiles[i].mov.now=0;
        JEU->sort1_enm.projectiles[i].mov.start=0;
        JEU->sort1_enm.projectiles[i].exist=0;
    }
}

void map_init(leMap *MAP)
{
 
	int i, j;
	MAP->quitfloor = 0;
    for (i=0; i<HCASE; i++)
    {
        for (j=0; j<WCASE; j++)
        {
            MAP->tile[i][j]=0;
        }
    }
    for (i=0; i<HCASE; i++)
    {
        for (j=0; j<WCASE; j++)
        {
            MAP->tile2[i][j]=0;
        }
    }
    for (i=0; i<HCASE; i++)
    {
        for (j=0; j<WCASE; j++)
        {
            MAP->obj[i][j]=0;
        }
    }
    for (i=0; i<HCASE; i++)
    {
        for (j=0; j<WCASE; j++)
        {
            MAP->col[i][j]=0;
        }
    }
}