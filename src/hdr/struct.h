#include "define.h"
#include "texture.h"

struct leBob
{
  SDL_Rect pos, posTemp;
  Texture *skin;
  SDL_Rect skinPos;

  //caract
  int speed;
  int hp;
  int hpMax;
  int money;
  int level;

};
typedef struct leBob leBob;

struct leMap
{
  int tile[HCASE][WCASE];
  int col[HCASE][WCASE];
  int obj[HCASE][WCASE];
  int tpin[HCASE][WCASE];
  int tpout[HCASE][WCASE];
};
typedef struct leMap leMap;
