#include <SDL2/SDL.h>
#include "hdr/define.h"
#include "hdr/texture.h"
#include "hdr/struct.h"

void AfficherBob(SDL_Renderer* render, leBob BOB)
{
  TextureRender(render, BOB.skin, BOB.pos.x, BOB.pos.y, &BOB.skinPos);
}

void CleanScreen(SDL_Renderer* render, int r, int g, int b)
{
  SDL_SetRenderDrawColor(render, r, g, b, 255);
  SDL_RenderClear(render);
}

void AfficherMap(SDL_Renderer* render, Texture* tileset, leMap MAP)
{
  SDL_Rect pos, posTile;
  posTile.w=TCASE; posTile.h=TCASE;
  int i, j;
  const int wtileset = tileset->w/TCASE;
  for (i=0; i<HCASE; i++)
  {
    for (j=0; j<WCASE; j++)
    {
        pos.x=j*TCASE;
        pos.y=i*TCASE;
        posTile.x=TCASE*(MAP.tile[i][j]%(wtileset));
        posTile.y=TCASE*(MAP.tile[i][j]/(wtileset));
        TextureRender(render, tileset, pos.x, pos.y, &posTile);
    }
  }
}

void AfficherObj(SDL_Renderer* render, Texture* objset, leMap MAP)
{
  SDL_Rect pos, posObj;
  posObj.w=TCASE; posObj.h=TCASE;
  int i, j;
  const int wobjset = objset->w/TCASE;
  for (i=0; i<HCASE; i++)
  {
    for (j=0; j<WCASE; j++)
    {
      pos.x=j*TCASE;
      pos.y=i*TCASE;
      posObj.x=TCASE*(MAP.obj[i][j]%(wobjset));
      posObj.y=TCASE*(MAP.obj[i][j]/(wobjset));
      TextureRender(render, objset, pos.x, pos.y, &posObj);
    }
  }
}
