#ifndef HEADER_INCLUDED_COLLISION
#define HEADER_INCLUDED_COLLISION
#include "struct.h"

void collision(leBob *BOB, leMap *MAP);
void collisionEnm(leBob *ENM, leMap *MAP, leBob *BOB);
void objetcollision(leMap *MAP, leBob *BOB, leJeu *JEU);
void sortcollision(leMap *MAP, leBob *ENM, leJeu *JEU);

#endif
