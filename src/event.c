#include <SDL2/SDL.h>
#include "hdr/other_screen.h"
#include "hdr/struct.h"

void inputReturn(leInput *INPUT)
{
    SDL_Event event;

    while(SDL_PollEvent(&event))

    {
        switch (event.type)
        {
        case SDL_QUIT:
            INPUT->quit=1;
            break;
        case SDL_KEYDOWN:
            INPUT->key[event.key.keysym.scancode]=1;
            break;
        case SDL_KEYUP:
            INPUT->key[event.key.keysym.scancode]=0;
            break;
        default:
            break;
        }
    }
}

void inputInit(leInput *INPUT)
{
    memset(INPUT->key, 0, sizeof(INPUT->key));
    INPUT->quit=0;
}


void mouvement(leInput *INPUT, SDL_Renderer *render,leBob *BOB0, int *continuer, int *restartgame)
{
    SDL_Event event;

    BOB0->posTemp.x=BOB0->pos.x;
    BOB0->posTemp.y=BOB0->pos.y;

    if  (INPUT->quit)
    {
        *continuer = 0;
        *restartgame = 0;
    }
    if  (INPUT->key[SDL_SCANCODE_UP])
    {
        BOB0->pos.y=BOB0->pos.y-BOB0->speed;
        BOB0->skinPos.x=TCASE;
    }
    if  (INPUT->key[SDL_SCANCODE_DOWN])
    {
        BOB0->pos.y=BOB0->pos.y+BOB0->speed;
        BOB0->skinPos.x=0;
    }
    if  (INPUT->key[SDL_SCANCODE_LEFT])
    {
        BOB0->pos.x=BOB0->pos.x-BOB0->speed;
        BOB0->skinPos.x=TCASE*2;
    }
    if  (INPUT->key[SDL_SCANCODE_RIGHT])
    {
        BOB0->pos.x=BOB0->pos.x+BOB0->speed;
        BOB0->skinPos.x=TCASE*3;
    }
    if  (INPUT->key[SDL_SCANCODE_ESCAPE])
    {
        inputInit(INPUT);
        if(menu_escape(render)==1)
          {
            *continuer = 0;
            *restartgame = 0;
          }
    }

    if (INPUT->key[SDL_SCANCODE_A])
    {
        if (BOB0->hp<BOB0->hpMax)
        BOB0->hp+=5;
    }

    if (INPUT->key[SDL_SCANCODE_Z])
    {
        BOB0->hp-=5;
    }
}

void mov_enm(SDL_Renderer *render, leBob *ENM)
{
    int i;
    for (i=0; i<ENNEMY_MAX; i++)
    {
        ENM[i].pos.x+=(aleatoire(0, 2)-1)*ENM[i].speed;
        ENM[i].pos.y+=(aleatoire(0, 2)-1)*ENM[i].speed;
    }
}

void menuavantjeux(int *startmenu, int *restartgame, int *continuer)
{
    SDL_Event event;

    SDL_WaitEvent(&event);
    switch(event.type)
    {
    case SDL_QUIT:
        *restartgame = 0;
        *continuer = 0;
        *startmenu = 0;
        break;

    case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
        case SDLK_RETURN:
            *startmenu=0;
            break;
        }
        break;
    }
}
