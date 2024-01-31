#include <circle.h>

Circle::Circle(SDL_Renderer *renderer, int x, int y, int radius, Uint32 color)
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

void Circle::render(int xOffset, int yOffset)
{
  int status = 0;
  int offsetx = 0;
  int offsety = radius;
  int d = radius - 1;

  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  while (offsety >= offsetx)
  {
    status += SDL_RenderDrawLine(renderer, x - offsety + xOffset, y + offsetx + yOffset,
                                 x + offsety + xOffset, y + offsetx + yOffset);
    status += SDL_RenderDrawLine(renderer, x - offsetx + xOffset, y + offsety + yOffset,
                                 x + offsetx + xOffset, y + offsety + yOffset);
    status += SDL_RenderDrawLine(renderer, x - offsetx + xOffset, y - offsety + yOffset,
                                 x + offsetx + xOffset, y - offsety + yOffset);
    status += SDL_RenderDrawLine(renderer, x - offsety + xOffset, y - offsetx + yOffset,
                                 x + offsety + xOffset, y - offsetx + yOffset);

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
