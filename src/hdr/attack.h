#ifndef ATTACK_H_INCLUDED
#define ATTACK_H_INCLUDED
#include "struct.h"

void attackcac_enm(leBob *ENM, leBob *BOB, leJeu *JEU);
void create_projectile(leJeu *JEU, leBob *BOB);
void move_projectile(leJeu *JEU, leBob *BOB);
void attack_bob(leBob *BOB, leJeu *JEU, leInput *INPUT);

#endif // ATTACK_H_INCLUDED
