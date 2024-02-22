#ifndef PENDULUM_H
#define PENDULUM_H

#include <math.h>
#include <line.h>
#include <circle.h>

#define GRAVITY 9.81
#define MAX_AMPLITUDE 90 * M_PI / 180.0

class Pendulum
{
public:
  Pendulum(SDL_Renderer *renderer, double length, double radius, Uint32 color);
  ~Pendulum();

  void update();
  void render();

private:
  double radius;
  double length;
  double period;
  double deltaTime;

  Line *line;
  Circle *circle;
  SDL_Renderer *renderer;
};

#endif
