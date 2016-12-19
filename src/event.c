#include <SDL2/SDL.h>
#include "hdr/other_screen.h"
#include "hdr/struct.h"
#include "hdr/basic.h"

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
        BOB0->direction=0;
    }
    if  (INPUT->key[SDL_SCANCODE_DOWN])
    {
        BOB0->pos.y=BOB0->pos.y+BOB0->speed;
        BOB0->skinPos.x=0;
        BOB0->direction=2;
    }
    if  (INPUT->key[SDL_SCANCODE_LEFT])
    {
        BOB0->pos.x=BOB0->pos.x-BOB0->speed;
        BOB0->skinPos.x=TCASE*2;
        BOB0->direction=3;

    }
    if  (INPUT->key[SDL_SCANCODE_RIGHT])
    {
        BOB0->pos.x=BOB0->pos.x+BOB0->speed;
        BOB0->skinPos.x=TCASE*3;
        BOB0->direction=1;
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
}

void mov_enm(SDL_Renderer *render, leBob *ENM, leBob *BOB)
{
    int i;
    for (i=0; i<ENNEMY_MAX; i++)
    {
        if (ENM[i].exist)
        {
            if (ENM[i].tmov.now-ENM[i].tmov.start >= 50)
            {
                ENM[i].posTemp.x=ENM[i].pos.x;
                ENM[i].posTemp.y=ENM[i].pos.y;

                if (distancepoint(ENM[i].pos.x, ENM[i].pos.y, BOB->pos.x, BOB->pos.y)<ENM[i].fov)
                {
                    int x, y;
                    x=ENM[i].pos.x-BOB->pos.x;
                    y=ENM[i].pos.y-BOB->pos.y;

                    if (x<-3)
                        ENM[i].pos.x+=ENM[i].speed;
                    if (x>3)
                        ENM[i].pos.x-=ENM[i].speed;
                    if (y<-3)
                        ENM[i].pos.y+=ENM[i].speed;
                    if (y>3)
                        ENM[i].pos.y-=ENM[i].speed;
                }

                ENM[i].tmov.start=ENM[i].tmov.now;
            }
            ENM[i].tmov.now=SDL_GetTicks();
        }
    }
}

void menuavantjeux(leInput *INPUT, int *startmenu, int *restartgame, int *continuer)
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
