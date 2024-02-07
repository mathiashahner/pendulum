#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>

class Circle
{
public:
  Circle(SDL_Renderer *renderer, double x, double y, double radius, Uint32 color);

  void render();
  void update(double x, double y, double radius);

private:
  double x, y;
  double radius;

  SDL_Color color;
  SDL_Renderer *renderer;
};

#endif
