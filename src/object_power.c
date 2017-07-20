#include <SDL2/SDL_mixer.h>
#include "hdr/struct.h"
#include "hdr/basic.h"

void callbackActionObject(int* objectType, leBob* BOB, leMap* MAP, leAudio* JEU)
{

    switch(*objectType)
    {
    case 1:
        if(BOB->hp < BOB->hpMax)
        {
            BOB->hp+=2+BOB->level;
            if(BOB->hp > BOB->hpMax)
                BOB->hp=BOB->hpMax;

            *objectType = 0;
            Mix_PlayChannel(1, JEU->sound2, 0);
        }
        break;

    case 2:
        BOB->hpMax+=1+(BOB->level/2);
        BOB->hp+=1+(BOB->level/2);

        *objectType = 0;
        Mix_PlayChannel(1, JEU->sound3, 0);
        break;

    case 3: // coffre
        BOB->money+=(aleatoire(2, 10)*BOB->level)+(aleatoire(2, 10)*BOB->luck);

        *objectType = 4;
        Mix_PlayChannel(5, JEU->sound1, 0);
        break;

    case 7:
        BOB->hp-=1;

        *objectType = 8;
        Mix_PlayChannel(1, JEU->sound4, 0);
        break;
	case 9: // Exit
		MAP->quitfloor = 1;
    default:
        break;
    }

}

void checkObject(leBob* BOB, leMap* MAP, leAudio *JEU)
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
