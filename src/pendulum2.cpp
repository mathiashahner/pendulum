#include <pendulum2.h>

Pendulum2::Pendulum2(SDL_Renderer *renderer, double length, double radius, Uint32 color)
{
  this->length = length;
  this->radius = radius;
  this->renderer = renderer;
  this->period = 2 * M_PI * sqrt(this->length / GRAVITY);

  this->line = new Line(renderer, 0, 0, 0, 0, color);
  this->circle = new Circle(renderer, 0, 0, radius, color);

  theta = MAX_AMPLITUDE;
  omega = 0.0;
}

Pendulum2::~Pendulum2()
{
}

double Pendulum2::f(double omega)
{
  return omega;
}

double Pendulum2::g(double theta)
{
  return -(GRAVITY / this->length) * sin(theta);
}

void Pendulum2::update()
{
  double k1, k2, k3, k4;
  double temp_theta, temp_omega;

  k1 = STEP * f(omega);
  k2 = STEP * f(omega + 0.5 * k1);
  k3 = STEP * f(omega + 0.5 * k2);
  k4 = STEP * f(omega + k3);
  temp_theta = theta + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);

  k1 = STEP * g(theta);
  k2 = STEP * g(theta + 0.5 * k1);
  k3 = STEP * g(theta + 0.5 * k2);
  k4 = STEP * g(theta + k3);
  temp_omega = omega + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);

  theta = temp_theta;
  omega = temp_omega;

  double x = (this->length * sin(theta)) + (1080 / 2);
  double y = (this->length * cos(theta)) + (720 / 2);

  this->line->update(1080 / 2, 720 / 2, x, y);
  this->circle->update(x, y, this->radius);
}

void Pendulum2::render()
{
  line->render();
  circle->render();
}
