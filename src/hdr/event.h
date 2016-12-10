#ifndef HEADER_INCLUDED_EVENT
#define HEADER_INCLUDED_EVENT

void mouvement(SDL_Event event,SDL_Renderer *render, leBob *BOB0, int *continuer, int *restartgame);
void menuavantjeux(SDL_Event event, int *startmenu, int *restartgame, int *continuer);

#endif
