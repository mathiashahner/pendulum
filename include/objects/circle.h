#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>

class Circle
{
public:
  Circle(SDL_Renderer *renderer, int x, int y, int radius, Uint32 color);

  void render(int xOffset, int yOffset);

private:
  int x, y;
  int radius;

  SDL_Color color;
  SDL_Renderer *renderer;
};

#endif
