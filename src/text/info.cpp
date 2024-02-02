#include <info.h>

Info::Info(SDL_Renderer *renderer)
{
  this->renderer = renderer;

  font = FC_CreateFont();

  FC_LoadFont(font, renderer, fontName, fontSize, fontColor, TTF_STYLE_NORMAL);
}

Info::~Info()
{
  FC_FreeFont(font);
}

int addLine(int *y, int lineHeight)
{
  *y += lineHeight;
  return *y;
}

void Info::render()
{
  int x = 10;
  int y = 10;

  SDL_Rect rect = {0, 0, 240, 1080};
  SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
  SDL_RenderFillRect(renderer, &rect);
}
