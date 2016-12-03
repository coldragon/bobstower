#include <SDL2/SDL.h>
#include "hdr/struct.h"
#include "hdr/texture.h"

int menu_escape(SDL_Renderer *render)
{
  Texture *img;
  SDL_Event event;
  int action = 0;
  int boucle = 1;
  printf("Escape Menu OK");
  img=TextureCreate(render, "res/escapetitle.png", 255, 0, 255, 255);
  TextureRender(render, img, 0, 0, NULL);
  SDL_RenderPresent(render);
  SDL_Delay(150);
  while(boucle)
  {
    SDL_WaitEvent(&event);
    switch(event.type)
    {
      case SDL_QUIT:
      boucle = 0;

      break;

      case SDL_KEYDOWN:
      switch(event.key.keysym.sym)
      {
        case SDLK_ESCAPE:
        boucle = 0;
        break;
      }
      break;
      //Fin switch
    }
  }
  return action;
}
