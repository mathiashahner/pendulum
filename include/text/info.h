#ifndef INFO_H
#define INFO_H

#include <SDL_FontCache.h>

class Info
{
public:
  Info(SDL_Renderer *renderer);
  ~Info();

  void render();

private:
  const int fontSize = 16;
  const char *fontName = "../assets/space-mono.ttf";
  const SDL_Color fontColor = FC_MakeColor(255, 255, 255, 255);

  FC_Font *font;
  SDL_Renderer *renderer;
};

#endif
