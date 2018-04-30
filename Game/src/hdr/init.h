#ifndef HEADER_INCLUDED_INIT
#define HEADER_INCLUDED_INIT
#include "struct.h"

void open_sdl_shit();
void close_sdl_shit();
void coreInit(leCore *CORE);
void coreFree(leCore *CORE);
void bob_init(leBob *BOB, SDL_Renderer *render, leMap MAP);
leBob enm_init(leBob BOB, leBob BOB0, leMap *MAP, SDL_Renderer *render);
void sort_init(leAudio *JEU, SDL_Renderer *render);
void map_init(leMap *MAP);
void main_loop(leCore *CORE);

#endif
