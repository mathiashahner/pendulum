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
  double theta, x, y;
  int width, height, screenCenterX, screenCenterY;

  SDL_GetRendererOutputSize(renderer, &width, &height);
  screenCenterX = width / 2;
  screenCenterY = height / 3;

  this->deltaTime += 0.1;
  theta = MAX_AMPLITUDE * cos(2 * M_PI / period * this->deltaTime);

  x = (this->length * sin(theta)) + screenCenterX;
  y = (this->length * cos(theta)) + screenCenterY;

  this->line->update(screenCenterX, screenCenterY, x, y);
  this->circle->update(x, y, this->radius);
}

void Pendulum::render()
{
  line->render();
  circle->render();
}
