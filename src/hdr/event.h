#ifndef HEADER_INCLUDED_EVENT
#define HEADER_INCLUDED_EVENT

void inputInit(leInput* INPUT);
void inputReturn(leInput *INPUT);
void mouvement(leInput *INPUT, SDL_Renderer *render, leBob *BOB0, int *continuer, int *restartgame);
void menuavantjeux(int *startmenu, int *restartgame, int *continuer);

#endif
