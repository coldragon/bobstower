#ifndef HEADER_INCLUDED_COLLISION
#define HEADER_INCLUDED_COLLISION
#include "struct.h"

int collisionmap(SDL_Rect *rect, leMap *MAP, int type, int haut, int bas, int gauche, int droite);
void collision(leBob *BOB, leMap *MAP);
void collisionEnm(leBob *ENM, leMap *MAP, leBob *BOB);
void objetcollision(leMap *MAP, leBob *BOB, leJeu *JEU);
void sortcollision(leMap *MAP, leBob *ENM, leJeu *JEU);

#endif
