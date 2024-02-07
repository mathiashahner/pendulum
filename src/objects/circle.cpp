#include <circle.h>

Circle::Circle(SDL_Renderer *renderer, double x, double y, double radius, Uint32 color)
{
  this->renderer = renderer;
  this->x = x;
  this->y = y;
  this->radius = radius;

  this->color.r = color >> 24;
  this->color.g = (color >> 16) & 0xFF;
  this->color.b = (color >> 8) & 0xFF;
  this->color.a = color & 0xFF;
}

void Circle::update(double x, double y, double radius)
{
  this->x = x;
  this->y = y;
  this->radius = radius;
}

void Circle::render()
{
  double status = 0;
  double offsetx = 0;
  double offsety = radius;
  double d = radius - 1;

  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  while (offsety >= offsetx)
  {
    status += SDL_RenderDrawLineF(renderer, x - offsety, y + offsetx, x + offsety, y + offsetx);
    status += SDL_RenderDrawLineF(renderer, x - offsetx, y + offsety, x + offsetx, y + offsety);
    status += SDL_RenderDrawLineF(renderer, x - offsetx, y - offsety, x + offsetx, y - offsety);
    status += SDL_RenderDrawLineF(renderer, x - offsety, y - offsetx, x + offsety, y - offsetx);

    if (status < 0)
    {
      status = -1;
      break;
    }

    if (d >= 2 * offsetx)
    {
      d -= 2 * offsetx + 1;
      offsetx += 1;
    }
    else if (d < 2 * (radius - offsety))
    {
      d += 2 * offsety - 1;
      offsety -= 1;
    }
    else
    {
      d += 2 * (offsety - offsetx - 1);
      offsety -= 1;
      offsetx += 1;
    }
  }
}
