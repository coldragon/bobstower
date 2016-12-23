#ifndef HEADER_INCLUDED_EVENT
#define HEADER_INCLUDED_EVENT

void inputInit(leInput* INPUT);
void inputReturn(leInput *INPUT);
void mouvement(leInput *INPUT, SDL_Renderer *render,leBob *BOB, leMap *MAP, int *continuer, int *restartgame);
void mov_enm(SDL_Renderer *render, leBob *ENM, leBob *BOB);
void menuavantjeux(leInput *INPUT, int *startmenu, int *restartgame, int *continuer);

#endif
