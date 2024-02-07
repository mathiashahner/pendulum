#include <pendulum.h>

Pendulum::Pendulum(SDL_Renderer *renderer, double length, double radius, Uint32 color)
{
  this->deltaTime = 0;
  this->length = length;
  this->radius = radius;
  this->renderer = renderer;
  this->period = 2 * M_PI * sqrt(this->length / GRAVITY);

  this->line = new Line(renderer, 0, 0, 0, 0, color);
  this->circle = new Circle(renderer, 0, 0, radius, color);
}

Pendulum::~Pendulum()
{
}

void Pendulum::update()
{
  this->deltaTime += 0.1;

  double theta = MAX_AMPLITUDE * cos(2 * M_PI / period * this->deltaTime);

  double x = (this->length * sin(theta)) + (1080 / 2);
  double y = (this->length * cos(theta)) + (720 / 2);

  this->line->update(1080 / 2, 720 / 2, x, y);
  this->circle->update(x, y, this->radius);
}

void Pendulum::render()
{
  line->render();
  circle->render();
}
