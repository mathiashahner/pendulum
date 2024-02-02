#include <point.h>

Point::Point() {}

Point::Point(int x, int y)
{
  this->x = x;
  this->y = y;
}

Point::Point(SDL_Renderer *renderer, int x, int y, Uint32 color)
{
  this->renderer = renderer;

  this->x = x;
  this->y = y;

  this->color.r = color >> 24;
  this->color.g = (color >> 16) & 0xFF;
  this->color.b = (color >> 8) & 0xFF;
  this->color.a = color & 0xFF;
}

void Point::render()
{
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawPoint(renderer, x, y);
}
