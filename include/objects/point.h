#ifndef RECT_H
#define RECT_H

#include <SDL2/SDL.h>

class Point
{
public:
  Point();
  Point(int x, int y);
  Point(SDL_Renderer *renderer, int x, int y, Uint32 color);

  int x, y;

  void render(int xOffset, int yOffset);

private:
  SDL_Color color;
  SDL_Renderer *renderer;
};

#endif
