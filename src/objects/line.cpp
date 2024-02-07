#include <line.h>

Line::Line() {}

Line::Line(SDL_Renderer *renderer, double x1, double y1, double x2, double y2, Uint32 color)
{
  this->renderer = renderer;

  this->color.r = color >> 24;
  this->color.g = (color >> 16) & 0xFF;
  this->color.b = (color >> 8) & 0xFF;
  this->color.a = color & 0xFF;

  this->x1 = x1;
  this->y1 = y1;
  this->x2 = x2;
  this->y2 = y2;
}

void Line::render()
{
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Line::update(double x1, double y1, double x2, double y2)
{
  this->x1 = x1;
  this->y1 = y1;
  this->x2 = x2;
  this->y2 = y2;
}
