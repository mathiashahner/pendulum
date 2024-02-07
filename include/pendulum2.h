#ifndef PENDULUM2_H
#define PENDULUM2_H

#include <math.h>
#include <line.h>
#include <circle.h>

#define STEP 0.1
#define GRAVITY 9.81
#define MAX_AMPLITUDE 90 * M_PI / 180.0

class Pendulum2
{
public:
  Pendulum2(SDL_Renderer *renderer, double length, double radius, Uint32 color);
  ~Pendulum2();

  void update();
  void render();

private:
  double radius;
  double length;
  double period;

  double theta;
  double omega;

  Line *line;
  Circle *circle;
  SDL_Renderer *renderer;

  double f(double omega);
  double g(double theta);
};

#endif
