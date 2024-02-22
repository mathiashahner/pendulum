#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>

class Circle
{
public:
  Circle(SDL_Renderer *renderer, double x, double y, double radius, Uint32 color);

  void render();
  void update(double x, double y, double radius);

  double momentAboutCM();
  double getKineticEnergy();
  double rotationalEnergy();
  double translationalEnergy();

  double mass = 200.0;
  double moment = 0.0;
  double velocityX = 0.0;
  double velocityY = 0.0;
  double angularVelocity = 0.0;

private:
  double x, y;
  double radius;

  SDL_Color color;
  SDL_Renderer *renderer;
};

#endif
