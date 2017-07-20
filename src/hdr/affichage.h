#ifndef HEADER_INCLUDED_AFFICHAGE
#define HEADER_INCLUDED_AFFICHAGE

void AfficherBob(SDL_Renderer* render, leBob *BOB);
void AfficherEnm(SDL_Renderer* render, leBob *ENM);
void CleanScreen(SDL_Renderer* render, int r, int g, int b);
void AfficherMap_layer1(SDL_Renderer* render, Texture* tileset, leMap *MAP);
void AfficherMap_layer2(SDL_Renderer* render, Texture* tileset, leMap *MAP);
void AfficherObj(SDL_Renderer* render, Texture* objset, leMap *MAP);
void AfficherSort(SDL_Renderer* render, Texture* sortset, leAudio *JEU);
void AfficherGui(SDL_Renderer* render, Texture* guiset, leBob *BOB, TTF_Font *police);
void AFFICHAGE(leCore *CORE, leBob *ENM, leBob *BOB0);

#endif
