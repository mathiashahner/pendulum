#ifndef LINE_H
#define LINE_H

#include <SDL2/SDL.h>

class Line
{
public:
  Line();
  Line(SDL_Renderer *renderer, double x1, double y1, double x2, double y2, Uint32 color);

  int x1, x2;
  int y1, y2;

  void update(double x1, double y1, double x2, double y2);
  void render();

private:
  SDL_Color color;
  SDL_Renderer *renderer;
};

#endif
