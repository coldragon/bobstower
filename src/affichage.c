#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "hdr/define.h"
#include "hdr/texture.h"
#include "hdr/struct.h"

extern const SDL_Color WHITE;


void AfficherBob(SDL_Renderer* render, leBob *BOB)
{
  TextureRender(render, BOB->skin, BOB->pos.x, BOB->pos.y, &BOB->skinPos);
}

void CleanScreen(SDL_Renderer* render, int r, int g, int b)
{
  SDL_SetRenderDrawColor(render, r, g, b, 255);
  SDL_RenderClear(render);
}

void AfficherMap_layer1(SDL_Renderer* render, Texture* tileset, leMap MAP)
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

void AfficherMap_layer2(SDL_Renderer* render, Texture* tileset, leMap MAP)
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
        posTile.x=TCASE*(MAP.tile2[i][j]%(wtileset));
        posTile.y=TCASE*(MAP.tile2[i][j]/(wtileset));
        if (MAP.tile2[i][j])
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

void AfficherGui(SDL_Renderer* render, Texture* guiset, leBob *BOB, TTF_Font *police)
{
  char charTemp[100]={0};
  SDL_Surface* hpTxt;
  SDL_Texture* hpTexture;
  SDL_Rect rect;

  rect.y=42; rect.x=0; rect.h=32; rect.w=800;
  TextureRender(render, guiset, rect.y, rect.x, &rect);
  rect.y=0; rect.h=TCASE; rect.w=211;
  TextureRender(render, guiset, 0, 0, &rect);
  rect.y=TCASE; rect.h=10; rect.x=0; rect.w=4+((BOB->hp*201)/BOB->hpMax);
  TextureRender(render, guiset, 0, 16, &rect);

  // HP / HPMAX
  sprintf(charTemp, "LVL : %d -- HP : %d/%d", BOB->level, BOB->hp, BOB->hpMax);
  hpTxt = TTF_RenderText_Blended(police, &charTemp, WHITE);
  rect.x=5; rect.y=0;
  rect.h=hpTxt->h; rect.w=hpTxt->w;
  hpTexture = SDL_CreateTextureFromSurface(render, hpTxt);
  SDL_RenderCopy(render, hpTexture, NULL, &rect);
  SDL_FreeSurface(hpTxt);

  sprintf(&charTemp, "%d", BOB->money);
  rect.x=224
  ; rect.y=4;
  hpTxt = TTF_RenderText_Blended(police, &charTemp, WHITE);

  rect.h=hpTxt->h; rect.w=hpTxt->w;
  hpTexture = SDL_CreateTextureFromSurface(render, hpTxt);

  SDL_RenderCopy(render, hpTexture, NULL, &rect);
  SDL_FreeSurface(hpTxt);
}
