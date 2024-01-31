#ifndef LINE_H
#define LINE_H

#include <SDL2/SDL.h>

class Line
{
public:
  Line();
  Line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, Uint32 color);

  int x1, x2;
  int y1, y2;

  void update(int x1, int y1, int x2, int y2);
  void render(int xOffset, int yOffset);

private:
  SDL_Color color;
  SDL_Renderer *renderer;
};

#endif
