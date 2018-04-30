#ifndef HEADER_INCLUDED_AFFICHAGE
#define HEADER_INCLUDED_AFFICHAGE
#include <SDL2/SDL.h>
#include "struct.h"
#include "texture.h"

void cleanScreen(SDL_Renderer* render, int r, int g, int b);
void afficherMap_layer1(SDL_Renderer* render, Texture* tileset, leMap *MAP);
void afficherMap_layer2(SDL_Renderer* render, Texture* tileset, leMap *MAP);
void afficherObj(SDL_Renderer* render, Texture* objset, leMap *MAP);
void afficherCol(SDL_Renderer* render, leMap *MAP, Texture* gui);
void afficherSpawn(SDL_Renderer* render, leMap *MAP, Texture *gui);
void afficherExit(SDL_Renderer* render, leMap *MAP, Texture *gui);
void afficherGui(SDL_Renderer* render, leInput *INPUT, Texture* gui);
void afficherTileEdit(SDL_Renderer* render, leTexPack TEXPACK, leInput *INPUT, leState *STATE);
void AFFICHAGE(leCore *CORE);

#endif
