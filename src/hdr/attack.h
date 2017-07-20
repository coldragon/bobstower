#ifndef ATTACK_H_INCLUDED
#define ATTACK_H_INCLUDED
#include "struct.h"

void attackcac_enm(leBob *ENM, leBob *BOB, leAudio *JEU);
void create_projectile(leAudio *JEU, leSort *SORT, leBob *BOB);
void move_projectile(leAudio *JEU, leBob *BOB);
void attack_bob(leBob *BOB, leAudio *JEU, leInput *INPUT);

#endif // ATTACK_H_INCLUDED
