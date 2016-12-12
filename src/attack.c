#include "hdr/attack.h"
#include "hdr/basic.h"
#include "hdr/struct.h"

void attackcac_enm(leBob *ENM, leBob *BOB, leJeu *JEU)
{
    int i;
    for (i=0; i<ENNEMY_MAX; i++)
    {
        if (ENM[i].tempsAttack-ENM[i].tempsInitialAttack >= ENM[i].attackspeed)
        {
        if (distancepoint(ENM[i].pos.x+16, ENM[i].pos.y+16, BOB->pos.x+16, BOB->pos.y+16)<ENM[i].distattack)
        {
        BOB->hp--;
        Mix_PlayChannel(1, JEU->son4, 0);
        }
        ENM[i].tempsInitialAttack=ENM[i].tempsAttack;
        }
        else
        {

        }
        ENM[i].tempsAttack=SDL_GetTicks();

    }
}
