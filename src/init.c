#include "hdr/texture.h"
#include "hdr/define.h"
#include "hdr/struct.h"
#include "hdr/basic.h"

leBob bob_init(leBob BOB, SDL_Renderer *render)
{
    BOB.skin=TextureCreate(render, "res/bob.png", 255, 0, 255, 255);
    BOB.skinPos.x=0;
    BOB.skinPos.y=0;
    BOB.skinPos.w=BOB.skin->w/4;
    BOB.skinPos.h=BOB.skin->h;
    BOB.level = 1;
    BOB.hpMax = 10;
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

leBob enm_init(leBob BOB, leMap *MAP, SDL_Renderer *render)
{
    BOB.skin=TextureCreate(render, "res/gob1.png", 255, 0, 255, 255);
    BOB.skinPos.x=0;
    BOB.skinPos.y=0;
    BOB.skinPos.w=TCASE;
    BOB.skinPos.h=TCASE;
    BOB.level = 1;
    BOB.hpMax = 4;
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

    while ((MAP->col[(BOB.pos.y+23)/32][(BOB.pos.x+4)/32]== 1 || MAP->col[(BOB.pos.y+23)/32][(BOB.pos.x+28)/32]== 1 ||
            MAP->col[(BOB.pos.y+32)/32][(BOB.pos.x+4)/32]== 1 || MAP->col[(BOB.pos.y+32)/32][(BOB.pos.x+28)/32]== 1) ||
            (MAP->col[(BOB.pos.y)/32][(BOB.pos.x+4)/32]== 2 || MAP->col[(BOB.pos.y)/32][(BOB.pos.x+28)/32]== 2 ||
             MAP->col[(BOB.pos.y+10)/32][(BOB.pos.x+4)/32]== 2 || MAP->col[(BOB.pos.y+10)/32][(BOB.pos.x+28)/32]== 2))
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
    JEU->sort1_enm.speed=3;
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
    int initTile[HCASE][WCASE] =
    {
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
        {3, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3},
        {3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
        {3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 0, 2, 3},
        {3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 9, 1, 3},
        {3, 2, 9, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3},
        {3, 1, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    };
    for (i=0; i<HCASE; i++)
    {
        for (j=0; j<WCASE; j++)
        {
            MAP->tile[i][j]=initTile[i][j];
        }
    }

    int initTile2[HCASE][WCASE] =
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 6, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 6, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 6, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 6, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 10,2, 3},
        {0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
    };
    for (i=0; i<HCASE; i++)
    {
        for (j=0; j<WCASE; j++)
        {
            MAP->tile2[i][j]=initTile2[i][j];
        }
    }

    int initObj[HCASE][WCASE] =
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 7, 3, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    for (i=0; i<HCASE; i++)
    {
        for (j=0; j<WCASE; j++)
        {
            MAP->obj[i][j]=initObj[i][j];
        }
    }

    int initCol[HCASE][WCASE] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 2, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1},
        {1, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    };
    for (i=0; i<HCASE; i++)
    {
        for (j=0; j<WCASE; j++)
        {
            MAP->col[i][j]=initCol[i][j];
        }
    }
}
