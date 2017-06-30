#ifndef HEADER_INCLUDED_INIT
#define HEADER_INCLUDED_INIT

void open_sdl_shit();
void close_sdl_shit();
leBob bob_init(leBob BOB, SDL_Renderer *render);
leBob enm_init(leBob BOB, leBob BOB0, leMap *MAP, SDL_Renderer *render);
void sort_init(leJeu *JEU, SDL_Renderer *render);
void map_init(leMap *MAP);

#endif
